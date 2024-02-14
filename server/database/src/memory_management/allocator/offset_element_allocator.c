#include "offset_element_allocator.h"

#include <stddef.h>
#include <stdlib.h>

#include "page.h"

mem_offset_t offset_element_allocator_allocate(struct offset_element_allocator* self, mem_size_t alloc_size) {
  bool need_new_position = IS_EQUAL_OFFSET(self->current_position, MEM_NULL_OFFSET);
  if (need_new_position) {
    self->current_position = offset_page_allocator_allocate(self->page_alloc);
    self->current_position.value = sizeof(struct page_headers);
  }

  struct page_headers headers;

  offset_memory_manager_read(self->mem_manager,
                             (mem_offset_t){.data_block = self->current_position.data_block, .value = 0},
                             (mem_size_t){sizeof(headers)}, &headers);
  if (need_new_position) {
    headers.elements_header.elements_count.value = 0;
  }

  mem_size_t space_left = (mem_size_t){headers.page_header.page_data_size.value - self->current_position.value};

  if (alloc_size.value <= space_left.value) {
    mem_offset_t result = self->current_position;

    headers.elements_header.elements_count.value++;

    self->current_position.value += alloc_size.value;

    offset_memory_manager_write(
        self->mem_manager,
        (mem_offset_t){.data_block = self->current_position.data_block,
                       .value = sizeof(struct page_header) + offsetof(struct elements_page_header, elements_count)},
        (mem_size_t){sizeof(mem_size_t)}, &headers.elements_header.elements_count.value);

    return result;
  }

  mem_offset_t result;

  if (alloc_size.value % headers.page_header.page_data_size.value > space_left.value) {
    self->current_position = offset_page_allocator_allocate(self->page_alloc);
    self->current_position.value = sizeof(headers);
    result = self->current_position;
  } else {
    result = self->current_position;
    alloc_size.value -= space_left.value;

    struct elements_page_header elements_header = headers.elements_header;

    mem_offset_t new_block = offset_page_allocator_allocate(self->page_alloc);
    elements_header.next_page.value = new_block.data_block;
    elements_header.elements_count.value++;

    offset_memory_manager_write(
        self->mem_manager,
        (mem_offset_t){.data_block = self->current_position.data_block, .value = sizeof(struct page_header)},
        (mem_size_t){sizeof(elements_header)}, &elements_header);

    self->current_position = new_block;
    self->current_position.value = sizeof(headers);
  }

  while (alloc_size.value > 0) {
    mem_size_t page_data_size;

    offset_memory_manager_read(self->mem_manager,
                               (mem_offset_t){.data_block = self->current_position.data_block,
                                              .value = offsetof(struct page_header, page_data_size)},
                               (mem_size_t){sizeof(page_data_size)}, &page_data_size);

    space_left = (mem_size_t){page_data_size.value - self->current_position.value};

    if (space_left.value >= alloc_size.value) {
      mem_size_t elements_count = (mem_size_t){1};
      self->current_position.value += alloc_size.value;
      alloc_size.value = 0;
      offset_memory_manager_write(
          self->mem_manager,
          (mem_offset_t){.data_block = self->current_position.data_block,
                         .value = sizeof(struct page_header) + offsetof(struct elements_page_header, elements_count)},
          (mem_size_t){sizeof(mem_size_t)}, &elements_count);
      break;
    }

    alloc_size.value -= space_left.value;
    mem_offset_t new_page = offset_page_allocator_allocate(self->page_alloc);

    struct elements_page_header elements_header = {.elements_count = 1, .next_page = new_page.data_block};
    // there is might be optimization: not to write data in every allocation
    // keep current elements_header in ram and flush it only if data_block changes
    // or in destructor
    offset_memory_manager_write(
        self->mem_manager,
        (mem_offset_t){.data_block = self->current_position.data_block, .value = sizeof(struct page_header)},
        (mem_size_t){sizeof(elements_header)}, &elements_header);

    self->current_position.data_block = new_page.data_block;
    self->current_position.value = sizeof(struct page_headers);
  }

  return result;
}

void offset_element_allocator_free(struct offset_element_allocator* self, mem_offset_t target, mem_size_t size) {
  while (size.value != 0) {
    struct page_headers headers;

    offset_memory_manager_read(self->mem_manager, (mem_offset_t){.data_block = target.data_block, .value = 0},
                               (mem_size_t){sizeof(headers)}, &headers);

    uint64_t space_in_page = (headers.page_header.page_data_size.value - target.value);
    if (size.value < space_in_page) {
      size.value = 0;
    } else {
      size.value -= space_in_page;
    }

    if (headers.elements_header.elements_count.value == 1) {
      if (target.data_block == self->current_position.data_block) {
        self->current_position = MEM_NULL_OFFSET;
      }
      offset_page_allocator_free(self->page_alloc, target);
    } else {
      headers.elements_header.elements_count.value--;
      offset_memory_manager_write(
          self->mem_manager,
          (mem_offset_t){.data_block = target.data_block,
                         .value = sizeof(struct page_header) + offsetof(struct elements_page_header, elements_count)},
          (mem_size_t){sizeof(headers.elements_header.elements_count)}, &headers.elements_header.elements_count);
    }
    target.data_block = headers.elements_header.next_page.value;
    target.value = sizeof(headers);
  }
}

bool offset_element_allocator_alloc(struct offset_element_allocator** ptr) {
  *ptr = malloc(sizeof(struct offset_element_allocator));
  return (*ptr != NULL);
}

bool offset_element_allocator_ctor(struct offset_element_allocator* alloc, mem_offset_t place,
                                   struct offset_page_allocator* page_allocator,
                                   struct offset_memory_manager* mem_manager) {

  alloc->self_offset = place;
  alloc->page_alloc = page_allocator;
  alloc->mem_manager = mem_manager;
  alloc->current_position = MEM_NULL_OFFSET;
  return true;
}
void offset_element_allocator_dtor(struct offset_element_allocator* alloc) {
  struct offset_element_allocator_data data = {.current_position = alloc->current_position};
  offset_memory_manager_write(alloc->mem_manager, alloc->self_offset, (mem_size_t){sizeof(data)}, &data);
}

mem_size_t offset_element_allocator_get_data_size() {
  return (mem_size_t){sizeof(struct offset_element_allocator_data)};
}
bool offset_element_allocator_ctor_from_place(struct offset_element_allocator* alloc, mem_offset_t place,
                                              struct offset_page_allocator* page_allocator,
                                              struct offset_memory_manager* mem_manager) {
  struct offset_element_allocator_data data;
  offset_memory_manager_read(mem_manager, place, (mem_size_t){sizeof(data)}, &data);

  alloc->self_offset = place;
  alloc->page_alloc = page_allocator;
  alloc->mem_manager = mem_manager;
  alloc->current_position = data.current_position;

  return true;
}
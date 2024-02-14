#include "offset_page_allocator.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "common_types.h"
#include "offset_freelist_allocator.h"
#include "offset_memory_manager_extended_interface.h"
#include "page.h"

static bool is_page_free(struct offset_memory_manager* mem_manager, mem_offset_t page) {
  struct page_header header;
  offset_memory_manager_read(
      mem_manager, (mem_offset_t){.data_block = page.data_block, .value = offsetof(struct page_header, page_data_size)},
      (mem_size_t){sizeof(header.page_data_size)}, &header.page_data_size);
  return (header.page_data_size.value == 0);
}

mem_size_t offset_page_allocator_get_page_size(mem_size_t alloc_size) {
  return (mem_size_t){alloc_size.value + sizeof(struct page_header)};
}

mem_size_t offset_page_allocator_get_alloc_size(mem_size_t page_size) {
  return (mem_size_t){page_size.value - sizeof(struct page_header)};
}

static void offset_page_allocator_shrink_tail(struct offset_page_allocator* alloc, mem_offset_t tail) {
  mem_size_t page_size = offset_page_allocator_get_page_size(alloc->freelist_alloc.base_alloc.alloc_size);

  struct offset_list_iterator* iter;
  offset_list_iterator_alloc(&iter);

  tail.data_block -= page_size.value;
  tail.value = sizeof(struct page_header);
  int to_cut = 1;
  while (!offset_list_empty(alloc->freelist_alloc.free_list) && is_page_free(alloc->freelist_alloc.mem_manager, tail)) {
    ++to_cut;

    offset_list_iterator_ctor_from_place(iter, tail, alloc->freelist_alloc.mem_manager);
    offset_list_delete(alloc->freelist_alloc.free_list, iter);

    tail.data_block -= page_size.value;
  }

  free(iter);

  offset_memory_manager_cut(alloc->freelist_alloc.mem_manager, (mem_size_t){to_cut * page_size.value});
  alloc->last_allocated_page.data_block = tail.data_block;  // There is might be garbage if all pages was freed
}

void offset_page_allocator_free(struct offset_page_allocator* self, mem_offset_t target) {
  target.value = 0;

  if (target.data_block == self->last_allocated_page.data_block) {
    offset_page_allocator_shrink_tail(self, target);
  } else {
    mem_size_t page_data_size = {0};
    offset_memory_manager_write(self->freelist_alloc.mem_manager,
                                ADD_TO_OFFSET(target, offsetof(struct page_header, page_data_size)),
                                (mem_size_t){sizeof(mem_size_t)}, &page_data_size);
    offset_freelist_allocator_free((struct offset_freelist_allocator*)self,
                                   ADD_TO_OFFSET(target, sizeof(struct page_header)));
  }
}

mem_offset_t offset_page_allocator_allocate(struct offset_page_allocator* self) {
  mem_size_t page_size = offset_page_allocator_get_page_size(self->freelist_alloc.base_alloc.alloc_size);

  mem_offset_t result = offset_freelist_allocator_allocate((struct offset_freelist_allocator*)self);
  if (IS_EQUAL_OFFSET(result, MEM_NULL_OFFSET)) {
    result = offset_memory_manager_extend(self->freelist_alloc.mem_manager, page_size);
    self->last_allocated_page = result;
  }

  offset_memory_manager_write(
      self->freelist_alloc.mem_manager,
      (mem_offset_t){.data_block = result.data_block, .value = offsetof(struct page_header, page_data_size)},
      (mem_size_t){sizeof(page_size)}, &page_size);

  return ADD_TO_OFFSET(result, sizeof(struct page_header));
}

void offset_page_allocator_free_f(struct offset_fixed_base_allocator* base_alloc, mem_offset_t target) {
  offset_page_allocator_free((struct offset_page_allocator*)base_alloc, target);
}

mem_offset_t offset_page_allocator_allocate_f(struct offset_fixed_base_allocator* base_alloc) {
  return offset_page_allocator_allocate((struct offset_page_allocator*)base_alloc);
}

bool offset_page_allocator_alloc(struct offset_page_allocator** ptr) {
  *ptr = (struct offset_page_allocator*)malloc(sizeof(struct offset_page_allocator));
  return (*ptr != NULL);
}

bool offset_page_allocator_ctor(struct offset_page_allocator* alloc, mem_offset_t place,
                                struct offset_memory_manager* mem_manager, mem_size_t alloc_size) {
  if (!offset_freelist_allocator_ctor(&alloc->freelist_alloc,
                                      ADD_TO_OFFSET(place, sizeof(struct offset_page_allocator_data)), mem_manager,
                                      alloc_size)) {
    return false;
  }

  alloc->freelist_alloc.base_alloc.allocate_f = &offset_page_allocator_allocate_f;
  alloc->freelist_alloc.base_alloc.free_f = &offset_page_allocator_free_f;
  alloc->self_offset = place;
  alloc->last_allocated_page = MEM_NULL_OFFSET;
  return true;
}
void offset_page_allocator_dtor(struct offset_page_allocator* alloc) {
  offset_freelist_allocator_dtor(&alloc->freelist_alloc);

  struct offset_page_allocator_data data = {.last_allocated_page = alloc->last_allocated_page};

  offset_memory_manager_write(alloc->freelist_alloc.mem_manager, alloc->self_offset, (mem_size_t){sizeof(data)}, &data);
}

bool offset_page_allocator_ctor_from_place(struct offset_page_allocator* alloc, mem_offset_t place,
                                           struct offset_memory_manager* mem_manager) {
  struct offset_page_allocator_data data;
  offset_memory_manager_read(mem_manager, place, (mem_size_t){sizeof(data)}, &data);

  if (!offset_freelist_allocator_ctor_from_place(
          &alloc->freelist_alloc, ADD_TO_OFFSET(place, sizeof(struct offset_page_allocator_data)), mem_manager)) {
    return false;
  }

  alloc->last_allocated_page = data.last_allocated_page;
  alloc->freelist_alloc.base_alloc.allocate_f = &offset_page_allocator_allocate_f;
  alloc->freelist_alloc.base_alloc.free_f = &offset_page_allocator_free_f;
  alloc->self_offset = place;

  return true;
}

mem_size_t offset_page_allocator_get_data_size() {
  return (mem_size_t){offset_freelist_allocator_get_data_size().value + sizeof(struct offset_page_allocator_data)};
}
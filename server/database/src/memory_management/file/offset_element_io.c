#include "offset_element_io.h"

#include <stddef.h>
#include <stdlib.h>

#include "page.h"

bool offset_element_io_alloc(struct offset_element_io** ptr) {
  *ptr = malloc(sizeof(struct offset_element_io));
  return (*ptr != NULL);
}

void offset_element_io_read_f(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                              void* buffer) {
  struct offset_element_io* self = (struct offset_element_io*)manager;
  mem_size_t read = {0};

  if (offset.data_block == 0) {
    offset_memory_manager_read(self->main_mem_manager, offset, buf_size, buffer);
    return;
  }

  while (read.value < buf_size.value) {
    struct page_headers headers;

    offset_memory_manager_read(self->main_mem_manager, (mem_offset_t){.data_block = offset.data_block, .value = 0},
                               (mem_size_t){sizeof(headers)}, &headers);

    if (offset.value > headers.page_header.page_data_size.value) {
      offset.data_block = headers.elements_header.next_page.value;
      offset.value -= headers.page_header.page_data_size.value;
      continue;
    }

    mem_size_t data_in_page = {headers.page_header.page_data_size.value - offset.value};

    if (data_in_page.value > buf_size.value - read.value) {
      data_in_page.value = buf_size.value - read.value;
    }

    offset_memory_manager_read(self->main_mem_manager, offset, data_in_page, (char*)buffer + read.value);

    read.value += data_in_page.value;
    offset = (mem_offset_t){.data_block = headers.elements_header.next_page.value, .value = sizeof(headers)};
  }
}
void offset_element_io_write_f(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                               const void* buffer) {
  struct offset_element_io* self = (struct offset_element_io*)manager;
  mem_size_t written = {0};

  if (offset.data_block == 0) {
    offset_memory_manager_write(self->main_mem_manager, offset, buf_size, buffer);
    return;
  }

  while (written.value < buf_size.value) {
    struct page_headers headers;

    offset_memory_manager_read(self->main_mem_manager, (mem_offset_t){.data_block = offset.data_block, .value = 0},
                               (mem_size_t){sizeof(headers)}, &headers);

    if (offset.value > headers.page_header.page_data_size.value) {
      offset.data_block = headers.elements_header.next_page.value;
      offset.value -= headers.page_header.page_data_size.value;
      continue;
    }

    mem_size_t data_in_page = {headers.page_header.page_data_size.value - offset.value};

    if (data_in_page.value > buf_size.value - written.value) {
      data_in_page.value = buf_size.value - written.value;
    }

    offset_memory_manager_write(self->main_mem_manager, offset, data_in_page, (char*)buffer + written.value);

    written.value += data_in_page.value;
    offset = (mem_offset_t){.data_block = headers.elements_header.next_page.value, .value = sizeof(headers)};
  }
}

bool offset_element_io_ctor(struct offset_element_io* io, struct offset_memory_manager* mem_manager) {
  io->main_mem_manager = mem_manager;
  io->mem_manager.write_f = &offset_element_io_write_f;
  io->mem_manager.read_f = &offset_element_io_read_f;
  return true;
}
void offset_element_io_dtor(struct offset_element_io* io) {}

#include "offset_list_iterator.h"

#include <stddef.h>
#include <stdlib.h>

#include "common_types.h"

static void offset_list_iterator_read_header(const struct offset_list_iterator* iter,
                                             struct offset_list_node_header* header) {
  offset_memory_manager_read(iter->mem_manager, iter->current, (mem_size_t){sizeof(struct offset_list_node_header)},
                             header);
}

static void offset_list_iterator_write_header(struct offset_list_iterator* iter,
                                              const struct offset_list_node_header* header) {
  offset_memory_manager_write(iter->mem_manager, iter->current, (mem_size_t){sizeof(struct offset_list_node_header)},
                              header);
}

bool offset_list_iterator_ctor_from_place(struct offset_list_iterator* iter, mem_offset_t place,
                                          struct offset_memory_manager* mem_manager) {
  iter->mem_manager = mem_manager;
  iter->current = place;
  return true;
}

bool offset_list_iterator_alloc(struct offset_list_iterator** ptr) {
  *ptr = malloc(sizeof(struct offset_list_iterator));
  return (*ptr != NULL);
}

mem_offset_t offset_list_iterator_get_data_offset(const struct offset_list_iterator* iter) {
  return ADD_TO_OFFSET(iter->current, sizeof(struct offset_list_node_header));
}

mem_offset_t offset_list_iterator_get_data_offset_from_node_offset(mem_offset_t node_offset) {
  return ADD_TO_OFFSET(node_offset, sizeof(struct offset_list_node_header));
}

void offset_list_iterator_read_data(const struct offset_list_iterator* iter, mem_size_t buffer_size, void* buffer) {
  offset_memory_manager_read(iter->mem_manager, offset_list_iterator_get_data_offset(iter), buffer_size, buffer);
}
void offset_list_iterator_write_data(const struct offset_list_iterator* iter, mem_size_t buffer_size,
                                     const void* buffer) {
  offset_memory_manager_write(iter->mem_manager, offset_list_iterator_get_data_offset(iter), buffer_size, buffer);
}

void offset_list_iterator_next(struct offset_list_iterator* iter) {
  struct offset_list_node_header header;
  offset_list_iterator_read_header(iter, &header);
  offset_list_iterator_ctor_from_place(iter, header.next, iter->mem_manager);
}

void offset_list_iterator_prev(struct offset_list_iterator* iter) {
  struct offset_list_node_header header;
  offset_list_iterator_read_header(iter, &header);
  offset_list_iterator_ctor_from_place(iter, header.prev, iter->mem_manager);
}

bool offset_list_iterator_equals(const struct offset_list_iterator* lhs, const struct offset_list_iterator* rhs) {
  return !IS_EQUAL_OFFSET(lhs->current, MEM_NULL_OFFSET) && IS_EQUAL_OFFSET(lhs->current, rhs->current);
}

void offset_list_iterator_copy(const struct offset_list_iterator* src, struct offset_list_iterator* dst) {
  dst->current = src->current;
  dst->mem_manager = src->mem_manager;
}
mem_offset_t offset_list_iterator_get_node_offset(struct offset_list_iterator* iter) {
  return iter->current;
}

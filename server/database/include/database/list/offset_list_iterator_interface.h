#pragma once

#ifndef _OFFSET_LIST_ITERATOR_INTERFACE_H_
#define _OFFSET_LIST_ITERATOR_INTERFACE_H_

#include "common_types.h"
#include "offset_memory_manager_interface.h"

struct offset_list_iterator;

bool offset_list_iterator_alloc(struct offset_list_iterator** ptr);

bool offset_list_iterator_ctor_from_place(struct offset_list_iterator* iter, mem_offset_t place,
                                          struct offset_memory_manager* mem_manager);

void offset_list_iterator_next(struct offset_list_iterator* iter);
void offset_list_iterator_prev(struct offset_list_iterator* iter);

bool offset_list_iterator_equals(const struct offset_list_iterator* lhs, const struct offset_list_iterator* rhs);
void offset_list_iterator_copy(const struct offset_list_iterator* src, struct offset_list_iterator* dst);

void offset_list_iterator_read_data(const struct offset_list_iterator* iter, mem_size_t buffer_size, void* buffer);
void offset_list_iterator_write_data(const struct offset_list_iterator* iter, mem_size_t buffer_size,
                                     const void* buffer);

mem_offset_t offset_list_iterator_get_data_offset(const struct offset_list_iterator* iter);
mem_offset_t offset_list_iterator_get_data_offset_from_node_offset(mem_offset_t node_offset);

#endif /* _OFFSET_LIST_ITERATOR_INTERFACE_H_ */
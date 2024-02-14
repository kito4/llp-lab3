#pragma once

#ifndef _OFFSET_LIST_INTERFACE_H_
#define _OFFSET_LIST_INTERFACE_H_

#include <stdbool.h>

#include "common_types.h"
#include "offset_fixed_base_allocator_interface.h"
#include "offset_list_iterator_interface.h"
#include "offset_memory_manager_interface.h"

/**
 * @brief Offset based double linked list with fixed size nodes
 */
struct offset_list;

bool offset_list_alloc(struct offset_list** ptr);

/**
 * @brief Get node size, which corresponds to given data_size
 * 
 * @param data_size 
 * @return mem_size_t 
 */
mem_size_t offset_list_get_node_size(mem_size_t data_size);

/**
 * @brief Creates on the given place double linked list with fix-sized data block
 * 
 * The allocator sets the size of data block per node by it allocation size,
 * NOTE: Minimum allocation size is offset_list_get_node(0)
 * 
 * @param list 
 * @param mem_manager
 * @param allocator Allocator, which alloc_size could be calculated by calling offset_list_get_node_size(data_size)
 */
bool offset_list_ctor(struct offset_list* list, mem_offset_t place, struct offset_memory_manager* mem_manager,
                      struct offset_fixed_base_allocator* allocator);
void offset_list_dtor(struct offset_list* list);

void offset_list_get_allocator(struct offset_list* list, struct offset_fixed_base_allocator** alloc);

/**
 * @brief Amount of data consumed in serialized form
 * 
 * @return mem_size_t bytes
 */
mem_size_t offset_list_get_data_size();

/**
 * @brief Constructs list by reading data from given offset
 * 
 * @param list 
 * @param place
 * @param mem_manager 
 * @param allocator 
 */
bool offset_list_ctor_from_place(struct offset_list* list, mem_offset_t place,
                                 struct offset_memory_manager* mem_manager,
                                 struct offset_fixed_base_allocator* allocator);

void offset_list_head(struct offset_list* list, struct offset_list_iterator* target);
void offset_list_tail(struct offset_list* list, struct offset_list_iterator* target);

bool offset_list_empty(const struct offset_list* list);

/**
 * @brief Allocates and creates tail node with given data
 * 
 * Note that even if buffer_size < data_size,
 * then it will be allocated exactly data_size bytes for node data
 * 
 * @param list 
 * @param buffer_size must be not greater then list's data_size 
 * @param buffer
 */
bool offset_list_push_back(struct offset_list* list, mem_size_t buffer_size, const void* buffer);
bool offset_list_push_front(struct offset_list* list, mem_size_t buffer_size, const void* buffer);

/**
 * @brief Delete node
 * 
 * @param list 
 * @param node
 */
void offset_list_delete(struct offset_list* list, struct offset_list_iterator* node);
void offset_list_pop_back(struct offset_list* list);
void offset_list_pop_front(struct offset_list* list);

#endif /* _OFFSET_LIST_INTERFACE_H_ */

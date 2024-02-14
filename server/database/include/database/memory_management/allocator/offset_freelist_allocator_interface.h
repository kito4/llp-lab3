#pragma once

#ifndef _OFFSET_FREELIST_ALLOCATOR_INTERFACE_H_
#define _OFFSET_FREELIST_ALLOCATOR_INTERFACE_H_

#include <stdbool.h>

#include "common_types.h"
#include "offset_fixed_base_allocator_interface.h"
#include "offset_memory_manager_interface.h"

/**
 * @brief Offset freelist allocator
 * 
 * Free list allocator means, that it saves blocks that was freed in list and reuse them
 * If there no freed blocks returns MEM_NULL_OFFSET
 */
struct offset_freelist_allocator;

bool offset_freelist_allocator_alloc(struct offset_freelist_allocator** ptr);

/**
 * @brief Creates on the given place offset freelist allocator
 */
bool offset_freelist_allocator_ctor(struct offset_freelist_allocator* alloc, mem_offset_t place,
                                    struct offset_memory_manager* mem_manager, mem_size_t alloc_size);
void offset_freelist_allocator_dtor(struct offset_freelist_allocator* alloc);

/**
 * @brief Constructs allocator by reading data from given offset
 */
bool offset_freelist_allocator_ctor_from_place(struct offset_freelist_allocator* alloc, mem_offset_t place,
                                               struct offset_memory_manager* mem_manager);

/**
 * @brief Amount of data consumed in serialized form
 * 
 * @return mem_size_t bytes
 */
mem_size_t offset_freelist_allocator_get_data_size();

#endif /* _OFFSET_FREELIST_ALLOCATOR_INTERFACE_H_ */

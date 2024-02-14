#pragma once

#ifndef _OFFSET_FIXED_BASE_ALLOCATOR_INTERFACE_H_
#define _OFFSET_FIXED_BASE_ALLOCATOR_INTERFACE_H_

#include <stdbool.h>

#include "common_types.h"

/**
 * @brief Base struct for offset allocators with fixed allocation size
 * 
 * Offset means that it allocator works with offsets as pointers
 */
struct offset_fixed_base_allocator;

bool offset_fixed_base_allocator_alloc(struct offset_fixed_base_allocator** ptr);

mem_size_t offset_fixed_base_allocator_get_alloc_size(struct offset_fixed_base_allocator* ptr);

mem_offset_t offset_fixed_base_allocator_allocate(struct offset_fixed_base_allocator* allocator);
void offset_fixed_base_allocator_free(struct offset_fixed_base_allocator* allocator, mem_offset_t target);

#endif /* _OFFSET_FIXED_BASE_ALLOCATOR_INTERFACE_H_ */
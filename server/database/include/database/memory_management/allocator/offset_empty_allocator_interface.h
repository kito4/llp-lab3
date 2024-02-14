#pragma once

#ifndef _OFFSET_EMPTY_ALLOCATOR_H_
#define _OFFSET_EMPTY_ALLOCATOR_H_

#include <stdbool.h>

#include "common_types.h"

/**
 * @brief Empty allocator, that has empty allocate and free methods
 */
struct offset_empty_allocator;

bool offset_empty_allocator_alloc(struct offset_empty_allocator** ptr);

bool offset_empty_allocator_ctor(struct offset_empty_allocator* alloc, mem_size_t alloc_size);
void offset_empty_allocator_dtor(struct offset_empty_allocator* alloc);

#endif /* _OFFSET_EMPTY_ALLOCATOR_H_ */
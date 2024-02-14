#pragma once

#ifndef _OFFSET_FIXED_BASE_ALLOCATOR_H_
#define _OFFSET_FIXED_BASE_ALLOCATOR_H_

#include "common_types.h"

#include "offset_fixed_base_allocator_interface.h"

typedef mem_offset_t (*allocate_func_t)(struct offset_fixed_base_allocator*);
typedef void (*free_func_t)(struct offset_fixed_base_allocator*, mem_offset_t);

bool offset_fixed_base_allocator_ctor(struct offset_fixed_base_allocator* ptr, mem_size_t alloc_size);

struct offset_fixed_base_allocator {
  allocate_func_t allocate_f;
  free_func_t free_f;

  mem_size_t alloc_size;
};

#endif /* _OFFSET_FIXED_BASE_ALLOCATOR_H_ */
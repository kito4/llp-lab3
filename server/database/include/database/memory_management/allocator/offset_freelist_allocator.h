#pragma once

#ifndef _OFFSET_FREELIST_ALLOCATOR_H_
#define _OFFSET_FREELIST_ALLOCATOR_H_

#include "offset_fixed_base_allocator.h"
#include "offset_freelist_allocator_interface.h"
#include "offset_list_interface.h"

struct offset_freelist_allocator_data {
  mem_size_t alloc_size;
};

struct offset_freelist_allocator {
  struct offset_fixed_base_allocator base_alloc;

  mem_offset_t self_offset;
  struct offset_list* free_list;
  struct offset_memory_manager* mem_manager;
};

void offset_freelist_allocator_free(struct offset_freelist_allocator* alloc, mem_offset_t target);
mem_offset_t offset_freelist_allocator_allocate(struct offset_freelist_allocator* alloc);

#endif /* _OFFSET_FREELIST_ALLOCATOR_H_ */

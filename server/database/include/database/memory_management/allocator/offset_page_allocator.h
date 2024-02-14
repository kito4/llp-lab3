#pragma once

#ifndef _OFFSET_PAGE_ALLOCATOR_H_
#define _OFFSET_PAGE_ALLOCATOR_H_

#include <stdbool.h>

#include "offset_freelist_allocator.h"
#include "offset_page_allocator_interface.h"

struct offset_page_allocator_data {
  mem_offset_t last_allocated_page;
};

struct offset_page_allocator {
  struct offset_freelist_allocator freelist_alloc;

  mem_offset_t self_offset;
  mem_offset_t last_allocated_page;
};

#endif /* _OFFSET_PAGE_ALLOCATOR_H_ */
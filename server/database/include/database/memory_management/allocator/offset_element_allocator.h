#pragma once

#ifndef _OFFSET_ELEMENT_ALLOCATOR_H_
#define _OFFSET_ELEMENT_ALLOCATOR_H_

#include "offset_element_allocator_interface.h"

#include "offset_fixed_base_allocator.h"
#include "offset_page_allocator_interface.h"

struct offset_element_allocator_data {
  mem_offset_t current_position;
};

struct offset_element_allocator {
  struct offset_page_allocator* page_alloc;

  struct offset_memory_manager* mem_manager;

  mem_offset_t self_offset;
  mem_offset_t current_position;
};

#endif /* _OFFSET_ELEMENT_ALLOCATOR_H_ */
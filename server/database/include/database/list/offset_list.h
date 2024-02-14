#pragma once

#ifndef _OFFSET_LIST_H_
#define _OFFSET_LIST_H_

#include "offset_list_extended_interface.h"

#include "offset_fixed_base_allocator_interface.h"
#include "offset_memory_manager_interface.h"

struct offset_list_data {
  mem_offset_t head;
};

struct offset_list {
  struct offset_memory_manager* mem_manager;
  struct offset_fixed_base_allocator* allocator;

  mem_offset_t self_offset;
  mem_offset_t head;
};

#endif /* _OFFSET_LIST_H_ */

#pragma once

#ifndef _OFFSET_MEMORY_MANAGER_H_
#define _OFFSET_MEMORY_MANAGER_H_

#include "offset_memory_manager_extended_interface.h"

struct offset_memory_manager;

typedef mem_offset_t (*extend_memory_func_t)(struct offset_memory_manager*, mem_size_t size);
typedef void (*cut_memory_func_t)(struct offset_memory_manager*, mem_size_t size);
typedef void (*offset_read_func_t)(struct offset_memory_manager*, mem_offset_t, mem_size_t, void*);
typedef void (*offset_write_func_t)(struct offset_memory_manager*, mem_offset_t, mem_size_t, const void*);

struct offset_memory_manager {
  extend_memory_func_t extend_f;
  cut_memory_func_t cut_f;
  offset_read_func_t read_f;
  offset_write_func_t write_f;

  mem_size_t size;
};

bool offset_memory_manager_ctor(struct offset_memory_manager* manager, mem_size_t size);

#endif /* _OFFSET_MEMORY_MANAGER_H_ */

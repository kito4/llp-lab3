#pragma once

#ifndef _OFFSET_MEMORY_MANAGER_INTERFACE_H_
#define _OFFSET_MEMORY_MANAGER_INTERFACE_H_

#include <stdbool.h>

#include "common_types.h"

struct offset_memory_manager;

void offset_memory_manager_read(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                void* buffer);
void offset_memory_manager_write(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                 const void* buffer);

#endif /* _OFFSET_MEMORY_MANAGER_INTERFACE_H_ */

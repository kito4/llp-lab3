#pragma once

#ifndef _OFFSET_MEMORY_MANAGER_EXTENDED_INTERFACE_H_
#define _OFFSET_MEMORY_MANAGER_EXTENDED_INTERFACE_H_

#include "offset_memory_manager_interface.h"

mem_size_t offset_memory_manager_get_size(struct offset_memory_manager* manager);

mem_offset_t offset_memory_manager_extend(struct offset_memory_manager* manager, mem_size_t value);
void offset_memory_manager_cut(struct offset_memory_manager* manager, mem_size_t value);

#endif /* _OFFSET_MEMORY_MANAGER_EXTENDED_INTERFACE_H_ */
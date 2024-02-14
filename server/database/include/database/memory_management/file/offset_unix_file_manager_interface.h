#pragma once

#ifdef __unix__
#ifndef _OFFSET_unix_FILE_MANAGER_INTERFACE_H_
#define _OFFSET_unix_FILE_MANAGER_INTERFACE_H_

#include "common_types.h"
#include "offset_memory_manager_extended_interface.h"

struct offset_unix_file_manager;

bool offset_unix_file_manager_alloc(struct offset_unix_file_manager** ptr);
bool offset_unix_file_manager_ctor(struct offset_unix_file_manager* file_manager, const char* filename,
                                   mem_size_t page_size);
void offset_unix_file_manager_dtor(struct offset_unix_file_manager* file_manager);

#endif /* _OFFSET_unix_FILE_MANAGER_INTERFACE_H_ */
#endif /* __unix__ */
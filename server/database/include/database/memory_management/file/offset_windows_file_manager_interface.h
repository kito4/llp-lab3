#pragma once

#ifdef _WIN32
#ifndef _OFFSET_WINDOWS_FILE_MANAGER_INTERFACE_H_
#define _OFFSET_WINDOWS_FILE_MANAGER_INTERFACE_H_

#include "common_types.h"
#include "offset_memory_manager_extended_interface.h"

struct offset_windows_file_manager;

bool offset_windows_file_manager_alloc(struct offset_windows_file_manager** ptr);
bool offset_windows_file_manager_ctor(struct offset_windows_file_manager* file_manager, const char* filename,
                                      mem_size_t page_size);
void offset_windows_file_manager_dtor(struct offset_windows_file_manager* file_manager);

#endif /* _OFFSET_WINDOWS_FILE_MANAGER_INTERFACE_H_ */
#endif /* _WIN32 */
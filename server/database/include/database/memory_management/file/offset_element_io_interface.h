#pragma once

#ifndef _OFFSET_ELEMENT_IO_INTERFACE_H_
#define _OFFSET_ELEMENT_IO_INTERFACE_H_

#include "offset_memory_manager_interface.h"

/**
 * @brief wrapper on memory_manager that could read/write through multiple pages
 */
struct offset_element_io;

bool offset_element_io_alloc(struct offset_element_io** ptr);

bool offset_element_io_ctor(struct offset_element_io* io, struct offset_memory_manager* mem_manager);
void offset_element_io_dtor(struct offset_element_io* io);

#endif /* _OFFSET_ELEMENT_IO_INTERFACE_H_ */
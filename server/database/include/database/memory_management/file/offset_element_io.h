#pragma once

#ifndef _OFFSET_ELEMENT_IO_H_
#define _OFFSET_ELEMENT_IO_H_

#include "offset_element_io_interface.h"
#include "offset_memory_manager.h"

struct offset_element_io {
  struct offset_memory_manager mem_manager;

  struct offset_memory_manager* main_mem_manager;
};

#endif /* _OFFSET_ELEMENT_IO_H_ */
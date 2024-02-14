#pragma once

#ifndef _OFFSET_LIST_ITERATOR_H_
#define _OFFSET_LIST_ITERATOR_H_

#include "offset_list_iterator_interface.h"

struct offset_list_node_header {
  mem_offset_t next;
  mem_offset_t prev;
};

struct offset_list_iterator {
  mem_offset_t current;

  struct offset_memory_manager* mem_manager;
};

#endif /* _OFFSET_LIST_ITERATOR_H_ */
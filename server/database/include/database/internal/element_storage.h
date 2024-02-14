#pragma once

#include "common_types.h"
#include "offset_element_io_interface.h"
#include "offset_list_interface.h"
#include "offset_memory_manager_interface.h"
#include "offset_page_allocator_interface.h"

struct element_storage {
  struct offset_list* element_types;
  struct offset_list* link_types;

  struct offset_page_allocator* page_allocator;
  struct offset_element_allocator* heap;
  struct offset_fixed_element_allocator* link_node_allocator;
  struct offset_element_io* element_io;
  struct offset_memory_manager* mem_manager;
};

bool internal_element_storage_ctor(struct element_storage* storage, struct offset_memory_manager* mem_manager,
                                   mem_size_t page_size);
void internal_element_storage_dtor(struct element_storage* storage);

bool internal_element_storage_ctor_from_place(struct element_storage* storage,
                                              struct offset_memory_manager* mem_manager, mem_size_t page_size);

#ifndef _ELEMENT_STORAGE_H_
#define _ELEMENT_STORAGE_H_

#endif /* _ELEMENT_STORAGE_H_ */
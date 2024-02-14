#pragma once

#ifndef _LIST_CONSTRUCT_H_
#define _LIST_CONSTRUCT_H_

#include "common_types.h"
#include "offset_list_interface.h"
#include "offset_memory_manager_interface.h"
#include "offset_page_allocator_interface.h"

bool construct_list_with_element_alloc_from_place(struct offset_page_allocator* page_allocator,
                                                  struct offset_memory_manager* mem_manager, mem_offset_t* cur_pos,
                                                  struct offset_list* list, mem_size_t data_size);

bool construct_list_with_element_alloc(struct offset_page_allocator* page_allocator,
                                       struct offset_memory_manager* mem_manager, mem_offset_t* cur_pos,
                                       struct offset_list* list, mem_size_t data_size);

void destruct_list_with_element_alloc(struct offset_list* list);

#endif /* _LIST_CONSTRUCT_H_ */
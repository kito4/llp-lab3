#pragma once

#ifndef _OFFSET_ELEMENT_ALLOCATOR_INTERFACE_H_
#define _OFFSET_ELEMENT_ALLOCATOR_INTERFACE_H_

#include "offset_fixed_base_allocator_interface.h"
#include "offset_memory_manager_interface.h"
#include "offset_page_allocator_interface.h"

struct offset_element_allocator;

bool offset_element_allocator_alloc(struct offset_element_allocator** ptr);

bool offset_element_allocator_ctor(struct offset_element_allocator* alloc, mem_offset_t place,
                                   struct offset_page_allocator* page_allocator,
                                   struct offset_memory_manager* mem_manager);
void offset_element_allocator_dtor(struct offset_element_allocator* alloc);

mem_size_t offset_element_allocator_get_data_size();
bool offset_element_allocator_ctor_from_place(struct offset_element_allocator* alloc, mem_offset_t place,
                                              struct offset_page_allocator* page_allocator,
                                              struct offset_memory_manager* mem_manager);

mem_offset_t offset_element_allocator_allocate(struct offset_element_allocator* alloc, mem_size_t size);
void offset_element_allocator_free(struct offset_element_allocator* alloc, mem_offset_t target, mem_size_t size);

#endif /* _OFFSET_ELEMENT_ALLOCATOR_INTERFACE_H_ */
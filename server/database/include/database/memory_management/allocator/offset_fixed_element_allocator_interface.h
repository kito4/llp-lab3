#pragma once

#ifndef _OFFSET_FIXED_ELEMENT_ALLOCATOR_INTERFACE_H_
#define _OFFSET_FIXED_ELEMENT_ALLOCATOR_INTERFACE_H_

#include "common_types.h"
#include "offset_element_allocator_interface.h"

struct offset_fixed_element_allocator;

bool offset_fixed_element_allocator_alloc(struct offset_fixed_element_allocator** ptr);

bool offset_fixed_element_allocator_ctor_from_element_allocator(struct offset_fixed_element_allocator* alloc,
                                                                mem_size_t alloc_size,
                                                                struct offset_element_allocator* element_alloc);
void offset_fixed_element_allocator_dtor(struct offset_fixed_element_allocator* alloc);

bool offset_fixed_element_allocator_ctor_from_place(struct offset_fixed_element_allocator* alloc, mem_offset_t place,
                                                    mem_size_t alloc_size, struct offset_page_allocator* page_allocator,
                                                    struct offset_memory_manager* mem_manager);

bool offset_fixed_element_allocator_ctor(struct offset_fixed_element_allocator* alloc, mem_offset_t place,
                                         mem_size_t alloc_size, struct offset_page_allocator* page_allocator,
                                         struct offset_memory_manager* mem_manager);

// Returns data size if created by ctor or ctor_from_place
mem_size_t offset_fixed_element_allocator_get_data_size();

void offset_fixed_element_allocator_get_allocator(struct offset_fixed_element_allocator* alloc,
                                                  struct offset_element_allocator** element_alloc);

#endif /* _OFFSET_FIXED_ELEMENT_ALLOCATOR_INTERFACE_H_ */
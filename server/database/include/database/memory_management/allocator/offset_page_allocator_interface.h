#pragma once

#ifndef _OFFSET_PAGE_ALLOCATOR_INTERFACE_H_
#define _OFFSET_PAGE_ALLOCATOR_INTERFACE_H_

#include <stdbool.h>

#include "common_types.h"
#include "offset_freelist_allocator_interface.h"

struct offset_page_allocator;

bool offset_page_allocator_alloc(struct offset_page_allocator** ptr);

/**
 * @brief Creates on the given place page allocator
 * 
 * @param alloc 
 * @param place 
 * @param mem_manager 
 * @param alloc_size 
 */
bool offset_page_allocator_ctor(struct offset_page_allocator* alloc, mem_offset_t place,
                                struct offset_memory_manager* mem_manager, mem_size_t alloc_size);
void offset_page_allocator_dtor(struct offset_page_allocator* alloc);

/**
 * @brief Constructs allocator by reading data from given offset
 * 
 * @param alloc 
 * @param place
 * @param mem_manager 
 */
bool offset_page_allocator_ctor_from_place(struct offset_page_allocator* alloc, mem_offset_t place,
                                           struct offset_memory_manager* mem_manager);

/**
 * @brief Amount of data consumed in serialized form
 * 
 * @return mem_size_t bytes
 */
mem_size_t offset_page_allocator_get_data_size();

/**
 * @brief Real page size with overhead
 * 
 * @param alloc_size 
 * @return mem_size_t 
 */
mem_size_t offset_page_allocator_get_page_size(mem_size_t alloc_size);

/**
 * @brief Alloc size, that could be provided in ctor, to get given page_size
 * 
 * @param alloc 
 * @return mem_offset_t 
 */
mem_size_t offset_page_allocator_get_alloc_size(mem_size_t page_size);

mem_offset_t offset_page_allocator_allocate(struct offset_page_allocator* alloc);
void offset_page_allocator_free(struct offset_page_allocator* alloc, mem_offset_t target);

#endif /* _OFFSET_PAGE_ALLOCATOR_INTERFACE_H_ */

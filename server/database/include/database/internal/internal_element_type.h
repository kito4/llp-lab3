#pragma once

#ifndef _INTERNAL_ELEMENT_TYPE_H_
#define _INTERNAL_ELEMENT_TYPE_H_

#include "common_types.h"
#include "offset_element_allocator_interface.h"
#include "offset_list_interface.h"
#include "offset_memory_manager_interface.h"
#include "schema.h"

struct internal_element_type_data {
  element_type_id_t type_id;
  mem_size_t name_size;
  mem_offset_t name_offset;
  mem_size_t attribute_count;
  mem_offset_t attributes_offset;
  mem_size_t element_data_size;
  /* + offset_list data */
  /* + offset_list data */
};

struct internal_element_type {
  element_type_id_t type_id;

  mem_size_t name_size;
  mem_offset_t name_offset;

  mem_size_t attribute_count;
  mem_offset_t attributes_offset;

  struct offset_list* element_list;

  struct offset_element_allocator* heap;
  struct offset_memory_manager* element_io;
  mem_offset_t self_offset;
};

bool internal_element_type_ctor(struct internal_element_type* type, mem_offset_t place,
                                const struct element_type* element_type, struct offset_element_allocator* heap,
                                struct offset_page_allocator* page_allocator, struct offset_memory_manager* element_io);

bool internal_element_type_ctor_from_place(struct internal_element_type* type, mem_offset_t place,
                                           struct offset_element_allocator* heap,
                                           struct offset_page_allocator* page_allocator,
                                           struct offset_memory_manager* element_io);

void internal_element_type_dtor(struct internal_element_type* type);
void internal_element_type_delete(struct internal_element_type* type);

mem_size_t internal_element_type_get_data_size();

bool element_type_ctor(struct element_type* dst, struct internal_element_type* src);

#endif /* _INTERNAL_ELEMENT_TYPE_H_ */
#pragma once

#ifndef _INTERNAL_ELEMENT_H_
#define _INTERNAL_ELEMENT_H_

#include "common_types.h"
#include "element.h"
#include "offset_element_allocator_interface.h"
#include "offset_list_interface.h"
#include "offset_memory_manager_interface.h"

struct internal_element_data {
  element_type_id_t type_id;
  mem_size_t attrs_data_size;
  mem_offset_t element_type_offset;
  /* + attributes data */
  /* + offset_list data links_out */
  /* + offset_list data links_in */
};

struct internal_element {
  element_type_id_t type_id;
  mem_offset_t element_type_offset;

  mem_size_t attrs_data_size;
  attribute_count_t attrs_count;
  struct attribute* attrs;

  struct offset_list* links_out;
  struct offset_list* links_in;

  struct offset_element_allocator* heap;
  struct offset_memory_manager* mem_manager;
  struct offset_fixed_base_allocator* link_node_allocator;
  mem_offset_t self_offset;
};

mem_size_t internal_element_get_data_size(attribute_count_t attr_count, enum ATTRIBUTE_TYPE* types);

bool internal_element_create_at(mem_offset_t place, const struct element* element, mem_offset_t element_type_offset,
                                struct offset_fixed_base_allocator* link_node_allocator,
                                struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager);

bool internal_element_rewrite_attrs_at(mem_offset_t place, const struct attribute* attrs,
                                       attribute_count_t attribute_count, struct offset_element_allocator* heap,
                                       struct offset_memory_manager* mem_manager);

bool internal_element_ctor_from_place(struct internal_element* internal_element, mem_offset_t place,
                                      struct offset_fixed_base_allocator* link_node_allocator,
                                      struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager);
bool internal_element_ctor_from_place_and_attrs(struct internal_element* internal_element, mem_offset_t place,
                                                attribute_count_t attrs_count, enum ATTRIBUTE_TYPE* attrs_type,
                                                struct offset_fixed_base_allocator* link_node_allocator,
                                                struct offset_element_allocator* heap,
                                                struct offset_memory_manager* mem_manager);

void internal_element_dtor(struct internal_element* internal_element);
bool internal_element_delete(struct internal_element* internal_element);

bool internal_element_links_out_ctor_from_place(struct offset_list* list, mem_offset_t element_offset,
                                                struct offset_fixed_base_allocator* link_node_allocator,
                                                struct offset_memory_manager* mem_manager);
bool internal_element_links_in_ctor_from_place(struct offset_list* list, mem_offset_t element_offset,
                                               struct offset_fixed_base_allocator* link_node_allocator,
                                               struct offset_memory_manager* mem_manager);

void internal_element_links_dtor(struct offset_list* list);

bool element_ctor(struct element* dst, struct internal_element* src, struct offset_page_allocator* page_allocator,
                  struct offset_memory_manager* mem_manager);

#endif /* _INTERNAL_ELEMENT_H_ */
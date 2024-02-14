#pragma once

#ifndef _INTERNAL_LINK_TYPE_H_
#define _INTERNAL_LINK_TYPE_H_

#include "common_types.h"
#include "offset_element_allocator_interface.h"
#include "offset_list_interface.h"
#include "offset_memory_manager_interface.h"
#include "schema.h"

struct internal_link_type_data {
  link_type_id_t type_id;
  mem_size_t name_size;
  mem_offset_t name_offset;
};

struct internal_link_type {
  link_type_id_t type_id;
  mem_size_t name_size;
  mem_offset_t name_offset;

  mem_offset_t self_offset;
  struct offset_memory_manager* mem_manager;
  struct offset_element_allocator* heap;
};

bool internal_link_type_ctor(struct internal_link_type* type, mem_offset_t place, const struct link_type* link_type,
                             struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager);

bool internal_link_type_ctor_from_place(struct internal_link_type* type, mem_offset_t place,
                                        struct offset_element_allocator* heap,
                                        struct offset_memory_manager* mem_manager);

void internal_link_type_dtor(struct internal_link_type* type);
void internal_link_type_delete(struct internal_link_type* type);

mem_size_t internal_link_type_get_data_size();

bool link_type_ctor(struct link_type* dst, struct internal_link_type* src);

#endif /* _INTERNAL_LINK_TYPE_H_ */
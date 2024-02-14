#include "list_construct.h"

#include "offset_fixed_element_allocator_interface.h"

#include <stdlib.h>

bool construct_list_with_element_alloc_from_place(struct offset_page_allocator* page_allocator,
                                                  struct offset_memory_manager* mem_manager, mem_offset_t* cur_pos,
                                                  struct offset_list* list, mem_size_t data_size) {
  mem_size_t node_size = offset_list_get_node_size(data_size);

  struct offset_fixed_element_allocator* fixed_alloc;
  if (!offset_fixed_element_allocator_alloc(&fixed_alloc)) {
    return false;
  }

  if (!offset_fixed_element_allocator_ctor_from_place(fixed_alloc, *cur_pos, node_size, page_allocator, mem_manager)) {
    free(fixed_alloc);
    return false;
  }

  cur_pos->value += offset_fixed_element_allocator_get_data_size().value;

  if (!offset_list_ctor_from_place(list, *cur_pos, mem_manager, (struct offset_fixed_base_allocator*)fixed_alloc)) {
    offset_fixed_element_allocator_dtor(fixed_alloc);
    free(fixed_alloc);
    return false;
  }
  cur_pos->value += offset_list_get_data_size().value;
  return true;
}

bool construct_list_with_element_alloc(struct offset_page_allocator* page_allocator,
                                       struct offset_memory_manager* mem_manager, mem_offset_t* cur_pos,
                                       struct offset_list* list, mem_size_t data_size) {
  mem_size_t node_size = offset_list_get_node_size(data_size);

  struct offset_fixed_element_allocator* fixed_alloc;
  if (!offset_fixed_element_allocator_alloc(&fixed_alloc)) {
    return false;
  }

  if (!offset_fixed_element_allocator_ctor(fixed_alloc, *cur_pos, node_size, page_allocator, mem_manager)) {
    free(fixed_alloc);
    return false;
  }

  cur_pos->value += offset_fixed_element_allocator_get_data_size().value;

  if (!offset_list_ctor(list, *cur_pos, mem_manager, (struct offset_fixed_base_allocator*)fixed_alloc)) {
    offset_fixed_element_allocator_dtor(fixed_alloc);
    free(fixed_alloc);
    return false;
  }
  cur_pos->value += offset_list_get_data_size().value;
  return true;
}

void destruct_list_with_element_alloc(struct offset_list* list) {
  struct offset_fixed_base_allocator* base_alloc;
  offset_list_get_allocator(list, &base_alloc);

  offset_list_dtor(list);

  offset_fixed_element_allocator_dtor((struct offset_fixed_element_allocator*)base_alloc);
  free(base_alloc);
}
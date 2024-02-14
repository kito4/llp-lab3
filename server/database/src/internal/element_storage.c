#include "element_storage.h"

#include "internal_element_type.h"
#include "internal_link.h"
#include "internal_link_type.h"
#include "list_construct.h"
#include "offset_element_allocator_interface.h"
#include "offset_fixed_element_allocator_interface.h"

#include <stdlib.h>

bool internal_element_storage_ctor_from_place(struct element_storage* storage,
                                              struct offset_memory_manager* mem_manager, mem_size_t page_size) {
  bool res = true;
  res &= offset_list_alloc(&storage->element_types);
  res &= offset_list_alloc(&storage->link_types);
  res &= offset_page_allocator_alloc(&storage->page_allocator);
  res &= offset_element_allocator_alloc(&storage->heap);
  res &= offset_fixed_element_allocator_alloc(&storage->link_node_allocator);
  res &= offset_element_io_alloc(&storage->element_io);

  if (!res || !offset_element_io_ctor(storage->element_io, mem_manager)) {
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  storage->mem_manager = mem_manager;

  mem_offset_t cur_pos = {.data_block = 0, .value = 0};

  if (!construct_list_with_element_alloc_from_place(storage->page_allocator,
                                                    (struct offset_memory_manager*)storage->element_io, &cur_pos,
                                                    storage->element_types, internal_element_type_get_data_size())) {
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  if (!construct_list_with_element_alloc_from_place(storage->page_allocator,
                                                    (struct offset_memory_manager*)storage->element_io, &cur_pos,
                                                    storage->link_types, internal_link_type_get_data_size())) {
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  if (!offset_page_allocator_ctor_from_place(storage->page_allocator, cur_pos, storage->mem_manager)) {
    destruct_list_with_element_alloc(storage->link_types);
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }
  cur_pos.value += offset_page_allocator_get_data_size().value;

  if (!offset_element_allocator_ctor_from_place(storage->heap, cur_pos, storage->page_allocator,
                                                storage->mem_manager)) {
    offset_page_allocator_dtor(storage->page_allocator);
    destruct_list_with_element_alloc(storage->link_types);
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }
  cur_pos.value += offset_element_allocator_get_data_size().value;

  mem_size_t link_node_size = offset_list_get_node_size(internal_link_get_data_size());

  if (!offset_fixed_element_allocator_ctor_from_place(storage->link_node_allocator, cur_pos, link_node_size,
                                                      storage->page_allocator, mem_manager)) {
    offset_element_allocator_dtor(storage->heap);
    offset_page_allocator_dtor(storage->page_allocator);
    destruct_list_with_element_alloc(storage->link_types);
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  cur_pos.value += offset_fixed_element_allocator_get_data_size().value;
  return true;
}

bool internal_element_storage_ctor(struct element_storage* storage, struct offset_memory_manager* mem_manager,
                                   mem_size_t page_size) {
  bool res = true;
  res &= offset_list_alloc(&storage->element_types);
  res &= offset_list_alloc(&storage->link_types);
  res &= offset_page_allocator_alloc(&storage->page_allocator);
  res &= offset_element_allocator_alloc(&storage->heap);
  res &= offset_fixed_element_allocator_alloc(&storage->link_node_allocator);
  res &= offset_element_io_alloc(&storage->element_io);

  if (!res || !offset_element_io_ctor(storage->element_io, mem_manager)) {
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  storage->mem_manager = mem_manager;

  mem_offset_t cur_pos = {.data_block = 0, .value = 0};

  if (!construct_list_with_element_alloc(storage->page_allocator, (struct offset_memory_manager*)storage->element_io,
                                         &cur_pos, storage->element_types, internal_element_type_get_data_size())) {
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  if (!construct_list_with_element_alloc(storage->page_allocator, (struct offset_memory_manager*)storage->element_io,
                                         &cur_pos, storage->link_types, internal_link_type_get_data_size())) {
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  mem_size_t page_alloc_size = offset_page_allocator_get_alloc_size(page_size);
  if (!offset_page_allocator_ctor(storage->page_allocator, cur_pos, storage->mem_manager, page_alloc_size)) {
    destruct_list_with_element_alloc(storage->link_types);
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }
  cur_pos.value += offset_page_allocator_get_data_size().value;

  if (!offset_element_allocator_ctor(storage->heap, cur_pos, storage->page_allocator, storage->mem_manager)) {
    offset_page_allocator_dtor(storage->page_allocator);
    destruct_list_with_element_alloc(storage->link_types);
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }
  cur_pos.value += offset_element_allocator_get_data_size().value;

  mem_size_t link_node_size = offset_list_get_node_size(internal_link_get_data_size());

  if (!offset_fixed_element_allocator_ctor(storage->link_node_allocator, cur_pos, link_node_size,
                                           storage->page_allocator,
                                           (struct offset_memory_manager*)storage->element_io)) {
    offset_element_allocator_dtor(storage->heap);
    offset_page_allocator_dtor(storage->page_allocator);
    destruct_list_with_element_alloc(storage->link_types);
    destruct_list_with_element_alloc(storage->element_types);
    offset_element_io_dtor(storage->element_io);
    free(storage->element_types);
    free(storage->link_types);
    free(storage->page_allocator);
    free(storage->heap);
    free(storage->link_node_allocator);
    free(storage->element_io);
    return false;
  }

  cur_pos.value += offset_fixed_element_allocator_get_data_size().value;

  return res;
}

void internal_element_storage_dtor(struct element_storage* storage) {
  destruct_list_with_element_alloc(storage->link_types);
  destruct_list_with_element_alloc(storage->element_types);

  offset_fixed_element_allocator_dtor(storage->link_node_allocator);
  offset_element_allocator_dtor(storage->heap);
  offset_page_allocator_dtor(storage->page_allocator);

  offset_element_io_dtor(storage->element_io);

  free(storage->element_types);
  free(storage->link_node_allocator);
  free(storage->link_types);
  free(storage->page_allocator);
  free(storage->heap);
  free(storage->element_io);
}

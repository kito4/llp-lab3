#include "offset_freelist_allocator.h"

#include <stdlib.h>

#include "common_types.h"
#include "offset_empty_allocator_interface.h"
#include "offset_fixed_base_allocator.h"
#include "offset_list_extended_interface.h"
#include "offset_memory_manager_interface.h"

// static void offset_freelist_allocator_add_range(struct offset_freelist_allocator* alloc, mem_size_t size,
//                                                 mem_offset_t start) {
//   int count = size.value / alloc->base_alloc.alloc_size.value;
//   for (int i = 0; i < count; i++) {
//     offset_list_push_back_inplace(alloc->free_list, ADD_TO_OFFSET(start, alloc->base_alloc.alloc_size.value * count),
//                                   (mem_size_t){0}, NULL);
//   }
// }

void offset_freelist_allocator_free(struct offset_freelist_allocator* alloc, mem_offset_t target) {
  offset_list_push_front_inplace(alloc->free_list, target, (mem_size_t){0}, NULL);
}

mem_offset_t offset_freelist_allocator_allocate(struct offset_freelist_allocator* alloc) {
  if (!offset_list_empty(alloc->free_list)) {
    struct offset_list_iterator* last_freed;
    offset_list_iterator_alloc(&last_freed);
    offset_list_head(alloc->free_list, last_freed);

    mem_offset_t result = offset_list_iterator_get_node_offset(last_freed);

    offset_list_pop_front(alloc->free_list);
    free(last_freed);

    return result;
  }
  return MEM_NULL_OFFSET;
}

mem_offset_t offset_freelist_allocate_f(struct offset_fixed_base_allocator* alloc) {
  struct offset_freelist_allocator* self = (struct offset_freelist_allocator*)alloc;
  return offset_freelist_allocator_allocate(self);
}

void offset_freelist_free_f(struct offset_fixed_base_allocator* alloc, mem_offset_t target) {
  struct offset_freelist_allocator* self = (struct offset_freelist_allocator*)alloc;
  offset_freelist_allocator_free(self, target);
}

bool offset_freelist_allocator_alloc(struct offset_freelist_allocator** ptr) {
  *ptr = (struct offset_freelist_allocator*)malloc(sizeof(struct offset_freelist_allocator));
  return (*ptr != NULL);
}

bool offset_freelist_allocator_ctor(struct offset_freelist_allocator* alloc, mem_offset_t place,
                                    struct offset_memory_manager* mem_manager, mem_size_t alloc_size) {
  mem_size_t node_size = offset_list_get_node_size((mem_size_t){0});
  if (alloc_size.value < node_size.value) {
    alloc_size = node_size;
  }

  if (!offset_fixed_base_allocator_ctor(&alloc->base_alloc, alloc_size)) {
    return false;
  }

  alloc->base_alloc.allocate_f = &offset_freelist_allocate_f;
  alloc->base_alloc.free_f = &offset_freelist_free_f;
  alloc->self_offset = place;

  if (offset_list_alloc(&alloc->free_list)) {
    struct offset_empty_allocator* empty_alloc;
    if (offset_empty_allocator_alloc(&empty_alloc)) {
      if (!offset_empty_allocator_ctor(empty_alloc, node_size)) {
        free(alloc->free_list);
        free(empty_alloc);
        return false;
      }
      if (!offset_list_ctor(alloc->free_list, ADD_TO_OFFSET(place, sizeof(struct offset_freelist_allocator_data)),
                            mem_manager, (struct offset_fixed_base_allocator*)empty_alloc)) {
        free(alloc->free_list);
        free(empty_alloc);
        return false;
      }
    } else {
      free(alloc->free_list);
      return false;
    }
  } else {
    return false;
  }

  alloc->mem_manager = mem_manager;
  return true;
}

bool offset_freelist_allocator_ctor_from_place(struct offset_freelist_allocator* alloc, mem_offset_t place,
                                               struct offset_memory_manager* mem_manager) {

  struct offset_freelist_allocator_data data;
  offset_memory_manager_read(mem_manager, place, (mem_size_t){sizeof(data)}, &data);
  if (!offset_fixed_base_allocator_ctor(&alloc->base_alloc, data.alloc_size)) {
    return false;
  }

  alloc->base_alloc.allocate_f = &offset_freelist_allocate_f;
  alloc->base_alloc.free_f = &offset_freelist_free_f;

  alloc->self_offset = place;
  alloc->mem_manager = mem_manager;

  if (offset_list_alloc(&alloc->free_list)) {
    struct offset_empty_allocator* empty_alloc;
    if (offset_empty_allocator_alloc(&empty_alloc)) {
      if (!offset_empty_allocator_ctor(empty_alloc, data.alloc_size)) {
        free(alloc->free_list);
        free(empty_alloc);
        return false;
      }
      if (!offset_list_ctor_from_place(alloc->free_list,
                                       ADD_TO_OFFSET(place, sizeof(struct offset_freelist_allocator_data)), mem_manager,
                                       (struct offset_fixed_base_allocator*)empty_alloc)) {
        free(alloc->free_list);
        free(empty_alloc);
        return false;
      }
    } else {
      free(alloc->free_list);
      return false;
    }
  } else {
    return false;
  }

  return true;
}

void offset_freelist_allocator_dtor(struct offset_freelist_allocator* alloc) {
  struct offset_fixed_base_allocator* base_alloc;
  offset_list_get_allocator(alloc->free_list, &base_alloc);
  free(base_alloc);

  offset_list_dtor(alloc->free_list);
  free(alloc->free_list);

  struct offset_freelist_allocator_data data = {.alloc_size = alloc->base_alloc.alloc_size};

  offset_memory_manager_write(alloc->mem_manager, alloc->self_offset, (mem_size_t){sizeof(data)}, &data);
}

mem_size_t offset_freelist_allocator_get_data_size() {
  return (mem_size_t){.value = (sizeof(struct offset_freelist_allocator_data) + offset_list_get_data_size().value)};
}
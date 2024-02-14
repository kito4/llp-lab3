#include "offset_fixed_element_allocator.h"

#include <stdlib.h>

bool offset_fixed_element_allocator_alloc(struct offset_fixed_element_allocator** ptr) {
  *ptr = malloc(sizeof(struct offset_fixed_element_allocator));
  return (*ptr != NULL);
}

mem_offset_t offset_fixed_element_allocator_allocate_f(struct offset_fixed_base_allocator* fixed) {
  struct offset_fixed_element_allocator* self = (struct offset_fixed_element_allocator*)fixed;
  return offset_element_allocator_allocate(self->element_alloc, fixed->alloc_size);
}

void offset_fixed_element_allocator_free_f(struct offset_fixed_base_allocator* fixed, mem_offset_t target) {
  struct offset_fixed_element_allocator* self = (struct offset_fixed_element_allocator*)fixed;
  offset_element_allocator_free(self->element_alloc, target, fixed->alloc_size);
}

bool offset_fixed_element_allocator_ctor_from_element_allocator(struct offset_fixed_element_allocator* alloc,
                                                                mem_size_t alloc_size,
                                                                struct offset_element_allocator* element_alloc) {
  if (!offset_fixed_base_allocator_ctor(&alloc->base_alloc, alloc_size)) {
    return false;
  }
  alloc->base_alloc.allocate_f = &offset_fixed_element_allocator_allocate_f;
  alloc->base_alloc.free_f = &offset_fixed_element_allocator_free_f;

  alloc->element_alloc = element_alloc;
  alloc->owner = false;
  return true;
}

bool offset_fixed_element_allocator_ctor_from_place(struct offset_fixed_element_allocator* alloc, mem_offset_t place,
                                                    mem_size_t alloc_size, struct offset_page_allocator* page_allocator,
                                                    struct offset_memory_manager* mem_manager) {
  if (!offset_element_allocator_alloc(&alloc->element_alloc)) {
    return false;
  }

  if (!offset_element_allocator_ctor_from_place(alloc->element_alloc, place, page_allocator, mem_manager)) {
    free(alloc->element_alloc);
    return false;
  }

  if (!offset_fixed_element_allocator_ctor_from_element_allocator(alloc, alloc_size, alloc->element_alloc)) {
    offset_element_allocator_dtor(alloc->element_alloc);
    free(alloc->element_alloc);
    return false;
  }

  alloc->owner = true;

  return true;
}

bool offset_fixed_element_allocator_ctor(struct offset_fixed_element_allocator* alloc, mem_offset_t place,
                                         mem_size_t alloc_size, struct offset_page_allocator* page_allocator,
                                         struct offset_memory_manager* mem_manager) {
  if (!offset_element_allocator_alloc(&alloc->element_alloc)) {
    return false;
  }

  if (!offset_element_allocator_ctor(alloc->element_alloc, place, page_allocator, mem_manager)) {
    free(alloc->element_alloc);
    return false;
  }

  if (!offset_fixed_element_allocator_ctor_from_element_allocator(alloc, alloc_size, alloc->element_alloc)) {
    offset_element_allocator_dtor(alloc->element_alloc);
    free(alloc->element_alloc);
    return false;
  }

  alloc->owner = true;

  return true;
}

void offset_fixed_element_allocator_dtor(struct offset_fixed_element_allocator* alloc) {
  if (alloc->owner) {
    offset_element_allocator_dtor(alloc->element_alloc);
    free(alloc->element_alloc);
  }
}

mem_size_t offset_fixed_element_allocator_get_data_size() {
  return offset_element_allocator_get_data_size();
}

void offset_fixed_element_allocator_get_allocator(struct offset_fixed_element_allocator* alloc,
                                                  struct offset_element_allocator** element_alloc) {
  *element_alloc = alloc->element_alloc;
}

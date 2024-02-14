#include "offset_empty_allocator_interface.h"

#include <stdlib.h>

#include "common_types.h"
#include "offset_fixed_base_allocator.h"

struct offset_empty_allocator {
  struct offset_fixed_base_allocator base_alloc;
};

mem_offset_t offset_empty_allocator_allocate_f(struct offset_fixed_base_allocator* alloc) {
  return MEM_NULL_OFFSET;
}

void offset_empty_allocator_free_f(struct offset_fixed_base_allocator* alloc, mem_offset_t target) {}

bool offset_empty_allocator_alloc(struct offset_empty_allocator** ptr) {
  *ptr = (struct offset_empty_allocator*)malloc(sizeof(struct offset_empty_allocator));
  return (*ptr != NULL);
}

bool offset_empty_allocator_ctor(struct offset_empty_allocator* alloc, mem_size_t alloc_size) {
  if (!offset_fixed_base_allocator_ctor((struct offset_fixed_base_allocator*)alloc, alloc_size)) {
    return false;
  }

  alloc->base_alloc.alloc_size = alloc_size;
  alloc->base_alloc.allocate_f = &offset_empty_allocator_allocate_f;
  alloc->base_alloc.free_f = &offset_empty_allocator_free_f;

  return true;
}

void offset_empty_allocator_dtor(struct offset_empty_allocator* alloc) {}

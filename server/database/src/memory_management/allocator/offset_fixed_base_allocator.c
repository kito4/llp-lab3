#include "offset_fixed_base_allocator.h"

#include <stdlib.h>

bool offset_fixed_base_allocator_alloc(struct offset_fixed_base_allocator** ptr) {
  *ptr = malloc(sizeof(struct offset_fixed_base_allocator));
  return (*ptr != NULL);
}

bool offset_fixed_base_allocator_ctor(struct offset_fixed_base_allocator* allocator, mem_size_t alloc_size) {
  allocator->alloc_size = alloc_size;
  return true;
}

mem_size_t offset_fixed_base_allocator_get_alloc_size(struct offset_fixed_base_allocator* ptr) {
  return ptr->alloc_size;
}

mem_offset_t offset_fixed_base_allocator_allocate(struct offset_fixed_base_allocator* allocator) {
  return allocator->allocate_f(allocator);
}

void offset_fixed_base_allocator_free(struct offset_fixed_base_allocator* allocator, mem_offset_t target) {
  allocator->free_f(allocator, target);
}
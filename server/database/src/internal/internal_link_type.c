#include "internal_link_type.h"
#include "internal_link.h"

#include <string.h>

mem_size_t internal_link_get_data_size() {
  return (mem_size_t){.value = sizeof(struct internal_link)};
}

bool internal_link_type_ctor(struct internal_link_type* type, mem_offset_t place, const struct link_type* link_type,
                             struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager) {
  mem_size_t name_size = {.value = strlen(link_type->type_name) + 1};
  mem_offset_t name_offset = offset_element_allocator_allocate(heap, name_size);

  if (IS_EQUAL_OFFSET(name_offset, MEM_NULL_OFFSET)) {
    return false;
  }

  offset_memory_manager_write(mem_manager, name_offset, name_size, link_type->type_name);

  *type = (struct internal_link_type){.name_offset = name_offset,
                                      .name_size = name_size,
                                      .self_offset = place,
                                      .type_id = link_type->type_id,
                                      .heap = heap,
                                      .mem_manager = mem_manager};

  struct internal_link_type_data data = {
      .name_offset = name_offset, .name_size = name_size, .type_id = link_type->type_id};

  offset_memory_manager_write(mem_manager, place, (mem_size_t){.value = sizeof(data)}, &data);

  return true;
}

bool internal_link_type_ctor_from_place(struct internal_link_type* type, mem_offset_t place,
                                        struct offset_element_allocator* heap,
                                        struct offset_memory_manager* mem_manager) {
  struct internal_link_type_data data;
  offset_memory_manager_read(mem_manager, place, (mem_size_t){.value = sizeof(data)}, &data);

  *type = (struct internal_link_type){.heap = heap,
                                      .mem_manager = mem_manager,
                                      .name_offset = data.name_offset,
                                      .name_size = data.name_size,
                                      .self_offset = place,
                                      .type_id = data.type_id};

  return true;
}

void internal_link_type_dtor(struct internal_link_type* type) {
  // data immutable, so we don't need to write it
}

void internal_link_type_delete(struct internal_link_type* type) {
  offset_element_allocator_free(type->heap, type->name_offset, type->name_size);
  internal_link_type_dtor(type);
}

mem_size_t internal_link_type_get_data_size() {
  return (mem_size_t){.value = sizeof(struct internal_link_type_data)};
}

bool link_type_ctor(struct link_type* dst, struct internal_link_type* src) {
  dst->type_id = src->type_id;

  dst->type_name = malloc(src->name_size.value);
  if (dst->type_name == NULL) {
    return false;
  }
  offset_memory_manager_read(src->mem_manager, src->name_offset, src->name_size, dst->type_name);
  return true;
}
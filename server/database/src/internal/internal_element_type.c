#include "internal_element_type.h"

#include <stdlib.h>
#include <string.h>

#include "internal_element.h"
#include "list_construct.h"

bool internal_element_type_ctor(struct internal_element_type* type, mem_offset_t place,
                                const struct element_type* element_type, struct offset_element_allocator* heap,
                                struct offset_page_allocator* page_allocator,
                                struct offset_memory_manager* element_io) {
  mem_size_t name_size = (mem_size_t){.value = strlen(element_type->type_name) + 1};
  mem_offset_t name_offset = offset_element_allocator_allocate(heap, name_size);

  if (IS_EQUAL_OFFSET(name_offset, MEM_NULL_OFFSET)) {
    return false;
  }

  mem_size_t attributes_size = (mem_size_t){.value = sizeof(enum ATTRIBUTE_TYPE) * element_type->attribute_count};
  mem_offset_t attributes_offset = offset_element_allocator_allocate(heap, attributes_size);

  if (IS_EQUAL_OFFSET(attributes_offset, MEM_NULL_OFFSET)) {
    offset_element_allocator_free(heap, name_offset, name_size);
    return false;
  }

  offset_memory_manager_write(element_io, name_offset, name_size, element_type->type_name);
  offset_memory_manager_write(element_io, attributes_offset, attributes_size, element_type->attribute_types);

  *type = (struct internal_element_type){.type_id = element_type->type_id,
                                         .attribute_count = element_type->attribute_count,
                                         .attributes_offset = attributes_offset,
                                         .name_size = name_size,
                                         .name_offset = name_offset,
                                         .self_offset = place,
                                         .heap = heap,
                                         .element_io = element_io};

  if (!offset_list_alloc(&type->element_list)) {
    offset_element_allocator_free(heap, attributes_offset, attributes_size);
    offset_element_allocator_free(heap, name_offset, name_size);
    return false;
  }

  mem_size_t element_data_size =
      internal_element_get_data_size(element_type->attribute_count, element_type->attribute_types);
  mem_offset_t list_place = ADD_TO_OFFSET(place, sizeof(struct internal_element_type_data));

  struct internal_element_type_data data = {.attribute_count = type->attribute_count,
                                            .attributes_offset = type->attributes_offset,
                                            .name_offset = type->name_offset,
                                            .name_size = type->name_size,
                                            .type_id = type->type_id,
                                            .element_data_size = element_data_size};

  offset_memory_manager_write(element_io, place, (mem_size_t){.value = sizeof(data)}, &data);

  if (!construct_list_with_element_alloc(page_allocator, element_io, &list_place, type->element_list,
                                         element_data_size)) {
    free(type->element_list);
    offset_element_allocator_free(heap, attributes_offset, attributes_size);
    offset_element_allocator_free(heap, name_offset, name_size);
    return false;
  }

  return true;
}

bool internal_element_type_ctor_from_place(struct internal_element_type* type, mem_offset_t place,
                                           struct offset_element_allocator* heap,
                                           struct offset_page_allocator* page_allocator,
                                           struct offset_memory_manager* element_io) {
  struct internal_element_type_data data;

  offset_memory_manager_read(element_io, place, (mem_size_t){.value = sizeof(data)}, &data);

  *type = (struct internal_element_type){.attribute_count = data.attribute_count,
                                         .attributes_offset = data.attributes_offset,
                                         .name_size = data.name_size,
                                         .name_offset = data.name_offset,
                                         .type_id = data.type_id,
                                         .self_offset = place,
                                         .heap = heap,
                                         .element_io = element_io};

  if (!offset_list_alloc(&type->element_list)) {
    return false;
  }

  mem_offset_t list_place = ADD_TO_OFFSET(place, sizeof(struct internal_element_type_data));

  if (!construct_list_with_element_alloc_from_place(page_allocator, element_io, &list_place, type->element_list,
                                                    data.element_data_size)) {
    free(type->element_list);
    return false;
  }

  return true;
}

void internal_element_type_dtor(struct internal_element_type* type) {
  // data immutable, so we don't need to write it
  destruct_list_with_element_alloc(type->element_list);
  free(type->element_list);
}

void internal_element_type_delete(struct internal_element_type* type) {
  offset_element_allocator_free(type->heap, type->name_offset, type->name_size);
  offset_element_allocator_free(type->heap, type->attributes_offset,
                                (mem_size_t){.value = sizeof(enum ATTRIBUTE_TYPE) * type->attribute_count.value});
  internal_element_type_dtor(type);
}

mem_size_t internal_element_type_get_data_size() {
  return (mem_size_t){.value = (sizeof(struct internal_element_type_data) +
                                offset_element_allocator_get_data_size().value + offset_list_get_data_size().value)};
}

bool element_type_ctor(struct element_type* dst, struct internal_element_type* src) {
  dst->attribute_count = src->attribute_count.value;
  dst->type_id = src->type_id;

  dst->type_name = malloc(src->name_size.value);
  if (dst->type_name == NULL) {
    return false;
  }

  offset_memory_manager_read(src->element_io, src->name_offset, src->name_size, dst->type_name);

  dst->attribute_types = malloc(src->attribute_count.value * sizeof(enum ATTRIBUTE_TYPE));
  if (dst->attribute_types == NULL) {
    return false;
  }

  offset_memory_manager_read(src->element_io, src->attributes_offset,
                             (mem_size_t){.value = src->attribute_count.value * sizeof(enum ATTRIBUTE_TYPE)},
                             dst->attribute_types);

  return true;
}

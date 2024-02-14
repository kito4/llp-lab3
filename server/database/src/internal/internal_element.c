#include "internal_element.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "internal_element_type.h"
#include "internal_link.h"

mem_size_t internal_element_get_attrs_size(attribute_count_t attrs_count, enum ATTRIBUTE_TYPE* types) {
  mem_size_t res = {.value = 0};
  for (attribute_count_t i = 0; i < attrs_count; i++) {
    if (types[i] == ATTR_TYPE_INT64) {
      res.value += sizeof(int64_t);
    } else if (types[i] == ATTR_TYPE_INT32) {
      res.value += sizeof(int32_t);
    } else if (types[i] == ATTR_TYPE_DOUBLE) {
      res.value += sizeof(double);
    } else if (types[i] == ATTR_TYPE_BOOL) {
      res.value += sizeof(bool);
    } else if (types[i] == ATTR_TYPE_STRING) {
      res.value += sizeof(mem_offset_t) + sizeof(mem_size_t);
    }
  }
  return res;
}

mem_size_t internal_element_get_attrs_size2(attribute_count_t attrs_count, const struct attribute* attrs) {
  mem_size_t res = {.value = 0};
  for (attribute_count_t i = 0; i < attrs_count; i++) {
    if (attrs[i].type == ATTR_TYPE_INT64) {
      res.value += sizeof(int64_t);
    } else if (attrs[i].type == ATTR_TYPE_INT32) {
      res.value += sizeof(int32_t);
    } else if (attrs[i].type == ATTR_TYPE_DOUBLE) {
      res.value += sizeof(double);
    } else if (attrs[i].type == ATTR_TYPE_BOOL) {
      res.value += sizeof(bool);
    } else if (attrs[i].type == ATTR_TYPE_STRING) {
      res.value += sizeof(mem_offset_t) + sizeof(mem_size_t);
    }
  }
  return res;
}

mem_size_t internal_element_get_data_size(attribute_count_t attrs_count, enum ATTRIBUTE_TYPE* types) {
  return (mem_size_t){.value = sizeof(struct internal_element_data) + 2 * offset_list_get_data_size().value +
                               internal_element_get_attrs_size(attrs_count, types).value};
}

static void clean_attrs(attribute_count_t attrs_count, const struct attribute* attrs, void* target,
                        struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager) {
  char* current = (char*)target;
  for (attribute_count_t i = 0; i < attrs_count; i++) {
    switch (attrs[i].type) {
      case ATTR_TYPE_BOOL:
        current += sizeof(bool);
        break;
      case ATTR_TYPE_DOUBLE:
        current += sizeof(double);
        break;
      case ATTR_TYPE_INT32:
        current += sizeof(int32_t);
        break;
      case ATTR_TYPE_INT64:
        current += sizeof(int64_t);
        break;
      case ATTR_TYPE_STRING:;
        mem_size_t str_size;
        memcpy(&str_size, (void*)current, sizeof(mem_size_t));
        current += sizeof(mem_size_t);

        mem_offset_t str_offset;
        memcpy(&str_offset, (void*)current, sizeof(mem_offset_t));
        current += sizeof(mem_offset_t);

        offset_element_allocator_free(heap, str_offset, str_size);
        break;
      default:
        break;
    }
  }
}

static mem_size_t serialize_attrs(attribute_count_t attrs_count, const struct attribute* attrs, void* target,
                                  struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager) {
  char* current = (char*)target;
  for (attribute_count_t i = 0; i < attrs_count; i++) {
    switch (attrs[i].type) {
      case ATTR_TYPE_BOOL:
        memcpy((void*)current, &(attrs[i].value.as_bool), sizeof(bool));
        current += sizeof(bool);
        break;
      case ATTR_TYPE_DOUBLE:
        memcpy((void*)current, &(attrs[i].value.as_double), sizeof(double));
        current += sizeof(double);
        break;
      case ATTR_TYPE_INT32:
        memcpy((void*)current, &(attrs[i].value.as_int32), sizeof(int32_t));
        current += sizeof(int32_t);
        break;
      case ATTR_TYPE_INT64:
        memcpy((void*)current, &(attrs[i].value.as_int64), sizeof(int64_t));
        current += sizeof(int64_t);
        break;
      case ATTR_TYPE_STRING:;
        mem_size_t str_size = (mem_size_t){.value = strlen(attrs[i].value.as_string.data) + 1};
        mem_offset_t str_offset = offset_element_allocator_allocate(heap, str_size);

        if (IS_EQUAL_OFFSET(str_offset, MEM_NULL_OFFSET)) {
          clean_attrs(i, attrs, target, heap, mem_manager);
          return (mem_size_t){.value = 0};
        }

        offset_memory_manager_write(mem_manager, str_offset, str_size, attrs[i].value.as_string.data);

        memcpy((void*)current, &str_size, sizeof(mem_size_t));
        current += sizeof(mem_size_t);

        memcpy((void*)current, &str_offset, sizeof(mem_offset_t));
        current += sizeof(mem_offset_t);
        break;
      default:
        clean_attrs(i, attrs, target, heap, mem_manager);
        return (mem_size_t){.value = 0};
    }
  }
  return (mem_size_t){.value = current - (char*)target};
}

static void free_attrs(attribute_count_t attrs_count, struct attribute* attrs) {
  if (attrs == NULL) {
    return;
  }
  for (attribute_count_t k = 0; k < attrs_count; k++) {
    if (attrs[k].type == ATTR_TYPE_STRING) {
      free(attrs[k].value.as_string.data);
    }
  }
}

// TODO: think about safety
static mem_size_t deserialize_attrs(attribute_count_t attrs_count, struct attribute* target, const void* attrs_data,
                                    struct offset_memory_manager* mem_manager) {
  char* current = (char*)attrs_data;
  for (attribute_count_t i = 0; i < attrs_count; i++) {
    switch (target[i].type) {
      case ATTR_TYPE_BOOL:
        memcpy(&(target[i].value.as_bool), (void*)current, sizeof(bool));
        current += sizeof(bool);
        break;
      case ATTR_TYPE_DOUBLE:
        memcpy(&(target[i].value.as_double), (void*)current, sizeof(double));
        current += sizeof(double);
        break;
      case ATTR_TYPE_INT32:
        memcpy(&(target[i].value.as_int32), (void*)current, sizeof(int32_t));
        current += sizeof(int32_t);
        break;
      case ATTR_TYPE_INT64:
        memcpy(&(target[i].value.as_int64), (void*)current, sizeof(int64_t));
        current += sizeof(int64_t);
        break;
      case ATTR_TYPE_STRING:;
        mem_size_t str_size;
        mem_offset_t str_offset;

        memcpy(&str_size, (void*)current, sizeof(mem_size_t));
        current += sizeof(mem_size_t);

        memcpy(&str_offset, (void*)current, sizeof(mem_offset_t));
        current += sizeof(mem_offset_t);

        target[i].value.as_string.data = malloc(str_size.value);
        if (target[i].value.as_string.data == NULL) {
          free_attrs(i, target);
          return (mem_size_t){.value = 0};
        }

        offset_memory_manager_read(mem_manager, str_offset, str_size, target[i].value.as_string.data);
        break;
      default:
        free_attrs(i, target);
        return (mem_size_t){.value = 0};
    }
  }
  return (mem_size_t){.value = current - (char*)attrs_data};
}

bool internal_element_rewrite_attrs_at(mem_offset_t place, const struct attribute* attrs,
                                       attribute_count_t attribute_count, struct offset_element_allocator* heap,
                                       struct offset_memory_manager* mem_manager) {
  mem_size_t attrs_data_size = internal_element_get_attrs_size2(attribute_count, attrs);
  void* attrs_data = malloc(attrs_data_size.value);
  if (attrs_data == NULL) {
    return false;
  }

  offset_memory_manager_read(mem_manager, ADD_TO_OFFSET(place, sizeof(struct internal_element_data)), attrs_data_size,
                             attrs_data);

  clean_attrs(attribute_count, attrs, attrs_data, heap, mem_manager);

  mem_size_t written = serialize_attrs(attribute_count, attrs, attrs_data, heap, mem_manager);

  if (written.value != attrs_data_size.value) {
    free(attrs_data);
    return false;
  }

  offset_memory_manager_write(mem_manager, ADD_TO_OFFSET(place, sizeof(struct internal_element_data)), attrs_data_size,
                              attrs_data);

  free(attrs_data);
  return true;
}

bool internal_element_create_at(mem_offset_t place, const struct element* element, mem_offset_t element_type_offset,
                                struct offset_fixed_base_allocator* link_node_allocator,
                                struct offset_element_allocator* heap, struct offset_memory_manager* mem_manager) {
  struct internal_element_data data = {
      .attrs_data_size = internal_element_get_attrs_size(element->element_type->attribute_count,
                                                         element->element_type->attribute_types),
      .element_type_offset = element_type_offset,
      .type_id = element->element_type->type_id};

  offset_memory_manager_write(mem_manager, place, (mem_size_t){.value = sizeof(data)}, &data);

  void* attrs_data = malloc(data.attrs_data_size.value);
  if (attrs_data == NULL) {
    return false;
  }

  mem_size_t written = serialize_attrs(element->attribute_count, element->attributes, attrs_data, heap, mem_manager);

  if (written.value != data.attrs_data_size.value) {
    free(attrs_data);
    return false;
  }

  offset_memory_manager_write(mem_manager, ADD_TO_OFFSET(place, sizeof(data)), data.attrs_data_size, attrs_data);

  mem_offset_t links_in_offset = ADD_TO_OFFSET(place, sizeof(data) + data.attrs_data_size.value);
  mem_offset_t links_out_offset =
      ADD_TO_OFFSET(place, sizeof(data) + data.attrs_data_size.value + offset_list_get_data_size().value);

  struct offset_list* links_out;
  struct offset_list* links_in;

  if (!offset_list_alloc(&links_out)) {
    clean_attrs(element->attribute_count, element->attributes, attrs_data, heap, mem_manager);
    free(attrs_data);

    return false;
  }

  if (!offset_list_alloc(&links_in)) {
    free(links_out);

    clean_attrs(element->attribute_count, element->attributes, attrs_data, heap, mem_manager);
    free(attrs_data);

    return false;
  }

  if (!offset_list_ctor(links_out, links_out_offset, mem_manager, link_node_allocator)) {
    free(links_in);
    free(links_out);

    clean_attrs(element->attribute_count, element->attributes, attrs_data, heap, mem_manager);
    free(attrs_data);

    return false;
  }

  bool res = offset_list_ctor(links_in, links_in_offset, mem_manager, link_node_allocator);

  offset_list_dtor(links_in);
  offset_list_dtor(links_out);
  free(links_in);
  free(links_out);

  free(attrs_data);

  return res;
}

bool internal_element_ctor_from_place_and_attrs(struct internal_element* internal_element, mem_offset_t place,
                                                attribute_count_t attrs_count, enum ATTRIBUTE_TYPE* attrs_type,
                                                struct offset_fixed_base_allocator* link_node_allocator,
                                                struct offset_element_allocator* heap,
                                                struct offset_memory_manager* mem_manager) {
  struct internal_element_data data;
  offset_memory_manager_read(mem_manager, place, (mem_size_t){.value = sizeof(data)}, &data);

  *internal_element = (struct internal_element){.attrs_data_size = data.attrs_data_size,
                                                .element_type_offset = data.element_type_offset,
                                                .type_id = data.type_id,
                                                .heap = heap,
                                                .attrs_count = attrs_count,
                                                .mem_manager = mem_manager,
                                                .link_node_allocator = link_node_allocator,
                                                .self_offset = place};

  void* attrs_data = malloc(data.attrs_data_size.value);
  if (attrs_data == NULL) {
    return false;
  }
  offset_memory_manager_read(mem_manager, ADD_TO_OFFSET(place, sizeof(data)), data.attrs_data_size, attrs_data);

  internal_element->attrs = malloc(sizeof(struct attribute) * attrs_count);
  if (!internal_element->attrs) {
    free(attrs_data);
    return false;
  }

  for (attribute_count_t i = 0; i < attrs_count; i++) {
    internal_element->attrs[i].type = attrs_type[i];
  }

  mem_size_t read = deserialize_attrs(attrs_count, internal_element->attrs, attrs_data, mem_manager);
  if (read.value != data.attrs_data_size.value) {
    free(internal_element->attrs);
    free(attrs_data);
    return false;
  }

  mem_offset_t links_out_offset = ADD_TO_OFFSET(place, sizeof(data) + data.attrs_data_size.value);
  mem_offset_t links_in_offset =
      ADD_TO_OFFSET(place, sizeof(data) + data.attrs_data_size.value + offset_list_get_data_size().value);

  internal_element->links_out = NULL;
  internal_element->links_in = NULL;

  if (!offset_list_alloc(&internal_element->links_out) || !offset_list_alloc(&internal_element->links_in)) {
    free(internal_element->links_in);
    free(internal_element->links_out);

    free_attrs(attrs_count, internal_element->attrs);
    free(internal_element->attrs);

    free(attrs_data);
    return false;
  }

  if (offset_list_ctor_from_place(internal_element->links_out, links_out_offset, mem_manager, link_node_allocator)) {
    if (offset_list_ctor_from_place(internal_element->links_in, links_in_offset, mem_manager, link_node_allocator)) {
      free(attrs_data);

      return true;
    }
    offset_list_dtor(internal_element->links_out);
  }

  free(internal_element->links_in);
  free(internal_element->links_out);

  free_attrs(attrs_count, internal_element->attrs);
  free(internal_element->attrs);

  free(attrs_data);

  return false;
}

bool internal_element_ctor_from_place(struct internal_element* internal_element, mem_offset_t place,
                                      struct offset_fixed_base_allocator* link_node_allocator,
                                      struct offset_element_allocator* heap,
                                      struct offset_memory_manager* mem_manager) {
  mem_offset_t element_type_offset;
  offset_memory_manager_read(mem_manager,
                             ADD_TO_OFFSET(place, offsetof(struct internal_element_data, element_type_offset)),
                             (mem_size_t){.value = sizeof(mem_offset_t)}, &element_type_offset);
  mem_size_t attrs_count;
  offset_memory_manager_read(
      mem_manager, ADD_TO_OFFSET(element_type_offset, offsetof(struct internal_element_type_data, attribute_count)),
      (mem_size_t){.value = sizeof(mem_size_t)}, &attrs_count);

  mem_offset_t attributes_offset;
  offset_memory_manager_read(
      mem_manager, ADD_TO_OFFSET(element_type_offset, offsetof(struct internal_element_type_data, attributes_offset)),
      (mem_size_t){.value = sizeof(mem_offset_t)}, &attributes_offset);

  enum ATTRIBUTE_TYPE* attrs_type = malloc(sizeof(enum ATTRIBUTE_TYPE) * attrs_count.value);
  if (attrs_type == NULL) {
    return false;
  }

  offset_memory_manager_read(mem_manager, attributes_offset,
                             (mem_size_t){.value = sizeof(enum ATTRIBUTE_TYPE) * attrs_count.value}, attrs_type);

  bool res = internal_element_ctor_from_place_and_attrs(internal_element, place, attrs_count.value, attrs_type,
                                                        link_node_allocator, heap, mem_manager);

  free(attrs_type);
  return res;
}

void internal_element_dtor(struct internal_element* internal_element) {
  offset_list_dtor(internal_element->links_in);
  offset_list_dtor(internal_element->links_out);
  free(internal_element->links_in);
  free(internal_element->links_out);

  free_attrs(internal_element->attrs_count, internal_element->attrs);
  free(internal_element->attrs);
}

static bool delete_links(struct offset_list* links, bool out_links, struct offset_memory_manager* mem_manager,
                         struct offset_fixed_base_allocator* link_node_allocator) {
  struct offset_list_iterator* iter;
  if (!offset_list_iterator_alloc(&iter)) {
    return false;
  }

  struct offset_list* target_list;
  if (!offset_list_alloc(&target_list)) {
    free(iter);
    return false;
  }

  struct internal_link link;
  while (!offset_list_empty(links)) {
    offset_list_head(links, iter);
    offset_list_iterator_read_data(iter, (mem_size_t){.value = sizeof(link)}, &link);
    offset_list_pop_front(links);

    mem_offset_t list_offset;
    mem_size_t target_attrs_size;
    offset_memory_manager_read(mem_manager,
                               ADD_TO_OFFSET(offset_list_iterator_get_data_offset_from_node_offset(link.target_node),
                                             offsetof(struct internal_element_data, attrs_data_size)),
                               (mem_size_t){.value = sizeof(mem_size_t)}, &target_attrs_size);
    if (out_links) {
      list_offset = ADD_TO_OFFSET(
          offset_list_iterator_get_data_offset_from_node_offset(link.target_node),
          sizeof(struct internal_element_data) + target_attrs_size.value + offset_list_get_data_size().value);
    } else {
      list_offset = ADD_TO_OFFSET(offset_list_iterator_get_data_offset_from_node_offset(link.target_node),
                                  sizeof(struct internal_element_data) + target_attrs_size.value);
    }

    if (!offset_list_ctor_from_place(target_list, list_offset, mem_manager, link_node_allocator)) {
      free(target_list);
      free(iter);
      return false;
    }

    if (!offset_list_iterator_ctor_from_place(iter, link.chained_link_node, mem_manager)) {
      offset_list_dtor(target_list);
      free(target_list);
      free(iter);
      return false;
    }

    offset_list_delete(target_list, iter);
    offset_list_dtor(target_list);
  }

  free(target_list);
  free(iter);
  return true;
}

bool internal_element_delete(struct internal_element* internal_element) {
  mem_offset_t attrs_data_offset = ADD_TO_OFFSET(internal_element->self_offset, sizeof(struct internal_element_data));
  void* attrs_data = malloc(internal_element->attrs_data_size.value);
  if (attrs_data == NULL) {
    return false;
  }
  offset_memory_manager_read(internal_element->mem_manager, attrs_data_offset, internal_element->attrs_data_size,
                             attrs_data);

  clean_attrs(internal_element->attrs_count, internal_element->attrs, attrs_data, internal_element->heap,
              internal_element->mem_manager);

  free(attrs_data);

  if (!delete_links(internal_element->links_out, true, internal_element->mem_manager,
                    internal_element->link_node_allocator)) {
    return false;
  }

  if (!delete_links(internal_element->links_in, false, internal_element->mem_manager,
                    internal_element->link_node_allocator)) {
    return false;
  }

  internal_element_dtor(internal_element);

  return true;
}

// Note that functions moves out internal_element's data, so you can't reuse it
// Also links are not filled
bool element_ctor(struct element* dst, struct internal_element* src, struct offset_page_allocator* page_allocator,
                  struct offset_memory_manager* mem_manager) {
  dst->attributes = src->attrs;

  struct internal_element_type internal_element_type;
  if (!internal_element_type_ctor_from_place(&internal_element_type, src->element_type_offset, src->heap,
                                             page_allocator, mem_manager)) {
    return false;
  }

  dst->attribute_count = internal_element_type.attribute_count.value;
  dst->owns_type_ptr = true;
  dst->element_type = malloc(sizeof(struct element_type));

  if (dst->element_type == NULL) {
    internal_element_type_dtor(&internal_element_type);
    return false;
  }

  if (!element_type_ctor(dst->element_type, &internal_element_type)) {
    free(dst->element_type);
    internal_element_type_dtor(&internal_element_type);
    return false;
  }

  internal_element_type_dtor(&internal_element_type);
  src->attrs = NULL;

  return true;
}

bool internal_element_links_out_ctor_from_place(struct offset_list* list, mem_offset_t element_offset,
                                                struct offset_fixed_base_allocator* link_node_allocator,
                                                struct offset_memory_manager* mem_manager) {
  mem_size_t attrs_data_size;
  offset_memory_manager_read(mem_manager,
                             ADD_TO_OFFSET(element_offset, offsetof(struct internal_element_data, attrs_data_size)),
                             (mem_size_t){.value = sizeof(mem_size_t)}, &attrs_data_size);
  mem_offset_t links_out_offset =
      ADD_TO_OFFSET(element_offset, sizeof(struct internal_element_data) + attrs_data_size.value);

  return offset_list_ctor_from_place(list, links_out_offset, mem_manager, link_node_allocator);
}
bool internal_element_links_in_ctor_from_place(struct offset_list* list, mem_offset_t element_offset,
                                               struct offset_fixed_base_allocator* link_node_allocator,
                                               struct offset_memory_manager* mem_manager) {
  mem_size_t attrs_data_size;
  offset_memory_manager_read(mem_manager,
                             ADD_TO_OFFSET(element_offset, offsetof(struct internal_element_data, attrs_data_size)),
                             (mem_size_t){.value = sizeof(mem_size_t)}, &attrs_data_size);
  mem_offset_t links_in_offset = ADD_TO_OFFSET(
      element_offset, sizeof(struct internal_element_data) + attrs_data_size.value + offset_list_get_data_size().value);

  return offset_list_ctor_from_place(list, links_in_offset, mem_manager, link_node_allocator);
}

void internal_element_links_dtor(struct offset_list* list) {
  offset_list_dtor(list);
}
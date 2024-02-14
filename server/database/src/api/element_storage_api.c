#include "element_storage_api.h"

#include "element_storage.h"
#include "internal_element.h"
#include "internal_element_type.h"
#include "internal_link.h"
#include "internal_link_type.h"
#include "offset_list_extended_interface.h"
#include "offset_unix_file_manager_interface.h"
#include "offset_windows_file_manager_interface.h"
#include "storage_iterator.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

bool element_storage_alloc(struct element_storage** ptr) {
  *ptr = malloc(sizeof(struct element_storage));
  return (*ptr != NULL);
}

bool element_storage_ctor(struct element_storage* storage, const char* filename, size_t page_size) {
#ifdef _WIN32
  struct offset_windows_file_manager* file_manager;
  if (!offset_windows_file_manager_alloc(&file_manager)) {
    return false;
  }

  if (!offset_windows_file_manager_ctor(file_manager, filename, (mem_size_t){.value = page_size})) {
    free(file_manager);
    return false;
  }

  if (!internal_element_storage_ctor(storage, (struct offset_memory_manager*)file_manager,
                                     (mem_size_t){.value = page_size})) {
    offset_windows_file_manager_dtor(file_manager);
    free(file_manager);
    return false;
  }

  return true;
#endif /* _WIN32 */
#ifdef __unix__
  struct offset_unix_file_manager* file_manager;
  if (!offset_unix_file_manager_alloc(&file_manager)) {
    return false;
  }

  if (!offset_unix_file_manager_ctor(file_manager, filename, (mem_size_t){.value = page_size})) {
    free(file_manager);
    return false;
  }

  if (!internal_element_storage_ctor(storage, (struct offset_memory_manager*)file_manager,
                                     (mem_size_t){.value = page_size})) {
    offset_unix_file_manager_dtor(file_manager);
    free(file_manager);
    return false;
  }

  return true;
#endif /* __unix__ */
  return false;
}

bool element_storage_read(struct element_storage* storage, const char* filename, size_t page_size) {
#ifdef _WIN32
  struct offset_windows_file_manager* file_manager;
  if (!offset_windows_file_manager_alloc(&file_manager)) {
    return false;
  }

  if (!offset_windows_file_manager_ctor(file_manager, filename, (mem_size_t){.value = page_size})) {
    free(file_manager);
    return false;
  }

  if (!internal_element_storage_ctor_from_place(storage, (struct offset_memory_manager*)file_manager,
                                                (mem_size_t){.value = page_size})) {
    offset_windows_file_manager_dtor(file_manager);
    free(file_manager);
    return false;
  }

  return true;
#endif /* _WIN32 */
#ifdef __unix__
  struct offset_unix_file_manager* file_manager;
  if (!offset_unix_file_manager_alloc(&file_manager)) {
    return false;
  }

  if (!offset_unix_file_manager_ctor(file_manager, filename, (mem_size_t){.value = page_size})) {
    free(file_manager);
    return false;
  }

  if (!internal_element_storage_ctor_from_place(storage, (struct offset_memory_manager*)file_manager,
                                                (mem_size_t){.value = page_size})) {
    offset_unix_file_manager_dtor(file_manager);
    free(file_manager);
    return false;
  }

  return true;
#endif /* __unix__ */
  return false;
}

void element_storage_dtor(struct element_storage* storage) {
#ifdef _WIN32
  struct offset_windows_file_manager* file_manager = (struct offset_windows_file_manager*)storage->mem_manager;
  internal_element_storage_dtor(storage);
  offset_windows_file_manager_dtor(file_manager);
  free(file_manager);
#endif /* _WIN32 */
#ifdef __unix__
  struct offset_unix_file_manager* file_manager = (struct offset_unix_file_manager*)storage->mem_manager;
  internal_element_storage_dtor(storage);
  offset_unix_file_manager_dtor(file_manager);
  free(file_manager);
#endif /* __unix__ */
}

error_code element_storage_add_element_type(struct element_storage* storage, const struct element_type* type,
                                            struct storage_iterator* type_iter) {
  if (!offset_list_push_front(storage->element_types, (mem_size_t){.value = 0}, NULL)) {
    return ERROR_FILE_ALLOC_FAILED;
  }

  bool owns_head = (type_iter == NULL);

  struct offset_list_iterator* head;
  if (owns_head) {
    if (!offset_list_iterator_alloc(&head)) {
      offset_list_pop_front(storage->element_types);
      return ERROR_MEM_ALLOC_FAILED;
    }
  } else {
    head = &type_iter->iter;
  }

  offset_list_head(storage->element_types, head);
  struct internal_element_type internal_type;
  if (!internal_element_type_ctor(&internal_type, offset_list_iterator_get_data_offset(head), type, storage->heap,
                                  storage->page_allocator, (struct offset_memory_manager*)storage->element_io)) {
    if (owns_head) {
      free(head);
    }
    offset_list_pop_front(storage->element_types);
    return ERROR_UNABLE_TO_CREATE_INTERNAL_STRUCT;
  }

  if (owns_head) {
    free(head);
  }

  internal_element_type_dtor(&internal_type);

  return 0;
}

bool element_storage_element_type_list_is_empty(const struct element_storage* storage) {
  return offset_list_empty(storage->element_types);
}

error_code element_storage_get_element_type_iter(const struct element_storage* storage,
                                                 struct storage_iterator* target) {
  if (offset_list_empty(storage->element_types)) {
    return ERROR_LIST_IS_EMPTY;
  }
  offset_list_head(storage->element_types, (struct offset_list_iterator*)target);
  return 0;
}

error_code element_storage_remove_element_type(struct element_storage* storage, struct storage_iterator* type) {
  struct internal_element_type internal_type;
  if (!internal_element_type_ctor_from_place(&internal_type, offset_list_iterator_get_data_offset(&type->iter),
                                             storage->heap, storage->page_allocator,
                                             (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (!offset_list_empty(internal_type.element_list)) {
    internal_element_type_dtor(&internal_type);
    return ERROR_TYPE_IS_NOT_EMPTY;
  }

  internal_element_type_delete(&internal_type);
  offset_list_delete(storage->element_types, &type->iter);

  return 0;
}

error_code element_storage_get_element_type(const struct element_storage* storage, const struct storage_iterator* iter,
                                            struct element_type* target) {
  struct internal_element_type internal_type;
  if (!internal_element_type_ctor_from_place(&internal_type, offset_list_iterator_get_data_offset(&iter->iter),
                                             storage->heap, storage->page_allocator,
                                             (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  bool res = element_type_ctor(target, &internal_type);

  internal_element_type_dtor(&internal_type);
  return res ? 0 : ERROR_MEM_ALLOC_FAILED;
}

error_code element_storage_add_link_type(struct element_storage* storage, const struct link_type* type) {
  if (!offset_list_push_front(storage->link_types, (mem_size_t){.value = 0}, NULL)) {
    return ERROR_FILE_ALLOC_FAILED;
  }

  struct offset_list_iterator* head;
  if (!offset_list_iterator_alloc(&head)) {
    offset_list_pop_front(storage->link_types);
    return ERROR_MEM_ALLOC_FAILED;
  }

  offset_list_head(storage->link_types, head);
  struct internal_link_type internal_type;
  if (!internal_link_type_ctor(&internal_type, offset_list_iterator_get_data_offset(head), type, storage->heap,
                               (struct offset_memory_manager*)storage->element_io)) {
    free(head);
    offset_list_pop_front(storage->link_types);
    return ERROR_UNABLE_TO_CREATE_INTERNAL_STRUCT;
  }

  free(head);
  return 0;
}

bool element_storage_link_type_list_is_empty(const struct element_storage* storage) {
  return offset_list_empty(storage->link_types);
}

error_code element_storage_get_link_type_iter(const struct element_storage* storage, struct storage_iterator* target) {
  if (offset_list_empty(storage->link_types)) {
    return ERROR_LIST_IS_EMPTY;
  }
  offset_list_head(storage->link_types, (struct offset_list_iterator*)target);
  return 0;
}
error_code element_storage_remove_link_type(struct element_storage* storage, struct storage_iterator* type) {
  struct internal_link_type internal_type;
  if (!internal_link_type_ctor_from_place(&internal_type, offset_list_iterator_get_data_offset(&type->iter),
                                          storage->heap, (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  internal_link_type_delete(&internal_type);
  offset_list_delete(storage->link_types, &type->iter);

  return 0;
}

error_code element_storage_get_link_type(const struct element_storage* storage, const struct storage_iterator* iter,
                                         struct link_type* target) {
  struct internal_link_type internal_type;
  if (!internal_link_type_ctor_from_place(&internal_type, offset_list_iterator_get_data_offset(&iter->iter),
                                          storage->heap, (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  bool res = link_type_ctor(target, &internal_type);

  internal_link_type_dtor(&internal_type);
  return res ? 0 : ERROR_MEM_ALLOC_FAILED;
}

error_code element_storage_add_element_of_type(struct element_storage* storage, struct storage_iterator* type_iter,
                                               const struct element* element) {
  mem_offset_t element_type_offset = offset_list_iterator_get_data_offset(&type_iter->iter);

  struct internal_element_type type;
  if (!internal_element_type_ctor_from_place(&type, element_type_offset, storage->heap, storage->page_allocator,
                                             (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (!offset_list_push_front(type.element_list, (mem_size_t){.value = 0}, NULL)) {
    internal_element_type_dtor(&type);
    return ERROR_FILE_ALLOC_FAILED;
  }

  struct offset_list_iterator* head;
  if (!offset_list_iterator_alloc(&head)) {
    offset_list_pop_front(type.element_list);
    internal_element_type_dtor(&type);
    return ERROR_MEM_ALLOC_FAILED;
  }

  offset_list_head(type.element_list, head);
  mem_offset_t element_offset = offset_list_iterator_get_data_offset(head);

  if (!internal_element_create_at(element_offset, element, element_type_offset,
                                  (struct offset_fixed_base_allocator*)storage->link_node_allocator, storage->heap,
                                  (struct offset_memory_manager*)storage->element_io)) {
    free(head);
    offset_list_pop_front(type.element_list);
    internal_element_type_dtor(&type);
    return ERROR_UNABLE_TO_CREATE_INTERNAL_STRUCT;
  }

  free(head);
  internal_element_type_dtor(&type);

  return 0;
}

error_code element_storage_get_element_iter(const struct element_storage* storage,
                                            const struct storage_iterator* type_iter, struct storage_iterator* target) {
  mem_offset_t element_type_offset = offset_list_iterator_get_data_offset(&type_iter->iter);

  struct internal_element_type type;
  if (!internal_element_type_ctor_from_place(&type, element_type_offset, storage->heap, storage->page_allocator,
                                             (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (offset_list_empty(type.element_list)) {
    internal_element_type_dtor(&type);
    return ERROR_LIST_IS_EMPTY;
  }

  offset_list_head(type.element_list, &target->iter);

  internal_element_type_dtor(&type);
  return 0;
}

error_code element_storage_remove_element(struct element_storage* storage, struct storage_iterator* type_iter,
                                          struct storage_iterator* element_iter) {
  mem_offset_t element_type_offset = offset_list_iterator_get_data_offset(&type_iter->iter);
  mem_offset_t element_offset = offset_list_iterator_get_data_offset(&element_iter->iter);

  struct internal_element_type type;
  if (!internal_element_type_ctor_from_place(&type, element_type_offset, storage->heap, storage->page_allocator,
                                             (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  struct internal_element element;
  if (!internal_element_ctor_from_place(&element, element_offset,
                                        (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                        storage->heap, (struct offset_memory_manager*)storage->element_io)) {
    internal_element_type_dtor(&type);
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (!internal_element_delete(&element)) {
    internal_element_dtor(&element);
    internal_element_type_dtor(&type);
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  offset_list_delete(type.element_list, &element_iter->iter);

  internal_element_type_dtor(&type);
  return 0;
}

error_code element_storage_get_element(const struct element_storage* storage,
                                       const struct storage_iterator* element_iter, struct element* target) {
  mem_offset_t element_offset = offset_list_iterator_get_data_offset(&element_iter->iter);

  struct internal_element element;
  if (!internal_element_ctor_from_place(&element, element_offset,
                                        (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                        storage->heap, (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (!element_ctor(target, &element, storage->page_allocator, (struct offset_memory_manager*)storage->element_io)) {
    internal_element_dtor(&element);
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  internal_element_dtor(&element);
  return 0;
}

error_code element_storage_get_element_attrs(const struct element_storage* storage,
                                             const struct storage_iterator* element_iter, struct element* target) {
  mem_offset_t element_offset = offset_list_iterator_get_data_offset(&element_iter->iter);

  struct internal_element internal_element;
  if (!internal_element_ctor_from_place(&internal_element, element_offset,
                                        (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                        storage->heap, (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  target->attribute_count = internal_element.attrs_count;
  target->attributes = internal_element.attrs;
  internal_element.attrs = NULL;

  internal_element_dtor(&internal_element);

  return 0;
}

error_code element_storage_rewrite_element_attrs(struct element_storage* storage, struct storage_iterator* element_iter,
                                                 const struct attribute* attrs, attribute_count_t attribute_count) {
  if (internal_element_rewrite_attrs_at(offset_list_iterator_get_data_offset(&element_iter->iter), attrs,
                                        attribute_count, storage->heap,
                                        (struct offset_memory_manager*)storage->element_io)) {
    return 0;
  }
  return ERROR_UNABLE_TO_CREATE_INTERNAL_STRUCT;
}

error_code element_storage_get_element_links_out_iter(const struct element_storage* storage,
                                                      const struct storage_iterator* element_iter,
                                                      struct storage_iterator* target) {
  mem_offset_t element_offset = offset_list_iterator_get_data_offset(&element_iter->iter);

  struct offset_list* list;
  if (!offset_list_alloc(&list)) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  if (!internal_element_links_out_ctor_from_place(list, element_offset,
                                                  (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                                  (struct offset_memory_manager*)storage->element_io)) {
    free(list);
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (offset_list_empty(list)) {
    internal_element_links_dtor(list);
    free(list);
    return ERROR_LIST_IS_EMPTY;
  }

  offset_list_head(list, &target->iter);

  internal_element_links_dtor(list);
  free(list);

  return 0;
}
error_code element_storage_get_element_links_in_iter(const struct element_storage* storage,
                                                     const struct storage_iterator* element_iter,
                                                     struct storage_iterator* target) {
  mem_offset_t element_offset = offset_list_iterator_get_data_offset(&element_iter->iter);

  struct offset_list* list;
  if (!offset_list_alloc(&list)) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  if (!internal_element_links_in_ctor_from_place(list, element_offset,
                                                 (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                                 (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (offset_list_empty(list)) {
    internal_element_links_dtor(list);
    free(list);
    return ERROR_LIST_IS_EMPTY;
  }

  offset_list_head(list, &target->iter);

  internal_element_links_dtor(list);
  free(list);

  return 0;
}

error_code element_storage_get_type_of_link(const struct element_storage* storage,
                                            const struct storage_iterator* link_iter, link_type_id_t* type_id) {
  mem_offset_t link_offset = offset_list_iterator_get_data_offset(&link_iter->iter);

  offset_memory_manager_read((struct offset_memory_manager*)storage->element_io,
                             ADD_TO_OFFSET(link_offset, offsetof(struct internal_link, type_id)),
                             (mem_size_t){.value = sizeof(link_type_id_t)}, type_id);
  return 0;
}

error_code element_storage_get_type_of_link_dst_element(const struct element_storage* storage,
                                                        const struct storage_iterator* link_iter,
                                                        element_type_id_t* target) {
  mem_offset_t link_offset = offset_list_iterator_get_data_offset(&link_iter->iter);
  mem_offset_t element_node_offset;

  offset_memory_manager_read((struct offset_memory_manager*)storage->element_io,
                             ADD_TO_OFFSET(link_offset, offsetof(struct internal_link, target_node)),
                             (mem_size_t){.value = sizeof(mem_offset_t)}, &element_node_offset);

  mem_offset_t element_offset = offset_list_iterator_get_data_offset_from_node_offset(element_node_offset);

  offset_memory_manager_read((struct offset_memory_manager*)storage->element_io,
                             ADD_TO_OFFSET(element_offset, offsetof(struct internal_element, type_id)),
                             (mem_size_t){.value = sizeof(element_type_id_t)}, target);

  return 0;
}

error_code element_storage_get_link_dst_element_iter(const struct element_storage* storage,
                                                     const struct storage_iterator* link_iter,
                                                     struct storage_iterator* element_iter) {
  mem_offset_t link_offset = offset_list_iterator_get_data_offset(&link_iter->iter);
  mem_offset_t element_node_offset;

  offset_memory_manager_read((struct offset_memory_manager*)storage->element_io,
                             ADD_TO_OFFSET(link_offset, offsetof(struct internal_link, target_node)),
                             (mem_size_t){.value = sizeof(mem_offset_t)}, &element_node_offset);

  if (!offset_list_iterator_ctor_from_place(&element_iter->iter, element_node_offset,
                                            (struct offset_memory_manager*)storage->element_io)) {
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  return 0;
}

error_code element_storage_add_link(struct element_storage* storage, struct storage_iterator* src_element_iter,
                                    struct storage_iterator* dst_element_iter, link_type_id_t link_type) {
  mem_offset_t src_offset = offset_list_iterator_get_data_offset(&src_element_iter->iter);
  mem_offset_t dst_offset = offset_list_iterator_get_data_offset(&dst_element_iter->iter);

  struct offset_list* links_out;
  if (!offset_list_alloc(&links_out)) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  struct offset_list* links_in;
  if (!offset_list_alloc(&links_in)) {
    free(links_out);
    return ERROR_MEM_ALLOC_FAILED;
  }

  if (!internal_element_links_out_ctor_from_place(links_out, src_offset,
                                                  (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                                  (struct offset_memory_manager*)storage->element_io)) {
    free(links_in);
    free(links_out);
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }
  if (!internal_element_links_in_ctor_from_place(links_in, dst_offset,
                                                 (struct offset_fixed_base_allocator*)storage->link_node_allocator,
                                                 (struct offset_memory_manager*)storage->element_io)) {
    internal_element_links_dtor(links_out);
    free(links_in);
    free(links_out);
    return ERROR_UNABLE_TO_READ_INTERNAL_STRUCT;
  }

  if (!offset_list_push_front(links_in, (mem_size_t){.value = 0}, NULL)) {
    internal_element_links_dtor(links_in);
    internal_element_links_dtor(links_out);
    free(links_in);
    free(links_out);
    return ERROR_FILE_ALLOC_FAILED;
  }
  if (!offset_list_push_front(links_out, (mem_size_t){.value = 0}, NULL)) {
    offset_list_pop_front(links_in);
    internal_element_links_dtor(links_in);
    internal_element_links_dtor(links_out);
    free(links_in);
    free(links_out);
    return ERROR_FILE_ALLOC_FAILED;
  }

  struct offset_list_iterator* iter_out = NULL;
  struct offset_list_iterator* iter_in = NULL;
  if (!offset_list_iterator_alloc(&iter_out) || !offset_list_iterator_alloc(&iter_in)) {
    free(iter_out);
    free(iter_in);
    offset_list_pop_front(links_out);
    offset_list_pop_front(links_in);
    internal_element_links_dtor(links_in);
    internal_element_links_dtor(links_out);
    free(links_in);
    free(links_out);
    return ERROR_MEM_ALLOC_FAILED;
  }

  offset_list_head(links_out, iter_out);
  offset_list_head(links_in, iter_in);

  mem_offset_t out_offset = offset_list_iterator_get_node_offset(iter_out);
  mem_offset_t in_offset = offset_list_iterator_get_node_offset(iter_in);

  struct internal_link link_in = {.target_node = offset_list_iterator_get_node_offset(&src_element_iter->iter),
                                  .type_id = link_type,
                                  .chained_link_node = out_offset};
  struct internal_link link_out = {.target_node = offset_list_iterator_get_node_offset(&dst_element_iter->iter),
                                   .type_id = link_type,
                                   .chained_link_node = in_offset};

  offset_memory_manager_write((struct offset_memory_manager*)storage->element_io,
                              offset_list_iterator_get_data_offset_from_node_offset(in_offset),
                              (mem_size_t){.value = sizeof(struct internal_link)}, &link_in);

  offset_memory_manager_write((struct offset_memory_manager*)storage->element_io,
                              offset_list_iterator_get_data_offset_from_node_offset(out_offset),
                              (mem_size_t){.value = sizeof(struct internal_link)}, &link_out);

  free(iter_out);
  free(iter_in);
  internal_element_links_dtor(links_in);
  internal_element_links_dtor(links_out);
  free(links_in);
  free(links_out);

  return 0;
}
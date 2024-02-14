#include "query_processor.h"

#include <stdlib.h>
#include <string.h>

static bool match_attrs(struct attribute* attrs, struct attribute_pattern* pattern) {
  if (pattern == NULL) {
    return true;
  }
  switch (pattern->node_type) {
    case ATTRIBUTE_PATTERN_BIN_OP:
      switch (pattern->args.as_bin.op_type) {
        case ATTRIBUTE_PATTERN_AND:
          return (match_attrs(attrs, pattern->args.as_bin.lhs) && match_attrs(attrs, pattern->args.as_bin.rhs));
        case ATTRIBUTE_PATTERN_OR:
          return (match_attrs(attrs, pattern->args.as_bin.lhs) || match_attrs(attrs, pattern->args.as_bin.rhs));
        default:
          return false;
      }
      break;
    case ATTRIBUTE_PATTERN_UN_OP:
      switch (pattern->args.as_unary.op_type) {
        case ATTRIBUTE_PATTERN_NOT:
          return !match_attrs(attrs, pattern->args.as_unary.arg);
        default:
          return false;
      }
      break;
    case ATTRIBUTE_PATTERN_COND:
      switch (pattern->args.as_cond.cond) {
        case ATTRIBUTE_PATTERN_COND_EQ:
          switch (attrs[pattern->args.as_cond.attr_id].type) {
            case ATTR_TYPE_BOOL:
              return pattern->args.as_cond.attr.value.as_bool == attrs[pattern->args.as_cond.attr_id].value.as_bool;
            case ATTR_TYPE_DOUBLE:
              return pattern->args.as_cond.attr.value.as_double == attrs[pattern->args.as_cond.attr_id].value.as_double;
            case ATTR_TYPE_INT32:
              return pattern->args.as_cond.attr.value.as_int32 == attrs[pattern->args.as_cond.attr_id].value.as_int32;
            case ATTR_TYPE_INT64:
              return pattern->args.as_cond.attr.value.as_int64 == attrs[pattern->args.as_cond.attr_id].value.as_int64;
            case ATTR_TYPE_STRING:
              return (strcmp(pattern->args.as_cond.attr.value.as_string.data,
                             attrs[pattern->args.as_cond.attr_id].value.as_string.data) == 0);
            default:
              return false;
          }
          break;
        case ATTRIBUTE_PATTERN_COND_LESS:
          switch (attrs[pattern->args.as_cond.attr_id].type) {
            case ATTR_TYPE_BOOL:
              return pattern->args.as_cond.attr.value.as_bool > attrs[pattern->args.as_cond.attr_id].value.as_bool;
            case ATTR_TYPE_DOUBLE:
              return pattern->args.as_cond.attr.value.as_double > attrs[pattern->args.as_cond.attr_id].value.as_double;
            case ATTR_TYPE_INT32:
              return pattern->args.as_cond.attr.value.as_int32 > attrs[pattern->args.as_cond.attr_id].value.as_int32;
            case ATTR_TYPE_INT64:
              return pattern->args.as_cond.attr.value.as_int64 > attrs[pattern->args.as_cond.attr_id].value.as_int64;
            default:
              return false;
          }
          break;
        case ATTRIBUTE_PATTERN_COND_GREATER:
          switch (attrs[pattern->args.as_cond.attr_id].type) {
            case ATTR_TYPE_BOOL:
              return pattern->args.as_cond.attr.value.as_bool < attrs[pattern->args.as_cond.attr_id].value.as_bool;
            case ATTR_TYPE_DOUBLE:
              return pattern->args.as_cond.attr.value.as_double < attrs[pattern->args.as_cond.attr_id].value.as_double;
            case ATTR_TYPE_INT32:
              return pattern->args.as_cond.attr.value.as_int32 < attrs[pattern->args.as_cond.attr_id].value.as_int32;
            case ATTR_TYPE_INT64:
              return pattern->args.as_cond.attr.value.as_int64 < attrs[pattern->args.as_cond.attr_id].value.as_int64;
            default:
              return false;
          }
          break;
        case ATTRIBUTE_PATTERN_COND_CONTAINS:
          if (attrs[pattern->args.as_cond.attr_id].type == ATTR_TYPE_STRING) {
            return (strstr(attrs[pattern->args.as_cond.attr_id].value.as_string.data,
                           pattern->args.as_cond.attr.value.as_string.data) != NULL);
          }
          return false;
        default:
          return false;
      }
    default:
      return false;
  }
  return false;
}

static error_code match_pattern(struct storage_iterator* element_iterator, struct element_pattern* pattern,
                                struct element_storage* storage, bool* match);

static bool check_next_link(struct storage_iterator* head_iterator, struct storage_iterator* link_iterator,
                            struct element_storage* storage, struct link_pattern* link_pattern, link_count_t link_count,
                            link_count_t link_idx, error_code* error) {
  if (link_idx >= link_count) {
    *error = 0;
    return true;
  }

  if (link_pattern[link_idx].target->idx > 0) {
    return check_next_link(head_iterator, link_iterator, storage, link_pattern, link_count, link_idx + 1, error);
  }

  struct storage_iterator* element_iter;
  if (!storage_iterator_alloc(&element_iter)) {
    *error = ERROR_MEM_ALLOC_FAILED;
    return false;
  }

  do {
    link_type_id_t link_type;
    *error = element_storage_get_type_of_link(storage, link_iterator, &link_type);

    if (*error == 0 && link_type == link_pattern[link_idx].link_type->type_id) {
      element_type_id_t element_type;
      *error = element_storage_get_type_of_link_dst_element(storage, link_iterator, &element_type);
      if (*error == 0 && element_type == link_pattern[link_idx].target->element_type->type_id) {
        *error = element_storage_get_link_dst_element_iter(storage, link_iterator, element_iter);

        if (*error == 0) {
          bool match = false;
          *error = match_pattern(element_iter, link_pattern[link_idx].target, storage, &match);

          if (*error == 0 && match) {
            free(element_iter);
            storage_iterator_next(link_iterator);
            storage_iterator_copy(link_iterator, head_iterator);
            return check_next_link(head_iterator, link_iterator, storage, link_pattern, link_count, link_idx + 1,
                                   error);
          }
        }
      }
    }

    if (*error != 0) {
      break;
    }

    storage_iterator_next(link_iterator);
  } while (!storage_iterator_equals(head_iterator, link_iterator));

  free(element_iter);
  return false;
}

static error_code match_links(struct storage_iterator* link_iterator, struct link_pattern* link_pattern,
                              link_count_t link_count, struct element_storage* storage, bool* match) {
  if (link_count == 0) {
    *match = true;
    return 0;
  }

  struct storage_iterator* head_iterator;
  if (!storage_iterator_alloc(&head_iterator)) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  storage_iterator_copy(link_iterator, head_iterator);

  error_code error;
  *match = check_next_link(head_iterator, link_iterator, storage, link_pattern, link_count, 0, &error);

  free(head_iterator);
  return error;
}

// If an error, then failed. If no error, then look at match
static error_code match_pattern(struct storage_iterator* element_iterator, struct element_pattern* pattern,
                                struct element_storage* storage, bool* match) {
  // check attributes
  struct element attrs_holder = {0};

  error_code error = element_storage_get_element_attrs(storage, element_iterator, &attrs_holder);

  if (error != 0) {
    return error;
  }

  if (match_attrs(attrs_holder.attributes, pattern->attr_pattern)) {
    // check links
    pattern->idx++;
    struct storage_iterator* link_iterator;
    if (storage_iterator_alloc(&link_iterator)) {
      if (pattern->links_in_cnt > 0) {
        error = element_storage_get_element_links_in_iter(storage, element_iterator, link_iterator);
      }
      if (error == 0) {
        error = match_links(link_iterator, pattern->links_in, pattern->links_in_cnt, storage, match);
        if (error == 0 && *match) {
          if (pattern->links_out_cnt > 0) {
            error = element_storage_get_element_links_out_iter(storage, element_iterator, link_iterator);
          }
          if (error == 0) {
            error = match_links(link_iterator, pattern->links_out, pattern->links_out_cnt, storage, match);
          }
        }
      }
      if (error == ERROR_LIST_IS_EMPTY) {
        error = 0;
        *match = false;
      }
    } else {
      error = ERROR_MEM_ALLOC_FAILED;
    }
    pattern->idx--;
    free(link_iterator);
  }

  element_dtor(&attrs_holder);
  return error;
}

struct query_result {
  struct storage_iterator* head_iter;
  struct storage_iterator* element_iter;
  struct element_pattern* pattern;
  struct element_storage* storage;
};

bool query_result_alloc(struct query_result** ptr) {
  *ptr = malloc(sizeof(struct query_result));
  return (*ptr != NULL);
}

static error_code query_result_ctor(struct query_result* q_res, struct storage_iterator* head_iter,
                                    struct element_pattern* pattern, struct element_storage* storage) {
  storage_iterator_alloc(&q_res->element_iter);
  storage_iterator_alloc(&q_res->head_iter);

  if (q_res->element_iter == NULL || q_res->head_iter == NULL) {
    free(q_res->element_iter);
    free(q_res->head_iter);
    return ERROR_MEM_ALLOC_FAILED;
  }

  storage_iterator_copy(head_iter, q_res->head_iter);
  storage_iterator_copy(q_res->head_iter, q_res->element_iter);

  q_res->pattern = pattern;
  q_res->storage = storage;

  return query_result_reset(q_res);
}

void query_result_dtor(struct query_result* res) {
  free(res->head_iter);
  free(res->element_iter);
}

error_code query_result_next(struct query_result* res) {
  storage_iterator_next(res->element_iter);

  while (!storage_iterator_equals(res->element_iter, res->head_iter)) {
    bool match = false;
    error_code error = match_pattern(res->element_iter, res->pattern, res->storage, &match);

    if (error != 0) {
      return error;
    }

    if (match) {
      return 0;
    }

    storage_iterator_next(res->element_iter);
  }
  return ERROR_HAS_NO_NEXT_ELEMENT;
}

error_code query_result_reset(struct query_result* res) {
  storage_iterator_copy(res->element_iter, res->head_iter);
  bool match = false;
  error_code error = match_pattern(res->element_iter, res->pattern, res->storage, &match);

  if (error != 0) {
    free(res->element_iter);
    free(res->head_iter);
    return error;
  }

  if (match) {
    return 0;
  }

  return query_result_next(res);
}

static bool alloc_and_copy_element_type(struct element_type* src, struct element_type** dst) {
  *dst = malloc(sizeof(struct element_type));
  if (*dst == NULL) {
    return false;
  }

  **dst = *src;

  size_t name_size = strlen(src->type_name) + 1;
  (*dst)->type_name = malloc(name_size);
  size_t attrs_size = sizeof(enum ATTRIBUTE_TYPE) * src->attribute_count;
  (*dst)->attribute_types = malloc(attrs_size);

  if ((*dst)->type_name != NULL && (*dst)->attribute_types != NULL) {
    strcpy((*dst)->type_name, src->type_name);
    memcpy((*dst)->attribute_types, src->attribute_types, attrs_size);
    return true;
  }

  free((*dst)->type_name);
  free((*dst)->attribute_types);
  free(*dst);

  *dst = NULL;
  return false;
}

error_code query_result_get_data(struct query_result* res, struct element** target) {
  *target = calloc(1, sizeof(struct element));
  if (*target == NULL) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  error_code error = element_storage_get_element_attrs(res->storage, res->element_iter, *target);

  if (error == 0) {
    (*target)->owns_type_ptr = true;
    if (alloc_and_copy_element_type(res->pattern->element_type, &((*target)->element_type))) {
      return 0;
    } else {
      error = ERROR_MEM_ALLOC_FAILED;
    }
  }

  element_dtor(*target);
  free(*target);

  return error;
}

static error_code find_element_type(struct element_storage* storage, struct storage_iterator* res,
                                    element_type_id_t type_id) {
  struct storage_iterator* head_type_iter;
  storage_iterator_alloc(&head_type_iter);

  if (head_type_iter == NULL) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  error_code error = element_storage_get_element_type_iter(storage, head_type_iter);
  if (error != 0) {
    free(head_type_iter);
    return error;
  }
  storage_iterator_copy(head_type_iter, res);

  do {
    struct element_type type;
    error_code error = element_storage_get_element_type(storage, res, &type);
    if (error != 0) {
      free(head_type_iter);
      return error;
    }

    if (type.type_id == type_id) {
      element_type_dtor(&type);
      free(head_type_iter);
      return 0;
    }

    element_type_dtor(&type);
    storage_iterator_next(res);
  } while (!storage_iterator_equals(res, head_type_iter));

  free(head_type_iter);
  return ERROR_NO_SUCH_TYPE;
}

static error_code allocate_and_find_element_type(struct element_storage* storage, element_type_id_t type_id,
                                                 struct storage_iterator** res) {
  if (!storage_iterator_alloc(res)) {
    return ERROR_MEM_ALLOC_FAILED;
  }

  error_code error = find_element_type(storage, *res, type_id);

  if (error != 0) {
    free(*res);
  }

  return error;
}

static error_code match_query(struct element_storage* storage, struct element_pattern* pattern,
                              struct query_result* res, struct storage_iterator** type_iter_res) {
  struct storage_iterator* type_iter;

  error_code error = allocate_and_find_element_type(storage, pattern->element_type->type_id, &type_iter);

  if (error != 0) {
    return error;
  }

  struct storage_iterator* element_iter;
  if (type_iter_res != NULL) {
    *type_iter_res = type_iter;
    if (!storage_iterator_alloc(&element_iter)) {
      error = ERROR_MEM_ALLOC_FAILED;
    }
  } else {
    element_iter = type_iter;
  }

  if (error == 0) {
    error = element_storage_get_element_iter(storage, type_iter, element_iter);
  }

  if (error == 0) {
    error = query_result_ctor(res, element_iter, pattern, storage);
  } else {
    *res = (struct query_result){0};
  }

  if (error == ERROR_LIST_IS_EMPTY) {
    error = ERROR_HAS_NO_NEXT_ELEMENT;
  }

  if (type_iter_res != NULL) {
    free(element_iter);
  } else {
    free(type_iter);
  }

  return error;
}

error_code process_query(struct element_storage* storage, struct query* query, struct query_result* res) {
  error_code error;
  struct storage_iterator* type_iter;

  switch (query->type) {
    case QUERY_TYPE_CREATE_VERTEX_TYPE:
      return element_storage_add_element_type(storage, query->args.as_create_vertex_type.type, NULL);
    case QUERY_TYPE_CREATE_EDGE_TYPE:
      return element_storage_add_link_type(storage, query->args.as_create_edge_type.type);
    case QUERY_TYPE_DROP_VERTEX_TYPE: {
      storage_iterator_alloc(&type_iter);
      element_storage_get_element_type_iter(storage, type_iter);

      struct storage_iterator* start_iter;
      storage_iterator_alloc(&start_iter);

      storage_iterator_copy(type_iter, start_iter);

      struct element_type type;
      do {
        element_type_dtor(&type);

        element_storage_get_element_type(storage, type_iter, &type);

        storage_iterator_next(type_iter);
      } while (!storage_iterator_equals(type_iter, start_iter) &&
               (strcmp(type.type_name, query->args.as_drop_vertex_type.type_name) != 0));

      error_code err;
      if (strcmp(type.type_name, query->args.as_drop_vertex_type.type_name) == 0) {
        err = element_storage_remove_element_type(storage, type_iter);
      } else {
        err = ERROR_NO_SUCH_TYPE;
      }

      free(type_iter);
      free(start_iter);
      element_type_dtor(&type);

      return err;
    }
    case QUERY_TYPE_DROP_EDGE_TYPE: {
      storage_iterator_alloc(&type_iter);
      element_storage_get_link_type_iter(storage, type_iter);

      struct storage_iterator* start_iter;
      storage_iterator_alloc(&start_iter);

      storage_iterator_copy(type_iter, start_iter);

      struct link_type type;
      do {
        link_type_dtor(&type);

        element_storage_get_link_type(storage, type_iter, &type);

        storage_iterator_next(type_iter);
      } while (!storage_iterator_equals(type_iter, start_iter) &&
               (strcmp(type.type_name, query->args.as_drop_edge_type.type_name) != 0));

      error_code err;
      if (strcmp(type.type_name, query->args.as_drop_edge_type.type_name) == 0) {
        err = element_storage_remove_link_type(storage, type_iter);
      } else {
        err = ERROR_NO_SUCH_TYPE;
      }

      free(type_iter);
      free(start_iter);
      link_type_dtor(&type);

      return err;
    }
    case QUERY_TYPE_MATCH:
      return match_query(storage, query->args.as_match.pattern, res, NULL);
    case QUERY_TYPE_CREATE:;
      error_code error =
          allocate_and_find_element_type(storage, query->args.as_create.element->element_type->type_id, &type_iter);

      if (error != 0) {
        return error;
      }

      if (error == 0) {
        error = element_storage_add_element_of_type(storage, type_iter, query->args.as_create.element);
      }

      free(type_iter);
      return error;
    case QUERY_TYPE_DELETE:;
      struct storage_iterator* delete_iterator;
      if (!storage_iterator_alloc(&delete_iterator)) {
        return ERROR_MEM_ALLOC_FAILED;
      }

      struct query_result node_to_delete;
      error = match_query(storage, query->args.as_delete.pattern, &node_to_delete, &type_iter);

      if (error != 0) {
        free(delete_iterator);
        return error;
      }

      while (error == 0) {
        storage_iterator_copy(node_to_delete.element_iter, delete_iterator);

        error_code error_next = query_result_next(&node_to_delete);
        storage_iterator_copy(node_to_delete.element_iter, node_to_delete.head_iter);
        if (error_next == 0 || error_next == ERROR_HAS_NO_NEXT_ELEMENT) {
          error = element_storage_remove_element(storage, type_iter, delete_iterator);

          if (error == 0) {
            error = error_next;
          }
        }
      }

      free(type_iter);
      query_result_dtor(&node_to_delete);
      free(delete_iterator);
      if (error == ERROR_HAS_NO_NEXT_ELEMENT) {
        return 0;
      }
      return error;
    case QUERY_TYPE_LINK:;
      struct query_result src;
      struct query_result dst;

      error = match_query(storage, query->args.as_link.source_pattern, &src, NULL);
      if (error == 0) {
        error = match_query(storage, query->args.as_link.dst_pattern, &dst, NULL);
      }

      if (error != 0) {
        if (error == ERROR_HAS_NO_NEXT_ELEMENT) {
          return 0;
        }
        return error;
      }

      do {
        do {
          error = element_storage_add_link(storage, src.element_iter, dst.element_iter,
                                           query->args.as_link.link_type->type_id);
          if (error == 0) {
            error = query_result_next(&dst);
          }
        } while (error == 0);
        if (error == ERROR_HAS_NO_NEXT_ELEMENT) {
          error = query_result_reset(&dst);
          if (error == 0) {
            error = query_result_next(&src);
          }
        }
      } while (error == 0);

      query_result_dtor(&src);
      query_result_dtor(&dst);

      if (error == ERROR_HAS_NO_NEXT_ELEMENT) {
        return 0;
      }
      return error;
    case QUERY_TYPE_SET:;
      struct query_result node_to_update;

      error = match_query(storage, query->args.as_set.pattern, &node_to_update, NULL);

      while (error == 0) {
        struct element attrs_holder = {0};
        error = element_storage_get_element_attrs(storage, node_to_update.element_iter, &attrs_holder);

        for (attribute_count_t i = 0; i < query->args.as_set.attributes_count; i++) {
          attribute_count_t attr_id = query->args.as_set.attributes[i].attribute_id;
          struct attribute attr = query->args.as_set.attributes[i].attribute;
          switch (attrs_holder.attributes[attr_id].type) {
            case ATTR_TYPE_BOOL:
              attrs_holder.attributes[attr_id].value.as_bool = attr.value.as_bool;
              break;
            case ATTR_TYPE_DOUBLE:
              if (attr.type == ATTR_TYPE_INT64) {
                attrs_holder.attributes[attr_id].value.as_double = attr.value.as_int64;
              } else {
                attrs_holder.attributes[attr_id].value.as_double = attr.value.as_double;
              }
              break;
            case ATTR_TYPE_INT32:
              attrs_holder.attributes[attr_id].value.as_int32 = attr.value.as_int32;
              break;
            case ATTR_TYPE_INT64:
              attrs_holder.attributes[attr_id].value.as_int64 = attr.value.as_int64;
              break;
            case ATTR_TYPE_STRING:
              free(attrs_holder.attributes[attr_id].value.as_string.data);
              size_t size = strlen(attr.value.as_string.data) + 1;

              attrs_holder.attributes[attr_id].value.as_string.data = malloc(size);
              if (attrs_holder.attributes[attr_id].value.as_string.data == NULL) {
                error = ERROR_MEM_ALLOC_FAILED;
              } else {
                strcpy(attrs_holder.attributes[attr_id].value.as_string.data, attr.value.as_string.data);
              }
              break;
            default:
              error = ERROR_NO_SUCH_TYPE;
              break;
          }
          if (error != 0) {
            break;
          }
        }

        if (error == 0) {
          error = element_storage_rewrite_element_attrs(storage, node_to_update.element_iter, attrs_holder.attributes,
                                                        attrs_holder.attribute_count);
          if (error == 0) {
            error = query_result_next(&node_to_update);
          }
        }
        element_dtor(&attrs_holder);
      }

      query_result_dtor(&node_to_update);

      if (error == ERROR_HAS_NO_NEXT_ELEMENT) {
        return 0;
      }
      return error;
    default:
      return ERROR_UNKNOWN_QUERY_TYPE;
  }
  return ERROR_UNKNOWN_QUERY_TYPE;
}
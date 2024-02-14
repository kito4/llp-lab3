#include "offset_list.h"
#include "offset_list_iterator.h"

#include <stddef.h>
#include <stdlib.h>

bool offset_list_alloc(struct offset_list** ptr) {
  if (!ptr) {
    return false;
  }
  *ptr = malloc(sizeof(struct offset_list));
  return (*ptr != NULL);
}

static mem_size_t offset_list_get_data_block_size(struct offset_list* list) {
  if (!list || !list->allocator) {
    return (mem_size_t){0};
  }
  return (mem_size_t){offset_fixed_base_allocator_get_alloc_size(list->allocator).value -
                      sizeof(struct offset_list_node_header)};
}

mem_size_t offset_list_get_node_size(mem_size_t data_size) {
  return (mem_size_t){data_size.value + sizeof(struct offset_list_node_header)};
}

bool offset_list_ctor(struct offset_list* list, mem_offset_t place, struct offset_memory_manager* mem_manager,
                      struct offset_fixed_base_allocator* allocator) {
  list->mem_manager = mem_manager;
  list->allocator = allocator;
  list->self_offset = place;
  list->head = MEM_NULL_OFFSET;

  struct offset_list_data data = {.head = MEM_NULL_OFFSET};
  offset_memory_manager_write(mem_manager, place, (mem_size_t){sizeof(struct offset_list_data)}, &data);

  return true;
}
void offset_list_dtor(struct offset_list* list) {
  offset_memory_manager_write(list->mem_manager,
                              ADD_TO_OFFSET(list->self_offset, offsetof(struct offset_list_data, head)),
                              (mem_size_t){sizeof(mem_offset_t)}, &list->head);
}

void offset_list_get_allocator(struct offset_list* list, struct offset_fixed_base_allocator** allocator) {
  *allocator = list->allocator;
}

mem_size_t offset_list_get_data_size() {
  return (mem_size_t){sizeof(struct offset_list_data)};
}

bool offset_list_ctor_from_place(struct offset_list* list, mem_offset_t place,
                                 struct offset_memory_manager* mem_manager,
                                 struct offset_fixed_base_allocator* allocator) {
  list->mem_manager = mem_manager;
  list->allocator = allocator;
  list->self_offset = place;

  struct offset_list_data data;
  offset_memory_manager_read(mem_manager, place, (mem_size_t){sizeof(struct offset_list_data)}, &data);

  list->head = data.head;

  return true;
}

void offset_list_head(struct offset_list* list, struct offset_list_iterator* target) {
  offset_list_iterator_ctor_from_place(target, list->head, list->mem_manager);
}

void offset_list_tail(struct offset_list* list, struct offset_list_iterator* target) {
  offset_list_head(list, target);
  offset_list_iterator_prev(target);
}

bool offset_list_empty(const struct offset_list* list) {
  return IS_EQUAL_OFFSET(list->head, MEM_NULL_OFFSET);
}

void offset_list_push_back_inplace(struct offset_list* list, mem_offset_t place, mem_size_t buffer_size,
                                   const void* buffer) {
  mem_offset_t node_offset = place;
  struct offset_list_node_header header;

  if (IS_EQUAL_OFFSET(list->head, MEM_NULL_OFFSET)) {
    list->head = node_offset;

    header.next = list->head;
    header.prev = list->head;
  } else {
    struct offset_list_iterator tail;
    offset_list_head(list, &tail);

    struct offset_list_iterator head = tail;
    offset_list_iterator_prev(&tail);

    header.next = head.current;
    header.prev = tail.current;

    offset_memory_manager_write(list->mem_manager,
                                ADD_TO_OFFSET(header.next, offsetof(struct offset_list_node_header, prev)),
                                (mem_size_t){sizeof(mem_offset_t)}, &node_offset);

    offset_memory_manager_write(list->mem_manager,
                                ADD_TO_OFFSET(header.prev, offsetof(struct offset_list_node_header, next)),
                                (mem_size_t){sizeof(mem_offset_t)}, &node_offset);
  }

  offset_memory_manager_write(list->mem_manager, node_offset, (mem_size_t){sizeof(header)}, &header);
  if (buffer_size.value != 0) {
    offset_memory_manager_write(list->mem_manager, ADD_TO_OFFSET(node_offset, sizeof(header)), buffer_size, buffer);
  }
}

void offset_list_push_front_inplace(struct offset_list* list, mem_offset_t place, mem_size_t buffer_size,
                                    const void* buffer) {
  offset_list_push_back_inplace(list, place, buffer_size, buffer);
  list->head = place;
}

bool offset_list_push_back(struct offset_list* list, mem_size_t buffer_size, const void* buffer) {
  mem_offset_t node_offset = offset_fixed_base_allocator_allocate(list->allocator);
  if (IS_EQUAL_OFFSET(node_offset, MEM_NULL_OFFSET)) {
    return false;
  }
  offset_list_push_back_inplace(list, node_offset, buffer_size, buffer);
  return true;
}

bool offset_list_push_front(struct offset_list* list, mem_size_t buffer_size, const void* buffer) {
  mem_offset_t node_offset = offset_fixed_base_allocator_allocate(list->allocator);
  if (IS_EQUAL_OFFSET(node_offset, MEM_NULL_OFFSET)) {
    return false;
  }
  offset_list_push_back_inplace(list, node_offset, buffer_size, buffer);
  list->head = node_offset;
  return true;
}

void offset_list_delete(struct offset_list* list, struct offset_list_iterator* node) {
  mem_offset_t to_free = node->current;

  struct offset_list_node_header header;
  offset_memory_manager_read(node->mem_manager, node->current, (mem_size_t){sizeof(struct offset_list_node_header)},
                             &header);

  mem_offset_t next_offset = header.next;
  mem_offset_t prev_offset = header.prev;

  if (IS_EQUAL_OFFSET(list->head, to_free)) {
    if (IS_EQUAL_OFFSET(next_offset, list->head)) {
      next_offset = MEM_NULL_OFFSET;
      prev_offset = MEM_NULL_OFFSET;
    }

    list->head = next_offset;
  }

  if (!IS_EQUAL_OFFSET(next_offset, MEM_NULL_OFFSET)) {
    offset_memory_manager_write(list->mem_manager,
                                ADD_TO_OFFSET(prev_offset, offsetof(struct offset_list_node_header, next)),
                                (mem_size_t){sizeof(mem_offset_t)}, &next_offset);
    offset_memory_manager_write(list->mem_manager,
                                ADD_TO_OFFSET(next_offset, offsetof(struct offset_list_node_header, prev)),
                                (mem_size_t){sizeof(mem_offset_t)}, &prev_offset);
  }

  offset_fixed_base_allocator_free(list->allocator, to_free);
}

void offset_list_pop_back(struct offset_list* list) {
  struct offset_list_iterator tail;
  offset_list_tail(list, &tail);
  offset_list_delete(list, &tail);
}

void offset_list_pop_front(struct offset_list* list) {
  struct offset_list_iterator head;
  offset_list_head(list, &head);
  offset_list_delete(list, &head);
}

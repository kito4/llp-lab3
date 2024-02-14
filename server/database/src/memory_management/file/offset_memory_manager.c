#include "offset_memory_manager.h"

#include <stdlib.h>

void offset_memory_manager_read(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                void* buffer) {
  manager->read_f(manager, offset, buf_size, buffer);
}
void offset_memory_manager_write(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                 const void* buffer) {
  manager->write_f(manager, offset, buf_size, buffer);
}

mem_offset_t offset_memory_manager_extend(struct offset_memory_manager* manager, mem_size_t value) {
  mem_offset_t result = manager->extend_f(manager, value);
  manager->size.value += value.value;
  return result;
}

mem_size_t offset_memory_manager_get_size(struct offset_memory_manager* manager) {
  return manager->size;
}

void offset_memory_manager_cut(struct offset_memory_manager* manager, mem_size_t value) {
  manager->cut_f(manager, value);
  manager->size.value -= value.value;
}

bool offset_memory_manager_ctor(struct offset_memory_manager* manager, mem_size_t size) {
  manager->size = size;
  return true;
}

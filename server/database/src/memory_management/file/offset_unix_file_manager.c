#ifdef __unix__

#include "offset_memory_manager.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

struct offset_unix_file_manager {
  struct offset_memory_manager base_manager;
  char* filename;
  int fd;
  void* base;
};

bool offset_unix_file_manager_alloc(struct offset_unix_file_manager** ptr) {
  *ptr = malloc(sizeof(struct offset_unix_file_manager));
  return (*ptr != NULL);
}

bool offset_unix_file_manager_set_file_size(struct offset_unix_file_manager* file_manager, mem_size_t new_size) {
  if (file_manager->base != NULL) {
    if (msync(file_manager->base, file_manager->base_manager.size.value, MS_SYNC) == 0) {
      if (munmap(file_manager->base, file_manager->base_manager.size.value) != 0) {
        return false;
      }
    } else {
      return false;
    }
  }

  if (ftruncate(file_manager->fd, new_size.value) != 0) {
    return false;
  }

  file_manager->base = mmap(NULL, new_size.value, PROT_READ | PROT_WRITE, MAP_SHARED, file_manager->fd, 0);
  return (file_manager->base != NULL);
}

void offset_unix_file_manager_read_f(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                     void* buffer) {
  struct offset_unix_file_manager* self = (struct offset_unix_file_manager*)manager;
  void* target = (void*)(self->base + offset.data_block + offset.value);
  memcpy(buffer, target, buf_size.value);
}

void offset_unix_file_manager_write_f(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                      const void* buffer) {
  struct offset_unix_file_manager* self = (struct offset_unix_file_manager*)manager;
  void* target = (void*)(self->base + offset.data_block + offset.value);
  memcpy(target, buffer, buf_size.value);
}

mem_offset_t offset_unix_file_manager_extend_f(struct offset_memory_manager* manager, mem_size_t value) {
  struct offset_unix_file_manager* self = (struct offset_unix_file_manager*)manager;
  mem_offset_t result = {.data_block = manager->size.value, .value = 0};

  if (!offset_unix_file_manager_set_file_size(self, (mem_size_t){.value = manager->size.value + value.value})) {
    return MEM_NULL_OFFSET;
  }

  return result;
}

void offset_unix_file_manager_cut_f(struct offset_memory_manager* manager, mem_size_t value) {
  struct offset_unix_file_manager* self = (struct offset_unix_file_manager*)manager;

  offset_unix_file_manager_set_file_size(self, (mem_size_t){.value = manager->size.value - value.value});
}

bool offset_unix_file_manager_ctor(struct offset_unix_file_manager* file_manager, const char* filename,
                                   mem_size_t page_size) {
  file_manager->fd = open(filename, O_CREAT | O_RDWR, 0644);
  if (file_manager->fd < 0) {
    return false;
  }

  file_manager->base = NULL;

  size_t name_size = strlen(filename) + 1;
  file_manager->filename = malloc(name_size);
  if (!file_manager->filename) {
    close(file_manager->fd);
    return false;
  }
  strcpy(file_manager->filename, filename);

  struct stat st;
  if (fstat(file_manager->fd, &st) < 0) {
    close(file_manager->fd);
    return false;
  }
  long file_size = st.st_size;

  if (file_size == -1L) {
    close(file_manager->fd);
    free(file_manager->filename);
    return false;
  }

  if (file_size == 0) {
    if (!offset_unix_file_manager_set_file_size(file_manager, page_size)) {
      close(file_manager->fd);
      free(file_manager->filename);
      return false;
    }
    file_size = page_size.value;
  } else if (file_size < page_size.value) {
    close(file_manager->fd);
    free(file_manager->filename);
    return false;
  } else {
    file_manager->base = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_manager->fd, 0);
    if (file_manager->base == NULL) {
      close(file_manager->fd);
      free(file_manager->filename);
      return false;
    }
  }

  if (!offset_memory_manager_ctor(&file_manager->base_manager, (mem_size_t){.value = file_size})) {
    munmap(file_manager->base, file_size);
    close(file_manager->fd);
    free(file_manager->filename);
    return false;
  }

  file_manager->base_manager.cut_f = &offset_unix_file_manager_cut_f;
  file_manager->base_manager.extend_f = &offset_unix_file_manager_extend_f;
  file_manager->base_manager.read_f = &offset_unix_file_manager_read_f;
  file_manager->base_manager.write_f = &offset_unix_file_manager_write_f;

  return true;
}

void offset_unix_file_manager_dtor(struct offset_unix_file_manager* file_manager) {
  if (file_manager->base != NULL) {
    msync(file_manager->base, file_manager->base_manager.size.value, MS_SYNC);
    munmap(file_manager->base, file_manager->base_manager.size.value);
  }
  free(file_manager->filename);
  close(file_manager->fd);
}

#endif /* __unix__ */
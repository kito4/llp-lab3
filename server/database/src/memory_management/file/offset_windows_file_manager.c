#ifdef _WIN32

#include "offset_memory_manager.h"
#include "offset_windows_file_manager_interface.h"

#include <stdlib.h>
#include <windows.h>

struct offset_windows_file_manager {
  struct offset_memory_manager base_manager;
  char* filename;
  HANDLE file_handle;
  HANDLE mapping_handle;

  void* base;
};

bool offset_windows_file_manager_alloc(struct offset_windows_file_manager** ptr) {
  *ptr = malloc(sizeof(struct offset_windows_file_manager));
  return (ptr != NULL);
}

void offset_windows_file_manager_read_f(struct offset_memory_manager* manager, mem_offset_t offset, mem_size_t buf_size,
                                        void* buffer) {
  struct offset_windows_file_manager* self = (struct offset_windows_file_manager*)manager;
  void* target = (void*)(self->base + offset.data_block + offset.value);
  memcpy(buffer, target, buf_size.value);
}
void offset_windows_file_manager_write_f(struct offset_memory_manager* manager, mem_offset_t offset,
                                         mem_size_t buf_size, const void* buffer) {
  struct offset_windows_file_manager* self = (struct offset_windows_file_manager*)manager;
  void* target = (void*)(self->base + offset.data_block + offset.value);
  memcpy(target, buffer, buf_size.value);
}

bool offset_windows_file_manager_set_file_size(struct offset_windows_file_manager* file_manager, mem_size_t new_size) {
  if (file_manager->mapping_handle != NULL) {
    if (!UnmapViewOfFile(file_manager->base)) {
      return false;
    }
    if (!CloseHandle(file_manager->mapping_handle)) {
      return false;
    }
  }

  if (!SetFilePointerEx(file_manager->file_handle, (LARGE_INTEGER){.QuadPart = new_size.value}, NULL, FILE_BEGIN)) {
    return false;
  }

  if (!SetEndOfFile(file_manager->file_handle)) {
    return false;
  }

  file_manager->mapping_handle = CreateFileMappingA(file_manager->file_handle, NULL, PAGE_READWRITE, 0, 0, NULL);

  if (file_manager->mapping_handle == NULL) {
    return false;
  }

  file_manager->base = MapViewOfFile(file_manager->mapping_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);

  if (file_manager->base == NULL) {
    CloseHandle(file_manager->mapping_handle);
    return false;
  }

  return true;
}

mem_offset_t offset_windows_file_manager_extend_f(struct offset_memory_manager* manager, mem_size_t value) {
  struct offset_windows_file_manager* self = (struct offset_windows_file_manager*)manager;
  mem_offset_t result = {.data_block = manager->size.value, .value = 0};

  if (!offset_windows_file_manager_set_file_size(self, (mem_size_t){.value = manager->size.value + value.value})) {
    return MEM_NULL_OFFSET;
  }

  return result;
}

void offset_windows_file_manager_cut_f(struct offset_memory_manager* manager, mem_size_t value) {
  struct offset_windows_file_manager* self = (struct offset_windows_file_manager*)manager;

  offset_windows_file_manager_set_file_size(self, (mem_size_t){.value = manager->size.value - value.value});
}

bool offset_windows_file_manager_ctor(struct offset_windows_file_manager* file_manager, const char* filename,
                                      mem_size_t page_size) {
  size_t name_size = strlen(filename) + 1;
  file_manager->filename = malloc(name_size);
  if (file_manager->filename == NULL) {
    return false;
  }

  strcpy(file_manager->filename, filename);

  file_manager->mapping_handle = NULL;
  file_manager->base = NULL;

  file_manager->file_handle =
      CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

  if (file_manager->file_handle == INVALID_HANDLE_VALUE) {
    free(file_manager->filename);
    return false;
  }

  LARGE_INTEGER size;
  if (!GetFileSizeEx(file_manager->file_handle, &size)) {
    CloseHandle(file_manager->file_handle);
    free(file_manager->filename);
    return false;
  }

  if (size.QuadPart == 0) {
    if (!offset_windows_file_manager_set_file_size(file_manager, page_size)) {
      CloseHandle(file_manager->file_handle);
      free(file_manager->filename);
      return false;
    }
    size.QuadPart = page_size.value;
  } else if (size.QuadPart < page_size.value) {
    CloseHandle(file_manager->file_handle);
    free(file_manager->filename);
    return false;
  } else {
    file_manager->mapping_handle = CreateFileMappingA(file_manager->file_handle, NULL, PAGE_READWRITE, 0, 0, NULL);

    if (file_manager->mapping_handle == NULL) {
      return false;
    }

    file_manager->base = MapViewOfFile(file_manager->mapping_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    if (file_manager->base == NULL) {
      int error = GetLastError();
      CloseHandle(file_manager->mapping_handle);
      free(file_manager->filename);
      return false;
    }
  }

  if (!offset_memory_manager_ctor(&file_manager->base_manager, (mem_size_t){.value = size.QuadPart})) {
    UnmapViewOfFile(file_manager->base);
    CloseHandle(file_manager->mapping_handle);
    CloseHandle(file_manager->file_handle);
    free(file_manager->filename);
    return false;
  }

  file_manager->base_manager.cut_f = &offset_windows_file_manager_cut_f;
  file_manager->base_manager.extend_f = &offset_windows_file_manager_extend_f;
  file_manager->base_manager.read_f = &offset_windows_file_manager_read_f;
  file_manager->base_manager.write_f = &offset_windows_file_manager_write_f;

  return true;
}

void offset_windows_file_manager_dtor(struct offset_windows_file_manager* file_manager) {
  UnmapViewOfFile(file_manager->base);
  CloseHandle(file_manager->mapping_handle);
  CloseHandle(file_manager->file_handle);
  free(file_manager->filename);
}

#endif /* _WIN32 */
#pragma once

#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_

#include <stdint.h>

/**
 * @brief Structure that represents address
 */
typedef struct {
  uint64_t data_block;  ///< Offset of allocated data block
  uint64_t value;       ///< Offset from start of data block
} mem_offset_t;

#define MEM_NULL_OFFSET \
  (mem_offset_t) { .data_block = 0u, .value = 0u }

/**
 * @brief It's not recommended to use function call in any of argument, cause it could be called multiple time
 */
#define ADD_TO_OFFSET(offset, val) ((mem_offset_t){.data_block = offset.data_block, .value = offset.value + (val)})

/**
 * @brief It's not recommended to use function call in any of argument, cause it could be called multiple time
 */
#define IS_EQUAL_OFFSET(lhs, rhs) ((lhs.data_block == rhs.data_block) && (lhs.value == rhs.value))

typedef struct {
  uint64_t value;
} mem_size_t;

#endif /* _COMMON_TYPES_H_ */

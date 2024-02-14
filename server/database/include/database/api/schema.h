#pragma once

#ifndef _SCHEMA_H_
#define _SCHEMA_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "attribute.h"

typedef uint16_t element_type_id_t;
typedef uint16_t link_type_id_t;
typedef uint32_t attribute_count_t;
typedef uint32_t link_count_t;

struct element_type {
  element_type_id_t type_id;
  char* type_name;

  attribute_count_t attribute_count;
  enum ATTRIBUTE_TYPE* attribute_types;
};

/**
 * @brief Frees everything that might be malloced before
 * 
 * Use only with objects that has all fields allocated on heap
 * 
 * @param type 
 */
void element_type_dtor(struct element_type* type);

struct link_type {
  link_type_id_t type_id;
  char* type_name;
};

/**
 * @brief Frees everything that might be malloced before
 * 
 * Use only with objects that has all fields allocated on heap
 * 
 * @param type 
 */
void link_type_dtor(struct link_type* type);

/**
 * @brief Representation of file data schema in RAM
 */
struct schema {
  element_type_id_t element_types_count;
  struct element_type* element_types;

  link_type_id_t link_types_count;
  struct link_type* link_types;
};

#endif /* _SCHEMA_H_ */

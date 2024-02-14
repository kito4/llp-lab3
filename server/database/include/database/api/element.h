#pragma once

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "attribute.h"
#include "schema.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct element;

struct link {
  link_type_id_t link_type;
  struct element* dst;
};

/**
 * @brief Representation of data element in RAM
 * 
 * Also used in queries to represent patterns
 */
struct element {
  bool owns_type_ptr;  ///< If owns, then element_type will be freed in dtor
  struct element_type* element_type;

  attribute_count_t attribute_count;
  struct attribute* attributes;

  link_count_t links_out_cnt;
  struct link* links_out;

  link_count_t links_in_cnt;
  struct link* links_in;
};

// element must have no cycles
void element_free_links(struct link* links, link_count_t link_count, struct element* from);
// element must have no cycles
void element_dtor(struct element* element);

#endif /* _ELEMENT_H_ */

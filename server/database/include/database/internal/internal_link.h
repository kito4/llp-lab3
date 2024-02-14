#pragma once

#ifndef _INTERNAL_LINK_H_
#define _INTERNAL_LINK_H_

#include "common_types.h"
#include "element.h"
#include "schema.h"

struct internal_link {
  link_type_id_t type_id;
  mem_offset_t target_node;
  mem_offset_t chained_link_node;
};

mem_size_t internal_link_get_data_size();

#endif /* _INTERNAL_LINK_H_ */
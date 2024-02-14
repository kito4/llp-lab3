#pragma once

#ifndef _OFFSET_FIXED_ELEMENT_ALLOCATOR_H_
#define _OFFSET_FIXED_ELEMENT_ALLOCATOR_H_

#include "offset_element_allocator_interface.h"
#include "offset_fixed_base_allocator.h"
#include "offset_fixed_element_allocator_interface.h"

struct offset_fixed_element_allocator {
  struct offset_fixed_base_allocator base_alloc;
  struct offset_element_allocator* element_alloc;
  bool owner;
};

#endif /* _OFFSET_FIXED_ELEMENT_ALLOCATOR_H_ */
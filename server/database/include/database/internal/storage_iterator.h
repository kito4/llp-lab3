#pragma once

#ifndef _STORAGE_ITERATOR_H_
#define _STORAGE_ITERATOR_H_

#include "offset_list_iterator.h"
#include "storage_iterator_api.h"

struct storage_iterator {
  struct offset_list_iterator iter;
};

#endif /* _STORAGE_ITERATOR_H_ */
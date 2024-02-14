#pragma once

#ifndef _STORAGE_ITERATOR_API_H_
#define _STORAGE_ITERATOR_API_H_

#include <stdbool.h>

struct storage_iterator;

bool storage_iterator_alloc(struct storage_iterator** ptr);

void storage_iterator_next(struct storage_iterator* iter);
void storage_iterator_prev(struct storage_iterator* iter);
bool storage_iterator_equals(const struct storage_iterator* lhs, const struct storage_iterator* rhs);
void storage_iterator_copy(const struct storage_iterator* src, struct storage_iterator* dst);

#endif /* _STORAGE_ITERATOR_API_H_ */
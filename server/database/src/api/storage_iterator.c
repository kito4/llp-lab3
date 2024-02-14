#include "storage_iterator.h"

#include <stdlib.h>

bool storage_iterator_alloc(struct storage_iterator** ptr) {
  *ptr = malloc(sizeof(struct storage_iterator));
  return (*ptr != NULL);
}

void storage_iterator_next(struct storage_iterator* iter) {
  offset_list_iterator_next(&iter->iter);
}
void storage_iterator_prev(struct storage_iterator* iter) {
  offset_list_iterator_prev(&iter->iter);
}
bool storage_iterator_equals(const struct storage_iterator* lhs, const struct storage_iterator* rhs) {
  return offset_list_iterator_equals(&lhs->iter, &rhs->iter);
}
void storage_iterator_copy(const struct storage_iterator* src, struct storage_iterator* dst) {
  offset_list_iterator_copy(&src->iter, &dst->iter);
}
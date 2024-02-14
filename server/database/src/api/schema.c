#include "schema.h"

void element_type_dtor(struct element_type* type) {
  free(type->type_name);
  if (type->attribute_types) {
    free(type->attribute_types);
  }
}

void link_type_dtor(struct link_type* type) {
  free(type->type_name);
}
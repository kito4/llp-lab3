#include "element.h"

#include <stdlib.h>

static void free_attrs(struct attribute* attrs, attribute_count_t attribute_count) {
  for (attribute_count_t i = 0; i < attribute_count; i++) {
    if (attrs[i].type == ATTR_TYPE_STRING) {
      free(attrs[i].value.as_string.data);
    }
  }
  free(attrs);
}

void element_free_link(struct element* dst, struct element* from);

void element_free_links(struct link* links, link_count_t link_count, struct element* from) {
  for (link_count_t i = 0; i < link_count; i++) {
    if (links[i].dst == NULL || links[i].dst == from) {
      continue;
    }
    element_free_link(links[i].dst, from);
  }
  free(links);
}

void element_free_link(struct element* dst, struct element* from) {
  if (dst->owns_type_ptr && dst->element_type != NULL) {
    free(dst->element_type->type_name);
    free(dst->element_type);
  }
  free_attrs(dst->attributes, dst->attribute_count);

  if (dst->links_in != NULL) {
    for (link_count_t i = 0; i < dst->links_in_cnt; i++) {
      if (dst->links_in[i].dst == NULL || dst->links_in[i].dst == from) {
        continue;
      }
      element_free_link(dst->links_in[i].dst, dst);
    }
    free(dst->links_in);
  }
  if (dst->links_out != NULL) {
    for (link_count_t i = 0; i < dst->links_out_cnt; i++) {
      if (dst->links_out[i].dst == NULL || dst->links_out[i].dst == from) {
        continue;
      }
      element_free_link(dst->links_out[i].dst, dst);
    }
    free(dst->links_out);
  }
}

void element_dtor(struct element* element) {
  if (element->owns_type_ptr && element->element_type != NULL) {
    free(element->element_type->type_name);
    free(element->element_type->attribute_types);
    free(element->element_type);
  }
  free_attrs(element->attributes, element->attribute_count);

  if (element->links_in != NULL) {
    element_free_links(element->links_in, element->links_in_cnt, element);
  }
  if (element->links_out != NULL) {
    element_free_links(element->links_out, element->links_out_cnt, element);
  }
}
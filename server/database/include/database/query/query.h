#pragma once

#ifndef _QUERY_H_
#define _QUERY_H_

#include "element.h"
#include "schema.h"

enum ATTRIBUTE_PATTERN_NODE_TYPE { ATTRIBUTE_PATTERN_COND, ATTRIBUTE_PATTERN_BIN_OP, ATTRIBUTE_PATTERN_UN_OP };

enum ATTRIBUTE_PATTERN_UN_OP { ATTRIBUTE_PATTERN_NOT };
enum ATTRIBUTE_PATTERN_BIN_OP { ATTRIBUTE_PATTERN_AND, ATTRIBUTE_PATTERN_OR };

enum ATTRIBUTE_PATTERN_COND {
  ATTRIBUTE_PATTERN_COND_CONTAINS,
  ATTRIBUTE_PATTERN_COND_EQ,
  ATTRIBUTE_PATTERN_COND_LESS,
  ATTRIBUTE_PATTERN_COND_GREATER
};

struct attribute_pattern {
  enum ATTRIBUTE_PATTERN_NODE_TYPE node_type;
  union {
    struct {
      enum ATTRIBUTE_PATTERN_BIN_OP op_type;
      struct attribute_pattern* lhs;
      struct attribute_pattern* rhs;
    } as_bin;
    struct {
      enum ATTRIBUTE_PATTERN_UN_OP op_type;
      struct attribute_pattern* arg;
    } as_unary;
    struct {
      enum ATTRIBUTE_PATTERN_COND cond;
      attribute_count_t attr_id;
      struct attribute attr;
    } as_cond;
  } args;
};

struct element_pattern;

struct link_pattern {
  struct link_type* link_type;
  struct element_pattern* target;
};

struct element_pattern {
  struct element_type* element_type;

  struct attribute_pattern* attr_pattern;

  link_count_t links_out_cnt;
  struct link_pattern* links_out;

  link_count_t links_in_cnt;
  struct link_pattern* links_in;

  int idx;  ///< Must be initialized with zero, field to easily iterate through pattern without infinity loops
};

enum QUERY_TYPE {
  QUERY_TYPE_MATCH,
  QUERY_TYPE_CREATE,
  QUERY_TYPE_SET,
  QUERY_TYPE_LINK,
  QUERY_TYPE_DELETE,
  QUERY_TYPE_CREATE_VERTEX_TYPE,
  QUERY_TYPE_CREATE_EDGE_TYPE,
  QUERY_TYPE_DROP_VERTEX_TYPE,
  QUERY_TYPE_DROP_EDGE_TYPE
};

struct set_args {
  struct element_pattern* pattern;
  attribute_count_t attributes_count;

  struct attribute_and_id {
    attribute_count_t attribute_id;
    struct attribute attribute;
  }* attributes;
};

struct link_args {
  struct element_pattern* source_pattern;
  struct element_pattern* dst_pattern;
  struct link_type* link_type;
};

struct match_args {
  struct element_pattern* pattern;
};

struct delete_args {
  struct element_pattern* pattern;
};

struct create_args {
  struct element* element;
};

struct create_vertex_type_args {
  struct element_type* type;
};

struct create_edge_type_args {
  struct link_type* type;
};

struct drop_edge_type_args {
  char* type_name;
};

struct drop_vertex_type_args {
  char* type_name;
};

struct query {
  enum QUERY_TYPE type;

  union {
    struct match_args as_match;
    struct create_args as_create;
    struct delete_args as_delete;
    struct set_args as_set;
    struct link_args as_link;
    struct create_vertex_type_args as_create_vertex_type;
    struct drop_vertex_type_args as_drop_vertex_type;
    struct create_edge_type_args as_create_edge_type;
    struct drop_edge_type_args as_drop_edge_type;
  } args;
};

#endif /* _QUERY_H_ */

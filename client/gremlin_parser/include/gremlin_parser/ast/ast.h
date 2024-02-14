#pragma once

#ifndef _AST_H_
#define _AST_H_

#include <stdbool.h>
#include <stdint.h>

struct AST;

bool ast_alloc(struct AST** ptr);
void ast_free(struct AST* ast);

struct AST* ast_create_schema_add_v(struct AST* label, struct AST* props);
struct AST* ast_create_schema_drop_v(struct AST* label);
struct AST* ast_create_schema_add_e(struct AST* label);
struct AST* ast_create_schema_drop_e(struct AST* label);

struct AST* ast_create_prop_types_pair(struct AST* prop1, struct AST* prop2);
struct AST* ast_create_prop_types_int32();
struct AST* ast_create_prop_types_int64();
struct AST* ast_create_prop_types_double();
struct AST* ast_create_prop_types_bool();
struct AST* ast_create_prop_types_string();

struct AST* ast_create_prop_values(struct AST* val1, struct AST* val2);

struct AST* ast_create_graph_select(struct AST* specific_v);
struct AST* ast_create_graph_drop_v(struct AST* specific_v);
struct AST* ast_create_graph_add_v(struct AST* label, struct AST* prop_values_list);
struct AST* ast_create_graph_add_e(struct AST* label, struct AST* src_specific_v, struct AST* dst_specific_v);
struct AST* ast_create_graph_drop_e(struct AST* specific_v, struct AST* label, bool is_out);
struct AST* ast_create_graph_update(struct AST* specific_v, struct AST* prop_update_list);

struct AST* ast_create_prop_updates_list(struct AST* lhs, struct AST* rhs);
struct AST* ast_create_prop_update(struct AST* prop_id, struct AST* value);

struct AST* ast_create_specific_v(struct AST* label, struct AST* conditions);

struct AST* ast_create_condition_pair(struct AST* cond1, struct AST* cond2);
struct AST* ast_create_condition_has(struct AST* prop_id, struct AST* value_cond);
struct AST* ast_create_condition_or(struct AST* lhs, struct AST* rhs);
struct AST* ast_create_condition_out(struct AST* label);
struct AST* ast_create_condition_in(struct AST* label);
struct AST* ast_create_condition_filter(struct AST* conditions);

enum AST_NODE_VALUE_COND_TYPE {
  AST_NODE_VALUE_COND_EQ,
  AST_NODE_VALUE_COND_NEQ,
  AST_NODE_VALUE_COND_GT,
  AST_NODE_VALUE_COND_LT,
  AST_NODE_VALUE_COND_GTE,
  AST_NODE_VALUE_COND_LTE,
  AST_NODE_VALUE_COND_CONTAINS
};

struct AST* ast_create_value_cond(enum AST_NODE_VALUE_COND_TYPE type, struct AST* value);

struct AST* ast_create_property_id(struct AST* id);

struct AST* ast_create_int_literal(int64_t val);
struct AST* ast_create_double_literal(double val);

/**
 * @brief Creates ast label node
 * 
 * @param label ptr that will be MOVED into AST
 * @return struct AST* 
 */
struct AST* ast_create_string_literal(char* label);

enum AST_NODE_TYPE {
  AST_NODE_SCHEMA_ADD_V,
  AST_NODE_PROPERTY_TYPES_LIST,
  AST_NODE_SCHEMA_DROP_V,
  AST_NODE_SCHEMA_ADD_E,
  AST_NODE_SCHEMA_DROP_E,
  AST_NODE_GRAPH_SELECT,
  AST_NODE_GRAPH_ADD_E,
  AST_NODE_GRAPH_ADD_V,
  AST_NODE_GRAPH_DROP_E,
  AST_NODE_GRAPH_UPDATE,
  AST_NODE_PROPERTY_UPDATES_LIST,
  AST_NODE_PROPERTY_UPDATE,
  AST_NODE_PROPERTY_VALUES_LIST,
  AST_NODE_SPECIFIC_V,
  AST_NODE_V_CONDITIONS,
  AST_NODE_VALUE_COND,
  AST_NODE_PROPERTY_ID,
  AST_NODE_GRAPH_DROP_V,
  AST_NODE_LIT
};

enum AST_NODE_V_COND_TYPE {
  AST_NODE_V_COND_PAIR,
  AST_NODE_V_COND_HAS,
  AST_NODE_V_COND_FILTER,
  AST_NODE_V_COND_OR,
  AST_NODE_V_COND_OUT,
  AST_NODE_V_COND_IN
};

enum AST_NODE_LIT_TYPE { AST_NODE_LIT_STRING, AST_NODE_LIT_INT, AST_NODE_LIT_DOUBLE };

enum AST_NODE_PROPERTY_TYPE {
  AST_NODE_PROPERTY_INT32,
  AST_NODE_PROPERTY_INT64,
  AST_NODE_PROPERTY_DOUBLE,
  AST_NODE_PROPERTY_BOOL,
  AST_NODE_PROPERTY_STRING,
  AST_NODE_PROPERTY_PAIR
};

struct AST {
  enum AST_NODE_TYPE type;
  union {
    struct {
      struct AST* label;
      struct AST* prop_types;
    } as_schema_add_v;
    struct {
      struct AST* label;
    } as_schema_drop_v;
    struct {
      struct AST* label;
    } as_schema_add_e;
    struct {
      struct AST* label;
    } as_schema_drop_e;
    struct {
      struct AST* label;
      struct AST* properties;
    } as_graph_add_v;
    struct {
      struct AST* specific_v;
      struct AST* prop_updates_list;
    } as_graph_update;
    struct {
      struct AST* lhs;
      struct AST* rhs;
    } as_prop_update_list;
    struct {
      struct AST* property_id;
      struct AST* value;
    } as_prop_update;
    struct {
      struct AST* label;
      struct AST* src_specific_v;
      struct AST* dst_specific_v;
    } as_graph_add_e;
    struct {
      enum AST_NODE_PROPERTY_TYPE prop_type;
      union {
        struct {
          struct AST* lhs;
          struct AST* rhs;
        } as_pair;
      } value;
    } as_prop_types_list;
    struct {
      struct AST* lhs;
      struct AST* rhs;
    } as_prop_values_list;
    struct {
      struct AST* specific_v;
    } as_select;
    struct {
      struct AST* label;
      struct AST* conditions;
    } as_specific_v;
    struct {
      enum AST_NODE_V_COND_TYPE cond_type;
      union {
        struct {
          struct AST* lhs;
          struct AST* rhs;
        } as_pair;
        struct {
          struct AST* prop_id;
          struct AST* value_cond;
        } as_has;
        struct {
          struct AST* lhs;
          struct AST* rhs;
        } as_or;
        struct {
          struct AST* label;
        } as_out;
        struct {
          struct AST* label;
        } as_in;
        struct {
          struct AST* conditions;
        } as_filter;
      } value;
    } as_conditions;
    struct {
      enum AST_NODE_VALUE_COND_TYPE type;
      struct AST* value;
    } as_value_cond;
    struct {
      struct AST* id;
    } as_property_id;
    struct {
      struct AST* specific_v;
    } as_graph_drop_v;
    struct {
      struct AST* specific_v;
      struct AST* label;
      bool is_out;
    } as_graph_drop_e;
    struct {
      enum AST_NODE_LIT_TYPE type;
      union {
        char* as_string;
        int64_t as_int;
        double as_double;
      } value;
    } as_literal;
  } args;
};

#endif /* _AST_H_ */
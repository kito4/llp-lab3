#include "ast.h"

#include <stdlib.h>

bool ast_alloc(struct AST** ptr) {
  *ptr = malloc(sizeof(struct AST));
  return (*ptr != NULL);
}

void ast_free(struct AST* ast) {
  if (!ast) {
    return;
  }

  switch (ast->type) {
    case AST_NODE_GRAPH_UPDATE:
      ast_free(ast->args.as_graph_update.specific_v);
      ast_free(ast->args.as_graph_update.prop_updates_list);
      break;
    case AST_NODE_PROPERTY_UPDATE:
      ast_free(ast->args.as_prop_update.property_id);
      ast_free(ast->args.as_prop_update.value);
      break;
    case AST_NODE_PROPERTY_UPDATES_LIST:
      ast_free(ast->args.as_prop_update_list.lhs);
      ast_free(ast->args.as_prop_update_list.rhs);
      break;
    case AST_NODE_GRAPH_ADD_V:
      ast_free(ast->args.as_graph_add_v.label);
      ast_free(ast->args.as_graph_add_v.properties);
      break;
    case AST_NODE_PROPERTY_VALUES_LIST:
      ast_free(ast->args.as_prop_values_list.lhs);
      ast_free(ast->args.as_prop_values_list.rhs);
      break;
    case AST_NODE_GRAPH_ADD_E:
      ast_free(ast->args.as_graph_add_e.label);
      ast_free(ast->args.as_graph_add_e.src_specific_v);
      ast_free(ast->args.as_graph_add_e.dst_specific_v);
      break;
    case AST_NODE_LIT:
      switch (ast->args.as_literal.type) {
        case AST_NODE_LIT_STRING:
          free(ast->args.as_literal.value.as_string);
          break;
        case AST_NODE_LIT_INT:
        case AST_NODE_LIT_DOUBLE:
        default:
          break;
      }
      break;
    case AST_NODE_GRAPH_SELECT:
      ast_free(ast->args.as_select.specific_v);
      break;
    case AST_NODE_SPECIFIC_V:
      ast_free(ast->args.as_specific_v.conditions);
      ast_free(ast->args.as_specific_v.label);
      break;
    case AST_NODE_V_CONDITIONS:
      switch (ast->args.as_conditions.cond_type) {
        case AST_NODE_V_COND_PAIR:
          ast_free(ast->args.as_conditions.value.as_pair.lhs);
          ast_free(ast->args.as_conditions.value.as_pair.rhs);
          break;
        case AST_NODE_V_COND_HAS:
          ast_free(ast->args.as_conditions.value.as_has.prop_id);
          ast_free(ast->args.as_conditions.value.as_has.value_cond);
          break;
        case AST_NODE_V_COND_FILTER:
          ast_free(ast->args.as_conditions.value.as_filter.conditions);
          break;
        case AST_NODE_V_COND_OR:
          ast_free(ast->args.as_conditions.value.as_or.lhs);
          ast_free(ast->args.as_conditions.value.as_or.rhs);
          break;
        case AST_NODE_V_COND_OUT:
          ast_free(ast->args.as_conditions.value.as_out.label);
          break;
        case AST_NODE_V_COND_IN:
          ast_free(ast->args.as_conditions.value.as_in.label);
          break;
        default:
          break;
      }
      break;
    case AST_NODE_VALUE_COND:
      ast_free(ast->args.as_value_cond.value);
      break;
    case AST_NODE_PROPERTY_ID:
      ast_free(ast->args.as_property_id.id);
      break;
    case AST_NODE_GRAPH_DROP_V:
      ast_free(ast->args.as_graph_drop_v.specific_v);
      break;
    case AST_NODE_PROPERTY_TYPES_LIST:
      switch (ast->args.as_prop_types_list.prop_type) {
        case AST_NODE_PROPERTY_PAIR:
          ast_free(ast->args.as_prop_types_list.value.as_pair.lhs);
          ast_free(ast->args.as_prop_types_list.value.as_pair.rhs);
          break;
        case AST_NODE_PROPERTY_STRING:
        case AST_NODE_PROPERTY_BOOL:
        case AST_NODE_PROPERTY_DOUBLE:
        case AST_NODE_PROPERTY_INT32:
        case AST_NODE_PROPERTY_INT64:
          break;
        default:
          break;
      }
      break;
    case AST_NODE_SCHEMA_ADD_V:
      ast_free(ast->args.as_schema_add_v.label);
      ast_free(ast->args.as_schema_add_v.prop_types);
      break;
    case AST_NODE_SCHEMA_DROP_V:
      ast_free(ast->args.as_schema_drop_v.label);
      break;
    case AST_NODE_SCHEMA_ADD_E:
      ast_free(ast->args.as_schema_add_e.label);
      break;
    case AST_NODE_SCHEMA_DROP_E:
      ast_free(ast->args.as_schema_drop_e.label);
      break;
    default:
      break;
  }
  free(ast);
}

struct AST* ast_create_schema_add_v(struct AST* label, struct AST* props) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_SCHEMA_ADD_V;
  res->args.as_schema_add_v.label = label;
  res->args.as_schema_add_v.prop_types = props;

  return res;
}
struct AST* ast_create_schema_drop_v(struct AST* label) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_SCHEMA_DROP_V;
  res->args.as_schema_drop_v.label = label;

  return res;
}
struct AST* ast_create_schema_add_e(struct AST* label) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_SCHEMA_ADD_E;
  res->args.as_schema_add_e.label = label;

  return res;
}
struct AST* ast_create_schema_drop_e(struct AST* label) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_SCHEMA_DROP_E;
  res->args.as_schema_drop_e.label = label;

  return res;
}

struct AST* ast_create_prop_types_pair(struct AST* prop1, struct AST* prop2) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_TYPES_LIST;
  res->args.as_prop_types_list.prop_type = AST_NODE_PROPERTY_PAIR;
  res->args.as_prop_types_list.value.as_pair.lhs = prop1;
  res->args.as_prop_types_list.value.as_pair.rhs = prop2;

  return res;
}

struct AST* ast_create_prop_types_int32() {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_TYPES_LIST;
  res->args.as_prop_types_list.prop_type = AST_NODE_PROPERTY_INT32;

  return res;
}
struct AST* ast_create_prop_types_int64() {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_TYPES_LIST;
  res->args.as_prop_types_list.prop_type = AST_NODE_PROPERTY_INT64;

  return res;
}
struct AST* ast_create_prop_types_double() {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_TYPES_LIST;
  res->args.as_prop_types_list.prop_type = AST_NODE_PROPERTY_DOUBLE;

  return res;
}
struct AST* ast_create_prop_types_bool() {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_TYPES_LIST;
  res->args.as_prop_types_list.prop_type = AST_NODE_PROPERTY_BOOL;

  return res;
}
struct AST* ast_create_prop_types_string() {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_TYPES_LIST;
  res->args.as_prop_types_list.prop_type = AST_NODE_PROPERTY_STRING;

  return res;
}

struct AST* ast_create_string_literal(char* label) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_LIT;
  res->args.as_literal.type = AST_NODE_LIT_STRING;
  res->args.as_literal.value.as_string = label;

  return res;
}

struct AST* ast_create_graph_select(struct AST* specific_v) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_GRAPH_SELECT;
  res->args.as_select.specific_v = specific_v;

  return res;
}

struct AST* ast_create_graph_drop_v(struct AST* specific_v) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_GRAPH_DROP_V;
  res->args.as_graph_drop_v.specific_v = specific_v;

  return res;
}

struct AST* ast_create_specific_v(struct AST* label, struct AST* conditions) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_SPECIFIC_V;
  res->args.as_specific_v.label = label;
  res->args.as_specific_v.conditions = conditions;

  return res;
}

struct AST* ast_create_condition_pair(struct AST* cond1, struct AST* cond2) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_V_CONDITIONS;
  res->args.as_conditions.cond_type = AST_NODE_V_COND_PAIR;
  res->args.as_conditions.value.as_pair.lhs = cond1;
  res->args.as_conditions.value.as_pair.rhs = cond2;

  return res;
}
struct AST* ast_create_condition_has(struct AST* prop_id, struct AST* value_cond) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_V_CONDITIONS;
  res->args.as_conditions.cond_type = AST_NODE_V_COND_HAS;
  res->args.as_conditions.value.as_has.prop_id = prop_id;
  res->args.as_conditions.value.as_has.value_cond = value_cond;

  return res;
}
struct AST* ast_create_condition_or(struct AST* lhs, struct AST* rhs) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_V_CONDITIONS;
  res->args.as_conditions.cond_type = AST_NODE_V_COND_OR;
  res->args.as_conditions.value.as_or.lhs = lhs;
  res->args.as_conditions.value.as_or.rhs = rhs;

  return res;
}
struct AST* ast_create_condition_out(struct AST* label) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_V_CONDITIONS;
  res->args.as_conditions.cond_type = AST_NODE_V_COND_OUT;
  res->args.as_conditions.value.as_out.label = label;

  return res;
}
struct AST* ast_create_condition_in(struct AST* label) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_V_CONDITIONS;
  res->args.as_conditions.cond_type = AST_NODE_V_COND_IN;
  res->args.as_conditions.value.as_in.label = label;

  return res;
}
struct AST* ast_create_condition_filter(struct AST* conditions) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_V_CONDITIONS;
  res->args.as_conditions.cond_type = AST_NODE_V_COND_FILTER;
  res->args.as_conditions.value.as_filter.conditions = conditions;

  return res;
}

struct AST* ast_create_value_cond(enum AST_NODE_VALUE_COND_TYPE type, struct AST* value) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_VALUE_COND;
  res->args.as_value_cond.type = type;
  res->args.as_value_cond.value = value;

  return res;
}

struct AST* ast_create_property_id(struct AST* id) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_ID;
  res->args.as_property_id.id = id;

  return res;
}

struct AST* ast_create_int_literal(int64_t val) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_LIT;
  res->args.as_literal.type = AST_NODE_LIT_INT;
  res->args.as_literal.value.as_int = val;

  return res;
}
struct AST* ast_create_double_literal(double val) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_LIT;
  res->args.as_literal.type = AST_NODE_LIT_DOUBLE;
  res->args.as_literal.value.as_double = val;

  return res;
}

struct AST* ast_create_prop_values(struct AST* val1, struct AST* val2) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_VALUES_LIST;
  res->args.as_prop_values_list.lhs = val1;
  res->args.as_prop_values_list.rhs = val2;

  return res;
}

struct AST* ast_create_graph_add_v(struct AST* label, struct AST* prop_values_list) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_GRAPH_ADD_V;
  res->args.as_graph_add_v.label = label;
  res->args.as_graph_add_v.properties = prop_values_list;

  return res;
}

struct AST* ast_create_graph_add_e(struct AST* label, struct AST* src_specific_v, struct AST* dst_specific_v) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_GRAPH_ADD_E;
  res->args.as_graph_add_e.label = label;
  res->args.as_graph_add_e.src_specific_v = src_specific_v;
  res->args.as_graph_add_e.dst_specific_v = dst_specific_v;

  return res;
}

struct AST* ast_create_graph_drop_e(struct AST* specific_v, struct AST* label, bool is_out) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_GRAPH_DROP_E;
  res->args.as_graph_drop_e.specific_v = specific_v;
  res->args.as_graph_drop_e.label = label;
  res->args.as_graph_drop_e.is_out = is_out;

  return res;
}

struct AST* ast_create_graph_update(struct AST* specific_v, struct AST* prop_update_list) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_GRAPH_UPDATE;
  res->args.as_graph_update.specific_v = specific_v;
  res->args.as_graph_update.prop_updates_list = prop_update_list;

  return res;
}

struct AST* ast_create_prop_updates_list(struct AST* lhs, struct AST* rhs) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_UPDATES_LIST;
  res->args.as_prop_update_list.lhs = lhs;
  res->args.as_prop_update_list.rhs = rhs;

  return res;
}

struct AST* ast_create_prop_update(struct AST* prop_id, struct AST* value) {
  struct AST* res;
  if (!ast_alloc(&res)) {
    return NULL;
  }
  res->type = AST_NODE_PROPERTY_UPDATE;
  res->args.as_prop_update.property_id = prop_id;
  res->args.as_prop_update.value = value;

  return res;
}
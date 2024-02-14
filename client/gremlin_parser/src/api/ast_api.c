#include "ast_api.h"

#include <inttypes.h>
#include <stdint.h>

#include "ast.h"

#include "lexer.h"
#include "parser.h"
#include "parser_res.h"

struct AST* ast_parse() {
  if (yyparse() != 0) {
    return (void*)0;
  }
  return get_parse_result();
}

struct AST* ast_parse_from_file(FILE* input) {
  YY_BUFFER_STATE state = yy_create_buffer(input, YY_BUF_SIZE);
  yy_switch_to_buffer(state);
  if (yyparse() != 0) {
    yy_delete_buffer(state);
    return (void*)0;
  }
  yy_delete_buffer(state);
  return get_parse_result();
}

static char* AST_NODE_NAME[] = {
    [AST_NODE_SCHEMA_ADD_V] = "SCHEMA_ADD_V",
    [AST_NODE_PROPERTY_TYPES_LIST] = "",
    [AST_NODE_SCHEMA_DROP_V] = "SCHEMA_DROP_V",
    [AST_NODE_SCHEMA_ADD_E] = "SCHEMA_ADD_E",
    [AST_NODE_SCHEMA_DROP_E] = "SCHEMA_DROP_E",
    [AST_NODE_GRAPH_SELECT] = "GRAPH_SELECT",
    [AST_NODE_GRAPH_ADD_E] = "GRAPH_ADD_E",
    [AST_NODE_GRAPH_ADD_V] = "GRAPH_ADD_V",
    [AST_NODE_GRAPH_DROP_E] = "GRAPH_DROP_E",
    [AST_NODE_GRAPH_UPDATE] = "GRAPH_UPDATE",
    [AST_NODE_PROPERTY_UPDATES_LIST] = "PROPERTY_UPDATES_LIST",
    [AST_NODE_PROPERTY_UPDATE] = "PROPERTY_UPDATE",
    [AST_NODE_PROPERTY_VALUES_LIST] = "PROPERTY_VALUES_LIST",
    [AST_NODE_SPECIFIC_V] = "SPECIFIC_V",
    [AST_NODE_V_CONDITIONS] = "",
    [AST_NODE_VALUE_COND] = "",
    [AST_NODE_PROPERTY_ID] = "PROPERTY_ID",
    [AST_NODE_GRAPH_DROP_V] = "GRAPH_DROP_V",
    [AST_NODE_LIT] = "",
};

static char* AST_NODE_LIT_NAME[] = {
    [AST_NODE_LIT_STRING] = "LIT_STRING",
    [AST_NODE_LIT_INT] = "LIT_INT",
    [AST_NODE_LIT_DOUBLE] = "LIT_DOUBLE",
};

static char* AST_NODE_VALUE_COND_NAME[] = {
    [AST_NODE_VALUE_COND_EQ] = "VALUE_COND_EQ",
    [AST_NODE_VALUE_COND_NEQ] = "VALUE_COND_NEQ",
    [AST_NODE_VALUE_COND_GT] = "VALUE_COND_GT",
    [AST_NODE_VALUE_COND_LT] = "VALUE_COND_LT",
    [AST_NODE_VALUE_COND_GTE] = "VALUE_COND_GTE",
    [AST_NODE_VALUE_COND_LTE] = "VALUE_COND_LTE",
    [AST_NODE_VALUE_COND_CONTAINS] = "VALUE_COND_CONTAINS",
};

static char* AST_NODE_PROPERTY_TYPE_NAME[] = {
    [AST_NODE_PROPERTY_INT32] = "PROPERTY_TYPE_INT32",   [AST_NODE_PROPERTY_INT64] = "PROPERTY_TYPE_INT64",
    [AST_NODE_PROPERTY_DOUBLE] = "PROPERTY_TYPE_DOUBLE", [AST_NODE_PROPERTY_BOOL] = "PROPERTY_TYPE_BOOL",
    [AST_NODE_PROPERTY_STRING] = "PROPERTY_TYPE_STRING", [AST_NODE_PROPERTY_PAIR] = "PROPERTY_TYPE_PAIR",
};

static char* AST_NODE_V_COND_NAME[] = {
    [AST_NODE_V_COND_PAIR] = "V_COND_PAIR",     [AST_NODE_V_COND_HAS] = "V_COND_HAS",
    [AST_NODE_V_COND_FILTER] = "V_COND_FILTER", [AST_NODE_V_COND_OR] = "V_COND_OR",
    [AST_NODE_V_COND_OUT] = "V_COND_OUT",       [AST_NODE_V_COND_IN] = "V_COND_IN",
};

// node, out, id, from_id, depth
typedef bool (*printer_t)(struct AST*, FILE*, uint64_t, uint64_t, uint64_t);

static uint64_t next_id = 1;

static void ast_walker(struct AST* ast, int from_id, FILE* out, int depth, printer_t printer) {
  uint64_t id = next_id++;

  if (!printer(ast, out, id, from_id, depth)) {
    return;
  }

  switch (ast->type) {
    case AST_NODE_GRAPH_UPDATE:
      ast_walker(ast->args.as_graph_update.specific_v, id, out, depth + 1, printer);
      ast_walker(ast->args.as_graph_update.prop_updates_list, id, out, depth + 1, printer);
      break;
    case AST_NODE_GRAPH_DROP_E:
      ast_walker(ast->args.as_graph_drop_e.label, id, out, depth + 1, printer);
      ast_walker(ast->args.as_graph_drop_e.specific_v, id, out, depth + 1, printer);
      break;
    case AST_NODE_GRAPH_ADD_V:
      ast_walker(ast->args.as_graph_add_v.label, id, out, depth + 1, printer);
      ast_walker(ast->args.as_graph_add_v.properties, id, out, depth + 1, printer);
      break;
    case AST_NODE_PROPERTY_VALUES_LIST:
      ast_walker(ast->args.as_prop_values_list.lhs, id, out, depth + 1, printer);
      ast_walker(ast->args.as_prop_values_list.rhs, id, out, depth + 1, printer);
      break;
    case AST_NODE_PROPERTY_UPDATES_LIST:
      ast_walker(ast->args.as_prop_update_list.lhs, id, out, depth + 1, printer);
      ast_walker(ast->args.as_prop_update_list.rhs, id, out, depth + 1, printer);
      break;
    case AST_NODE_PROPERTY_UPDATE:
      ast_walker(ast->args.as_prop_update.property_id, id, out, depth + 1, printer);
      ast_walker(ast->args.as_prop_update.value, id, out, depth + 1, printer);
      break;
    case AST_NODE_GRAPH_ADD_E:
      ast_walker(ast->args.as_graph_add_e.label, id, out, depth + 1, printer);
      ast_walker(ast->args.as_graph_add_e.src_specific_v, id, out, depth + 1, printer);
      ast_walker(ast->args.as_graph_add_e.dst_specific_v, id, out, depth + 1, printer);
      break;
    case AST_NODE_GRAPH_SELECT:
      ast_walker(ast->args.as_select.specific_v, id, out, depth + 1, printer);
      break;
    case AST_NODE_SPECIFIC_V:
      ast_walker(ast->args.as_specific_v.label, id, out, depth + 1, printer);
      ast_walker(ast->args.as_specific_v.conditions, id, out, depth + 1, printer);
      break;
    case AST_NODE_V_CONDITIONS:
      switch (ast->args.as_conditions.cond_type) {
        case AST_NODE_V_COND_PAIR:
          ast_walker(ast->args.as_conditions.value.as_pair.lhs, id, out, depth + 1, printer);
          ast_walker(ast->args.as_conditions.value.as_pair.rhs, id, out, depth + 1, printer);
          break;
        case AST_NODE_V_COND_HAS:
          ast_walker(ast->args.as_conditions.value.as_has.prop_id, id, out, depth + 1, printer);
          ast_walker(ast->args.as_conditions.value.as_has.value_cond, id, out, depth + 1, printer);
          break;
        case AST_NODE_V_COND_FILTER:
          ast_walker(ast->args.as_conditions.value.as_filter.conditions, id, out, depth + 1, printer);
          break;
        case AST_NODE_V_COND_OR:
          ast_walker(ast->args.as_conditions.value.as_or.lhs, id, out, depth + 1, printer);
          ast_walker(ast->args.as_conditions.value.as_or.rhs, id, out, depth + 1, printer);
          break;
        case AST_NODE_V_COND_OUT:
          ast_walker(ast->args.as_conditions.value.as_out.label, id, out, depth + 1, printer);
          break;
        case AST_NODE_V_COND_IN:
          ast_walker(ast->args.as_conditions.value.as_in.label, id, out, depth + 1, printer);
          break;
        default:
          break;
      }
      break;
    case AST_NODE_VALUE_COND:
      ast_walker(ast->args.as_value_cond.value, id, out, depth + 1, printer);
      break;
    case AST_NODE_PROPERTY_ID:
      ast_walker(ast->args.as_property_id.id, id, out, depth + 1, printer);
      break;
    case AST_NODE_GRAPH_DROP_V:
      ast_walker(ast->args.as_graph_drop_v.specific_v, id, out, depth + 1, printer);
      break;
    case AST_NODE_PROPERTY_TYPES_LIST:
      switch (ast->args.as_prop_types_list.prop_type) {
        case AST_NODE_PROPERTY_PAIR:
          ast_walker(ast->args.as_prop_types_list.value.as_pair.lhs, id, out, depth + 1, printer);
          ast_walker(ast->args.as_prop_types_list.value.as_pair.rhs, id, out, depth + 1, printer);
          break;
        default:
          break;
      }
      break;
    case AST_NODE_SCHEMA_ADD_V:
      ast_walker(ast->args.as_schema_add_v.label, id, out, depth + 1, printer);
      ast_walker(ast->args.as_schema_add_v.prop_types, id, out, depth + 1, printer);
      break;
    case AST_NODE_SCHEMA_DROP_V:
      ast_walker(ast->args.as_schema_drop_v.label, id, out, depth + 1, printer);
      break;
    case AST_NODE_SCHEMA_ADD_E:
      ast_walker(ast->args.as_schema_add_e.label, id, out, depth + 1, printer);
      break;
    case AST_NODE_SCHEMA_DROP_E:
      ast_walker(ast->args.as_schema_drop_e.label, id, out, depth + 1, printer);
      break;
    default:
      break;
  }
}

static void ast_print_node_name(struct AST* ast, FILE* out) {
  fprintf(out, "%s", AST_NODE_NAME[ast->type]);
  switch (ast->type) {
    case AST_NODE_GRAPH_DROP_E:
      if (ast->args.as_graph_drop_e.is_out) {
        fprintf(out, "_OUT");
      } else {
        fprintf(out, "_IN");
      }
      break;
    case AST_NODE_LIT:
      fprintf(out, "%s (", AST_NODE_LIT_NAME[ast->args.as_literal.type]);
      switch (ast->args.as_literal.type) {
        case AST_NODE_LIT_STRING:
          fprintf(out, "\'%s\'", ast->args.as_literal.value.as_string);
          break;
        case AST_NODE_LIT_INT:
          fprintf(out, "%" PRId64, ast->args.as_literal.value.as_int);
          break;
        case AST_NODE_LIT_DOUBLE:
          fprintf(out, "%lf", ast->args.as_literal.value.as_double);
          break;
        default:
          break;
      }
      fprintf(out, ")");
      break;
    case AST_NODE_V_CONDITIONS:
      fprintf(out, "%s", AST_NODE_V_COND_NAME[ast->args.as_conditions.cond_type]);
      break;
    case AST_NODE_VALUE_COND:
      fprintf(out, "%s", AST_NODE_VALUE_COND_NAME[ast->args.as_value_cond.type]);
      break;
    case AST_NODE_PROPERTY_TYPES_LIST:
      fprintf(out, "%s", AST_NODE_PROPERTY_TYPE_NAME[ast->args.as_prop_types_list.prop_type]);
      break;
    default:
      break;
  }
}

static void ast_print_offset(FILE* out, int depth) {
  for (int i = 0; i < depth - 1; i++) {
    fprintf(out, "|  ");
  }
  if (depth > 0) {
    fprintf(out, "|--");
  }
}

bool ast_base_printer(struct AST* ast, FILE* out, uint64_t id, uint64_t from_id, uint64_t depth) {
  ast_print_offset(out, depth);
  fprintf(out, "+-");

  if (!ast) {
    fprintf(out, "<NULL>\n");
    return false;
  }

  ast_print_node_name(ast, out);

  fprintf(out, "\n");
  return true;
}

void ast_print(struct AST* ast, FILE* out) {
  ast_walker(ast, 0, out, 0, &ast_base_printer);
}

bool ast_graphviz_printer(struct AST* ast, FILE* out, uint64_t id, uint64_t from_id, uint64_t depth) {
  if (!ast) {
    return false;
  }
  fprintf(out, "%" PRId64 " [label = \"", id);
  ast_print_node_name(ast, out);
  fprintf(out, "\";];\n");

  if (from_id != 0) {
    fprintf(out, "%" PRId64 " -> %" PRId64 ";\n", from_id, id);
  }
  return true;
}

void ast_graphviz(struct AST* ast, FILE* out) {
  fprintf(out, "digraph {\n");
  ast_walker(ast, 0, out, 0, &ast_graphviz_printer);
  fprintf(out, "}\n");
}
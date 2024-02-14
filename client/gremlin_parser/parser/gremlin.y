%{
#include <stdio.h>
#include <stdint.h>

#include "ast.h"
#include "parser_res.h"

int yylex (void);
void yyerror (char const * err) {
  fprintf(stderr, "Parse Error: %s\n", err);
}
%}
/* Bison declarations. */
%define parse.error verbose

%union {
  char* as_string;
  int64_t as_int;
  double as_double;
  struct AST* as_ast;
}

%token SEMICOLON
%token DOT
%token COMMA
%token L_PAR
%token R_PAR

%token SCHEMA
%token CREATE_F
%token DROP_F
%token PROPERTIES_F
%token INT32_F
%token INT64_F
%token DOUBLE_F
%token BOOL_F
%token STRING_F
%token VERTEX_LABEL
%token EDGE_LABEL
%token ADD_EDGE
%token ADD_VERTEX
%token OUT_E
%token IN_E
%token PROPERTY

%token GRAPH
%token V_F
%token HAS
%token HAS_LABEL
%token OUT
%token IN
%token FILTER
%token VALUES_F

%token OR
%token CONTAINING
%token NEQ
%token GT
%token LT
%token GTE
%token LTE

%token <as_int> INTEGER_LIT
%token <as_double> DOUBLE_LIT
%token <as_string> STRING_LIT

%type <as_ast> schema_op
%type <as_ast> v_label
%type <as_ast> string_lit
%type <as_ast> s_vertex_op
%type <as_ast> prop_types_dot
%type <as_ast> prop_types_list
%type <as_ast> prop_type_dot
%type <as_ast> e_label
%type <as_ast> s_edge_op

%type <as_ast> graph_op
%type <as_ast> specific_v_dot
%type <as_ast> has_label
%type <as_ast> v_path_pattern_dot
%type <as_ast> v_path_pattern
%type <as_ast> condition_list_dot
%type <as_ast> condition_list
%type <as_ast> condition
%type <as_ast> filter_expr
%type <as_ast> has_expr
%type <as_ast> edge_cond
%type <as_ast> edge_expr_dot
%type <as_ast> edge_expr
%type <as_ast> number_lit
%type <as_ast> value_cond
%type <as_ast> property_id
%type <as_ast> filter_argument

%type <as_ast> add_vertex
%type <as_ast> prop_values_list
%type <as_ast> prop_updates_list
%type <as_ast> prop_update
%type <as_ast> add_edge
%type <as_ast> drop_edge
%type <as_ast> specific_v

%destructor {
  ast_free($$);
} <as_ast>

%destructor {
  free($$);
} <as_string>

%% /* The grammar follows. */
query: 
  SCHEMA DOT schema_op {set_parse_result($3); YYACCEPT;}
| GRAPH DOT graph_op {set_parse_result($3); YYACCEPT;}

graph_op:
  specific_v_dot VALUES_F {$$ = ast_create_graph_select($1);}
| specific_v_dot DROP_F {$$ = ast_create_graph_drop_v($1);}
| drop_edge {$$ = $1;}
| add_vertex {$$ = $1;}
| add_edge {$$ = $1;} 
| specific_v_dot prop_updates_list SEMICOLON {$$ = ast_create_graph_update($1, $2);}

prop_updates_list:
  prop_update DOT prop_updates_list {$$ = ast_create_prop_updates_list($1, $3);}
| prop_update {$$ = ast_create_prop_updates_list($1, (void*)0);}

prop_update:
  PROPERTY L_PAR property_id COMMA number_lit R_PAR {$$ = ast_create_prop_update($3, $5);}
| PROPERTY L_PAR property_id COMMA string_lit R_PAR {$$ = ast_create_prop_update($3, $5);}

drop_edge:
  specific_v_dot OUT_E L_PAR string_lit R_PAR DOT DROP_F {$$ = ast_create_graph_drop_e($1, $4, 1);}
| specific_v_dot IN_E L_PAR string_lit R_PAR DOT DROP_F {$$ = ast_create_graph_drop_e($1, $4, 0);}

add_vertex:
  ADD_VERTEX L_PAR string_lit COMMA prop_values_list R_PAR {$$ = ast_create_graph_add_v($3, $5);}

prop_values_list:
  string_lit COMMA prop_values_list {$$ = ast_create_prop_values($1, $3);}
| number_lit COMMA prop_values_list {$$ = ast_create_prop_values($1, $3);}
| string_lit {$$ = ast_create_prop_values($1, (void*) 0);}
| number_lit {$$ = ast_create_prop_values($1, (void*) 0);}

add_edge:
  ADD_EDGE L_PAR string_lit COMMA specific_v COMMA specific_v R_PAR {$$ = ast_create_graph_add_e($3, $5, $7);}

specific_v:
  V_F DOT has_label DOT v_path_pattern {$$ = ast_create_specific_v($3, $5);}
| V_F DOT has_label {$$ = ast_create_specific_v($3, (void*)0);}

specific_v_dot:
  V_F DOT has_label DOT v_path_pattern_dot {$$ = ast_create_specific_v($3, $5);}
| V_F DOT has_label DOT {$$ = ast_create_specific_v($3, (void*)0);}

has_label:
  HAS_LABEL L_PAR string_lit R_PAR {$$ = $3;}

v_path_pattern:
  condition_list {$$ = $1;}
| condition_list_dot edge_expr {$$ = ast_create_condition_pair($1, $2);}
| edge_expr {$$ = $1;}

v_path_pattern_dot:
  condition_list_dot {$$ = $1;}
| condition_list_dot edge_expr_dot {$$ = ast_create_condition_pair($1, $2);}
| edge_expr_dot {$$ = $1;}

condition_list:
  condition {$$ = $1;}
| condition DOT condition_list {$$ = ast_create_condition_pair($1, $3);}

condition_list_dot:
  condition DOT condition_list_dot {$$ = ast_create_condition_pair($1, $3);}
| condition DOT {$$ = ast_create_condition_pair($1, (void*)0);}

condition:
  filter_expr {$$ = $1;}
| has_expr {$$ = $1;}

edge_expr:
  edge_cond DOT has_label {$$ = ast_create_condition_pair($1, ast_create_specific_v($3, (void*)0));}
| edge_cond DOT has_label DOT v_path_pattern {$$ = ast_create_condition_pair($1, ast_create_specific_v($3, $5));}

edge_expr_dot:
  edge_cond DOT has_label DOT {$$ = ast_create_condition_pair($1, ast_create_specific_v($3, (void*)0));}
| edge_cond DOT has_label DOT v_path_pattern_dot {$$ = ast_create_condition_pair($1, ast_create_specific_v($3, $5));}

edge_cond:
  OUT L_PAR string_lit R_PAR {$$ = ast_create_condition_out($3);}
| IN L_PAR string_lit R_PAR {$$ = ast_create_condition_in($3);}

has_expr:
  HAS L_PAR property_id COMMA value_cond R_PAR {$$ = ast_create_condition_has($3, $5);}

number_lit:
  INTEGER_LIT {$$ = ast_create_int_literal($1);}
| DOUBLE_LIT {$$ = ast_create_double_literal($1);}

value_cond:
  number_lit {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_EQ, $1);}
| string_lit {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_EQ, $1);}
| NEQ L_PAR number_lit R_PAR {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_NEQ, $3);}
| GT L_PAR number_lit R_PAR {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_GT, $3);}
| LT L_PAR number_lit R_PAR {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_LT, $3);}
| GTE L_PAR number_lit R_PAR {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_GTE, $3);}
| LTE L_PAR number_lit R_PAR {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_LTE, $3);}
| CONTAINING L_PAR string_lit R_PAR {$$ = ast_create_value_cond(AST_NODE_VALUE_COND_CONTAINS, $3);}

property_id:
  INTEGER_LIT {$$ = ast_create_property_id(ast_create_int_literal($1));}

filter_expr:
  FILTER L_PAR filter_argument R_PAR {$$ = ast_create_condition_filter($3);}

filter_argument:
  OR L_PAR filter_argument COMMA filter_argument R_PAR {$$ = ast_create_condition_or($3, $5);}
| v_path_pattern {$$ = $1;}

schema_op: 
  s_vertex_op {$$ = $1;}
| s_edge_op {$$ = $1;}

v_label: VERTEX_LABEL L_PAR string_lit R_PAR {$$ = $3;}

string_lit: STRING_LIT {$$ = ast_create_string_literal($1);}

s_vertex_op: 
  v_label DOT DROP_F {$$ = ast_create_schema_drop_v($1);}
| v_label DOT prop_types_dot CREATE_F {$$= ast_create_schema_add_v($1, $3);}

prop_types_dot: 
  %empty {$$ = (void*)0;} 
| PROPERTIES_F DOT prop_types_list {$$ = $3;}

prop_types_list: 
  prop_type_dot prop_types_list {$$ = ast_create_prop_types_pair($1, $2);}
| prop_type_dot {$$ = ast_create_prop_types_pair($1, (void*)0);}

prop_type_dot:
  INT32_F DOT {$$ = ast_create_prop_types_int32();}
| INT64_F DOT {$$ = ast_create_prop_types_int64();}
| DOUBLE_F DOT {$$ = ast_create_prop_types_double();}
| BOOL_F DOT {$$ = ast_create_prop_types_bool();}
| STRING_F DOT {$$ = ast_create_prop_types_string();}

e_label: EDGE_LABEL L_PAR string_lit R_PAR {$$ = $3;}
s_edge_op: 
  e_label DOT CREATE_F {$$ = ast_create_schema_add_e($1);}
| e_label DOT DROP_F {$$ = ast_create_schema_drop_e($1);}

%%
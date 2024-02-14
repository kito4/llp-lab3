#pragma once

#ifndef _AST_API_H_
#define _AST_API_H_

#include <stdio.h>

struct AST;

struct AST* ast_parse();
struct AST* ast_parse_from_file(FILE* input);

void ast_free(struct AST* ast);
void ast_print(struct AST* ast, FILE* out);
void ast_graphviz(struct AST* ast, FILE* out);

#endif /* _AST_API_H_ */
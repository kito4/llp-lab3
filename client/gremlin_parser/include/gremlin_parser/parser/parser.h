/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CLIENT_GREMLIN_PARSER_INCLUDE_GREMLIN_PARSER_PARSER_PARSER_H_INCLUDED
# define YY_YY_CLIENT_GREMLIN_PARSER_INCLUDE_GREMLIN_PARSER_PARSER_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    DOT = 259,                     /* DOT  */
    COMMA = 260,                   /* COMMA  */
    L_PAR = 261,                   /* L_PAR  */
    R_PAR = 262,                   /* R_PAR  */
    SCHEMA = 263,                  /* SCHEMA  */
    CREATE_F = 264,                /* CREATE_F  */
    DROP_F = 265,                  /* DROP_F  */
    PROPERTIES_F = 266,            /* PROPERTIES_F  */
    INT32_F = 267,                 /* INT32_F  */
    INT64_F = 268,                 /* INT64_F  */
    DOUBLE_F = 269,                /* DOUBLE_F  */
    BOOL_F = 270,                  /* BOOL_F  */
    STRING_F = 271,                /* STRING_F  */
    VERTEX_LABEL = 272,            /* VERTEX_LABEL  */
    EDGE_LABEL = 273,              /* EDGE_LABEL  */
    ADD_EDGE = 274,                /* ADD_EDGE  */
    ADD_VERTEX = 275,              /* ADD_VERTEX  */
    OUT_E = 276,                   /* OUT_E  */
    IN_E = 277,                    /* IN_E  */
    PROPERTY = 278,                /* PROPERTY  */
    GRAPH = 279,                   /* GRAPH  */
    V_F = 280,                     /* V_F  */
    HAS = 281,                     /* HAS  */
    HAS_LABEL = 282,               /* HAS_LABEL  */
    OUT = 283,                     /* OUT  */
    IN = 284,                      /* IN  */
    FILTER = 285,                  /* FILTER  */
    VALUES_F = 286,                /* VALUES_F  */
    OR = 287,                      /* OR  */
    CONTAINING = 288,              /* CONTAINING  */
    NEQ = 289,                     /* NEQ  */
    GT = 290,                      /* GT  */
    LT = 291,                      /* LT  */
    GTE = 292,                     /* GTE  */
    LTE = 293,                     /* LTE  */
    INTEGER_LIT = 294,             /* INTEGER_LIT  */
    DOUBLE_LIT = 295,              /* DOUBLE_LIT  */
    STRING_LIT = 296               /* STRING_LIT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "client/gremlin_parser/parser/gremlin.y"

  char* as_string;
  int64_t as_int;
  double as_double;
  struct AST* as_ast;

#line 112 "client/gremlin_parser/include/gremlin_parser/parser/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CLIENT_GREMLIN_PARSER_INCLUDE_GREMLIN_PARSER_PARSER_PARSER_H_INCLUDED  */

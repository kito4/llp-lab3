/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* First part of user prologue.  */
#line 1 "client/gremlin_parser/parser/gremlin.y"

#include <stdint.h>
#include <stdio.h>

#include "ast.h"
#include "parser_res.h"

int yylex(void);
void yyerror(char const* err) {
  fprintf(stderr, "Parse Error: %s\n", err);
}

#line 84 "client/gremlin_parser/src/parser/parser.c"

#ifndef YY_CAST
#ifdef __cplusplus
#define YY_CAST(Type, Val) static_cast<Type>(Val)
#define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type>(Val)
#else
#define YY_CAST(Type, Val) ((Type)(Val))
#define YY_REINTERPRET_CAST(Type, Val) ((Type)(Val))
#endif
#endif
#ifndef YY_NULLPTR
#if defined __cplusplus
#if 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#else
#define YY_NULLPTR ((void*)0)
#endif
#endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t {
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,               /* "end of file"  */
  YYSYMBOL_YYerror = 1,             /* error  */
  YYSYMBOL_YYUNDEF = 2,             /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,           /* SEMICOLON  */
  YYSYMBOL_DOT = 4,                 /* DOT  */
  YYSYMBOL_COMMA = 5,               /* COMMA  */
  YYSYMBOL_L_PAR = 6,               /* L_PAR  */
  YYSYMBOL_R_PAR = 7,               /* R_PAR  */
  YYSYMBOL_SCHEMA = 8,              /* SCHEMA  */
  YYSYMBOL_CREATE_F = 9,            /* CREATE_F  */
  YYSYMBOL_DROP_F = 10,             /* DROP_F  */
  YYSYMBOL_PROPERTIES_F = 11,       /* PROPERTIES_F  */
  YYSYMBOL_INT32_F = 12,            /* INT32_F  */
  YYSYMBOL_INT64_F = 13,            /* INT64_F  */
  YYSYMBOL_DOUBLE_F = 14,           /* DOUBLE_F  */
  YYSYMBOL_BOOL_F = 15,             /* BOOL_F  */
  YYSYMBOL_STRING_F = 16,           /* STRING_F  */
  YYSYMBOL_VERTEX_LABEL = 17,       /* VERTEX_LABEL  */
  YYSYMBOL_EDGE_LABEL = 18,         /* EDGE_LABEL  */
  YYSYMBOL_ADD_EDGE = 19,           /* ADD_EDGE  */
  YYSYMBOL_ADD_VERTEX = 20,         /* ADD_VERTEX  */
  YYSYMBOL_OUT_E = 21,              /* OUT_E  */
  YYSYMBOL_IN_E = 22,               /* IN_E  */
  YYSYMBOL_PROPERTY = 23,           /* PROPERTY  */
  YYSYMBOL_GRAPH = 24,              /* GRAPH  */
  YYSYMBOL_V_F = 25,                /* V_F  */
  YYSYMBOL_HAS = 26,                /* HAS  */
  YYSYMBOL_HAS_LABEL = 27,          /* HAS_LABEL  */
  YYSYMBOL_OUT = 28,                /* OUT  */
  YYSYMBOL_IN = 29,                 /* IN  */
  YYSYMBOL_FILTER = 30,             /* FILTER  */
  YYSYMBOL_VALUES_F = 31,           /* VALUES_F  */
  YYSYMBOL_OR = 32,                 /* OR  */
  YYSYMBOL_CONTAINING = 33,         /* CONTAINING  */
  YYSYMBOL_NEQ = 34,                /* NEQ  */
  YYSYMBOL_GT = 35,                 /* GT  */
  YYSYMBOL_LT = 36,                 /* LT  */
  YYSYMBOL_GTE = 37,                /* GTE  */
  YYSYMBOL_LTE = 38,                /* LTE  */
  YYSYMBOL_INTEGER_LIT = 39,        /* INTEGER_LIT  */
  YYSYMBOL_DOUBLE_LIT = 40,         /* DOUBLE_LIT  */
  YYSYMBOL_STRING_LIT = 41,         /* STRING_LIT  */
  YYSYMBOL_YYACCEPT = 42,           /* $accept  */
  YYSYMBOL_query = 43,              /* query  */
  YYSYMBOL_graph_op = 44,           /* graph_op  */
  YYSYMBOL_prop_updates_list = 45,  /* prop_updates_list  */
  YYSYMBOL_prop_update = 46,        /* prop_update  */
  YYSYMBOL_drop_edge = 47,          /* drop_edge  */
  YYSYMBOL_add_vertex = 48,         /* add_vertex  */
  YYSYMBOL_prop_values_list = 49,   /* prop_values_list  */
  YYSYMBOL_add_edge = 50,           /* add_edge  */
  YYSYMBOL_specific_v = 51,         /* specific_v  */
  YYSYMBOL_specific_v_dot = 52,     /* specific_v_dot  */
  YYSYMBOL_has_label = 53,          /* has_label  */
  YYSYMBOL_v_path_pattern = 54,     /* v_path_pattern  */
  YYSYMBOL_v_path_pattern_dot = 55, /* v_path_pattern_dot  */
  YYSYMBOL_condition_list = 56,     /* condition_list  */
  YYSYMBOL_condition_list_dot = 57, /* condition_list_dot  */
  YYSYMBOL_condition = 58,          /* condition  */
  YYSYMBOL_edge_expr = 59,          /* edge_expr  */
  YYSYMBOL_edge_expr_dot = 60,      /* edge_expr_dot  */
  YYSYMBOL_edge_cond = 61,          /* edge_cond  */
  YYSYMBOL_has_expr = 62,           /* has_expr  */
  YYSYMBOL_number_lit = 63,         /* number_lit  */
  YYSYMBOL_value_cond = 64,         /* value_cond  */
  YYSYMBOL_property_id = 65,        /* property_id  */
  YYSYMBOL_filter_expr = 66,        /* filter_expr  */
  YYSYMBOL_filter_argument = 67,    /* filter_argument  */
  YYSYMBOL_schema_op = 68,          /* schema_op  */
  YYSYMBOL_v_label = 69,            /* v_label  */
  YYSYMBOL_string_lit = 70,         /* string_lit  */
  YYSYMBOL_s_vertex_op = 71,        /* s_vertex_op  */
  YYSYMBOL_prop_types_dot = 72,     /* prop_types_dot  */
  YYSYMBOL_prop_types_list = 73,    /* prop_types_list  */
  YYSYMBOL_prop_type_dot = 74,      /* prop_type_dot  */
  YYSYMBOL_e_label = 75,            /* e_label  */
  YYSYMBOL_s_edge_op = 76           /* s_edge_op  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;

#ifdef short
#undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
#include <limits.h> /* INFRINGES ON USER NAME SPACE */
#if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#define YY_STDINT_H
#endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
#undef UINT_LEAST8_MAX
#undef UINT_LEAST16_MAX
#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
#if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#define YYPTRDIFF_T __PTRDIFF_TYPE__
#define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
#elif defined PTRDIFF_MAX
#ifndef ptrdiff_t
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#endif
#define YYPTRDIFF_T ptrdiff_t
#define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
#else
#define YYPTRDIFF_T long
#define YYPTRDIFF_MAXIMUM LONG_MAX
#endif
#endif

#ifndef YYSIZE_T
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned
#endif
#endif

#define YYSIZE_MAXIMUM \
  YY_CAST(YYPTRDIFF_T, (YYPTRDIFF_MAXIMUM < YY_CAST(YYSIZE_T, -1) ? YYPTRDIFF_MAXIMUM : YY_CAST(YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST(YYPTRDIFF_T, sizeof(X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#define YY_(Msgid) dgettext("bison-runtime", Msgid)
#endif
#endif
#ifndef YY_
#define YY_(Msgid) Msgid
#endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_PURE __attribute__((__pure__))
#else
#define YY_ATTRIBUTE_PURE
#endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define YY_ATTRIBUTE_UNUSED
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
#define YY_USE(E) ((void)(E))
#else
#define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && !defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
#if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")
#else
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                                            \
  _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"") \
      _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#endif
#define YY_IGNORE_MAYBE_UNINITIALIZED_END _Pragma("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
#define YY_IGNORE_USELESS_CAST_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
#define YY_IGNORE_USELESS_CAST_END _Pragma("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_END
#endif

#define YY_ASSERT(E) ((void)(0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#ifdef YYSTACK_USE_ALLOCA
#if YYSTACK_USE_ALLOCA
#ifdef __GNUC__
#define YYSTACK_ALLOC __builtin_alloca
#elif defined __BUILTIN_VA_ARG_INCR
#include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#elif defined _AIX
#define YYSTACK_ALLOC __alloca
#elif defined _MSC_VER
#include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#define alloca _alloca
#else
#define YYSTACK_ALLOC alloca
#if !defined _ALLOCA_H && !defined EXIT_SUCCESS
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
/* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#endif
#endif
#endif

#ifdef YYSTACK_ALLOC
/* Pacify GCC's 'empty if-body' warning.  */
#define YYSTACK_FREE(Ptr) \
  do { /* empty */        \
    ;                     \
  } while (0)
#ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#endif
#else
#define YYSTACK_ALLOC YYMALLOC
#define YYSTACK_FREE YYFREE
#ifndef YYSTACK_ALLOC_MAXIMUM
#define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#endif
#if (defined __cplusplus && !defined EXIT_SUCCESS && \
     !((defined YYMALLOC || defined malloc) && (defined YYFREE || defined free)))
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#if !defined malloc && !defined EXIT_SUCCESS
void* malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#ifndef YYFREE
#define YYFREE free
#if !defined free && !defined EXIT_SUCCESS
void free(void*); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#endif
#endif /* 1 */

#if (!defined yyoverflow && (!defined __cplusplus || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#define YYSTACK_GAP_MAXIMUM (YYSIZEOF(union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#define YYSTACK_BYTES(N) ((N) * (YYSIZEOF(yy_state_t) + YYSIZEOF(YYSTYPE)) + YYSTACK_GAP_MAXIMUM)

#define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
  do {                                                                 \
    YYPTRDIFF_T yynewbytes;                                            \
    YYCOPY(&yyptr->Stack_alloc, Stack, yysize);                        \
    Stack = &yyptr->Stack_alloc;                                       \
    yynewbytes = yystacksize * YYSIZEOF(*Stack) + YYSTACK_GAP_MAXIMUM; \
    yyptr += yynewbytes / YYSIZEOF(*yyptr);                            \
  } while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
#ifndef YYCOPY
#if defined __GNUC__ && 1 < __GNUC__
#define YYCOPY(Dst, Src, Count) __builtin_memcpy(Dst, Src, YY_CAST(YYSIZE_T, (Count)) * sizeof(*(Src)))
#else
#define YYCOPY(Dst, Src, Count)         \
  do {                                  \
    YYPTRDIFF_T yyi;                    \
    for (yyi = 0; yyi < (Count); yyi++) \
      (Dst)[yyi] = (Src)[yyi];          \
  } while (0)
#endif
#endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL 6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 35
/* YYNRULES -- Number of rules.  */
#define YYNRULES 77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 188

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 296

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX) \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? YY_CAST(yysymbol_kind_t, yytranslate[YYX]) : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] = {
    0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] = {0,   113, 113, 114, 117, 118, 119, 120, 121, 122, 125, 126, 129, 130, 133, 134,
                                       137, 140, 141, 142, 143, 146, 149, 150, 153, 154, 157, 160, 161, 162, 165, 166,
                                       167, 170, 171, 174, 175, 178, 179, 182, 183, 186, 187, 190, 191, 194, 197, 198,
                                       201, 202, 203, 204, 205, 206, 207, 208, 211, 214, 217, 218, 221, 222, 224, 226,
                                       229, 230, 233, 234, 237, 238, 241, 242, 243, 244, 245, 247, 249, 250};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST(yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char* yysymbol_name(yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char* const yytname[] = {"\"end of file\"",
                                      "error",
                                      "\"invalid token\"",
                                      "SEMICOLON",
                                      "DOT",
                                      "COMMA",
                                      "L_PAR",
                                      "R_PAR",
                                      "SCHEMA",
                                      "CREATE_F",
                                      "DROP_F",
                                      "PROPERTIES_F",
                                      "INT32_F",
                                      "INT64_F",
                                      "DOUBLE_F",
                                      "BOOL_F",
                                      "STRING_F",
                                      "VERTEX_LABEL",
                                      "EDGE_LABEL",
                                      "ADD_EDGE",
                                      "ADD_VERTEX",
                                      "OUT_E",
                                      "IN_E",
                                      "PROPERTY",
                                      "GRAPH",
                                      "V_F",
                                      "HAS",
                                      "HAS_LABEL",
                                      "OUT",
                                      "IN",
                                      "FILTER",
                                      "VALUES_F",
                                      "OR",
                                      "CONTAINING",
                                      "NEQ",
                                      "GT",
                                      "LT",
                                      "GTE",
                                      "LTE",
                                      "INTEGER_LIT",
                                      "DOUBLE_LIT",
                                      "STRING_LIT",
                                      "$accept",
                                      "query",
                                      "graph_op",
                                      "prop_updates_list",
                                      "prop_update",
                                      "drop_edge",
                                      "add_vertex",
                                      "prop_values_list",
                                      "add_edge",
                                      "specific_v",
                                      "specific_v_dot",
                                      "has_label",
                                      "v_path_pattern",
                                      "v_path_pattern_dot",
                                      "condition_list",
                                      "condition_list_dot",
                                      "condition",
                                      "edge_expr",
                                      "edge_expr_dot",
                                      "edge_cond",
                                      "has_expr",
                                      "number_lit",
                                      "value_cond",
                                      "property_id",
                                      "filter_expr",
                                      "filter_argument",
                                      "schema_op",
                                      "v_label",
                                      "string_lit",
                                      "s_vertex_op",
                                      "prop_types_dot",
                                      "prop_types_list",
                                      "prop_type_dot",
                                      "e_label",
                                      "s_edge_op",
                                      YY_NULLPTR};

static const char* yysymbol_name(yysymbol_kind_t yysymbol) {
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {
    4,    11,   59,   13,   22,   5,    -134, 63,   71,   -134, 74,   -134, 75,   -134, 79,   83,   86,   -134, -134,
    -134, -134, 0,    52,   52,   41,   58,   52,   52,   67,   -134, 90,   91,   92,   -134, 96,   97,   -134, 93,
    95,   -134, 99,   98,   -134, -134, 100,  101,  102,  105,  52,   52,   65,   -134, 87,   -134, -134, 45,   -134,
    88,   -5,   52,   36,   104,  107,  -134, 110,  -134, 108,  112,  113,  114,  116,  -134, 45,   117,  118,  -134,
    -134, 115,  119,  120,  121,  123,  124,  125,  126,  -134, 42,   122,  -134, 129,  -134, -134, 130,  131,  -5,
    -134, -134, -134, -134, -134, -134, 67,   88,   -134, -5,   -5,   -134, 65,   52,   52,   -12,  -134, 3,    67,
    127,  128,  132,  133,  137,  136,  -134, -134, 139,  138,  140,  142,  -134, -134, 42,   145,  -134, 146,  144,
    -134, 148,  -134, -134, -134, -134, 36,   -134, 9,    -134, -134, -12,  -134, 3,    67,   -134, 36,   -134, 147,
    149,  150,  151,  152,  153,  -134, 154,  -134, 141,  -134, 156,  -134, 52,   34,   34,   34,   34,   34,   -134,
    -12,  36,   155,  157,  158,  159,  160,  161,  162,  -134, -134, -134, -134, -134, -134, -134, -134};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] = {
    0,  0,  0,  0,  0,  0,  1,  0,  0,  2,  0,  60, 0,  61, 0,  0,  0,  3,  6,  7,  8,  0,  0,  0,  66, 0,  0,
    0,  0,  5,  0,  0,  0,  4,  0,  11, 63, 0,  0,  64, 0,  0,  76, 77, 0,  0,  0,  0,  0,  0,  0,  9,  0,  62,
    75, 0,  65, 0,  0,  0,  25, 0,  0,  56, 0,  10, 0,  0,  0,  0,  0,  67, 69, 0,  0,  46, 47, 0,  20, 19, 0,
    0,  0,  0,  0,  24, 30, 0,  32, 0,  38, 37, 0,  0,  0,  70, 71, 72, 73, 74, 68, 0,  0,  16, 0,  0,  26, 0,
    0,  0,  0,  31, 36, 0,  0,  0,  0,  0,  23, 0,  18, 17, 0,  0,  0,  0,  59, 27, 0,  33, 29, 0,  0,  35, 0,
    14, 15, 12, 13, 0,  21, 0,  43, 44, 0,  28, 36, 0,  57, 41, 22, 0,  0,  0,  0,  0,  0,  48, 0,  49, 0,  34,
    39, 42, 0,  0,  0,  0,  0,  0,  45, 0,  0,  0,  0,  0,  0,  0,  0,  0,  40, 55, 50, 51, 52, 53, 54, 58};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-134, -134, -134, 84,   -134, -134, -134, -29, -134, 25,   -134, -94,
                                       -131, 14,   8,    -58,  -57,  43,   89,   -54, -134, -85,  -134, 66,
                                       -134, -133, -134, -134, -22,  -134, -134, 106, -134, -134, -134};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] = {0,  3,   17, 34, 35,  18, 19, 77,  20, 74, 21, 47, 126, 85, 127, 128, 129, 130,
                                         88, 131, 90, 78, 158, 64, 91, 132, 9,  10, 79, 11, 41,  71, 72,  12,  13};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] = {
    37,  38,  86,  87,  44,  45,  89,  118, 150, 116, 29,  160, 1,   6,   81,  4,   82,  83,  84,  134, 125, 30,  31,
    32,  14,  15,  61,  62,  2,   81,  16,  33,  89,  84,  75,  76,  36,  80,  179, 7,   8,   180, 151, 152, 153, 154,
    155, 156, 75,  76,  36,  39,  40,  162, 133, 87,  157, 66,  67,  68,  69,  70,  81,  5,   82,  83,  84,  42,  43,
    22,  82,  83,  117, 75,  76,  120, 121, 23,  24,  25,  174, 175, 176, 177, 178, 26,  123, 124, 133, 27,  28,  86,
    87,  36,  46,  89,  48,  49,  50,  51,  53,  52,  54,  55,  63,  57,  58,  56,  59,  60,  32,  92,  95,  73,  93,
    94,  96,  97,  98,  159, 99,  101, 103, 102, 104, 105, 112, 119, 106, 107, 108, 109, 110, 113, 114, 115, 65,  135,
    136, 137, 138, 139, 173, 140, 141, 142, 171, 143, 144, 146, 147, 148, 149, 164, 161, 165, 166, 167, 168, 169, 172,
    170, 181, 163, 182, 183, 184, 185, 186, 187, 0,   145, 0,   122, 0,   111, 0,   0,   100};

static const yytype_int16 yycheck[] = {
    22,  23, 60,  60,  26,  27, 60,  101, 139, 94,  10,  144, 8,   0,   26,  4,   28,  29,  30,  113, 32, 21, 22,
    23,  19, 20,  48,  49,  24, 26,  25,  31,  86,  30,  39,  40,  41,  59,  171, 17,  18,  172, 33,  34, 35, 36,
    37,  38, 39,  40,  41,  10, 11,  147, 112, 112, 141, 12,  13,  14,  15,  16,  26,  4,   28,  29,  30, 9,  10,
    6,   28, 29,  94,  39,  40, 104, 105, 6,   4,   4,   165, 166, 167, 168, 169, 6,   108, 109, 146, 6,  4,  149,
    149, 41, 27,  149, 6,   6,  6,   3,   7,   4,   7,   4,   39,  5,   5,   9,   6,   4,   23,  7,   4,  25, 7,
    5,   4,  4,   4,   141, 4,  4,   7,   5,   5,   5,   4,   102, 7,   6,   6,   6,   6,   4,   4,   4,  52, 10,
    10,  7,  7,   4,   164, 7,  5,   7,   5,   7,   6,   4,   4,   7,   4,   6,   146, 6,   6,   6,   6,  6,  4,
    7,   7,  149, 7,   7,   7,  7,   7,   7,   -1,  128, -1,  107, -1,  86,  -1,  -1,  72};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] = {
    0,  8,  24, 43, 4,  4,  0,  17, 18, 68, 69, 71, 75, 76, 19, 20, 25, 44, 47, 48, 50, 52, 6,  6,  4,  4,  6,
    6,  4,  10, 21, 22, 23, 31, 45, 46, 41, 70, 70, 10, 11, 72, 9,  10, 70, 70, 27, 53, 6,  6,  6,  3,  4,  7,
    7,  4,  9,  5,  5,  6,  4,  70, 70, 39, 65, 45, 12, 13, 14, 15, 16, 73, 74, 25, 51, 39, 40, 49, 63, 70, 70,
    26, 28, 29, 30, 55, 57, 58, 60, 61, 62, 66, 7,  7,  5,  4,  4,  4,  4,  4,  73, 4,  5,  7,  5,  5,  7,  6,
    6,  6,  6,  60, 4,  4,  4,  4,  63, 70, 53, 51, 49, 49, 65, 70, 70, 32, 54, 56, 57, 58, 59, 61, 67, 57, 53,
    10, 10, 7,  7,  4,  7,  5,  7,  7,  6,  59, 4,  4,  7,  4,  54, 33, 34, 35, 36, 37, 38, 63, 64, 70, 67, 56,
    53, 55, 6,  6,  6,  6,  6,  6,  7,  5,  4,  70, 63, 63, 63, 63, 63, 67, 54, 7,  7,  7,  7,  7,  7,  7};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] = {0,  42, 43, 43, 44, 44, 44, 44, 44, 44, 45, 45, 46, 46, 47, 47, 48, 49, 49, 49,
                                   49, 50, 51, 51, 52, 52, 53, 54, 54, 54, 55, 55, 55, 56, 56, 57, 57, 58, 58, 59,
                                   59, 60, 60, 61, 61, 62, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 65, 66, 67, 67,
                                   68, 68, 69, 70, 71, 71, 72, 72, 73, 73, 74, 74, 74, 74, 74, 75, 76, 76};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] = {0, 2, 3, 3, 2, 2, 1, 1, 1, 3, 3, 1, 6, 6, 7, 7, 6, 3, 3, 1, 1, 8, 5, 3, 5, 4,
                                   4, 1, 2, 1, 1, 2, 1, 1, 3, 3, 2, 1, 1, 3, 5, 4, 5, 4, 4, 6, 1, 1, 1, 1, 4, 4,
                                   4, 4, 4, 4, 1, 4, 6, 1, 1, 1, 4, 1, 3, 4, 0, 3, 2, 1, 2, 2, 2, 2, 2, 4, 3, 3};

enum { YYENOMEM = -2 };

#define yyerrok (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYNOMEM goto yyexhaustedlab

#define YYRECOVERING() (!!yyerrstatus)

#define YYBACKUP(Token, Value)                      \
  do                                                \
    if (yychar == YYEMPTY) {                        \
      yychar = (Token);                             \
      yylval = (Value);                             \
      YYPOPSTACK(yylen);                            \
      yystate = *yyssp;                             \
      goto yybackup;                                \
    } else {                                        \
      yyerror(YY_("syntax error: cannot back up")); \
      YYERROR;                                      \
    }                                               \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* Enable debugging if requested.  */
#if YYDEBUG

#ifndef YYFPRINTF
#include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#define YYFPRINTF fprintf
#endif

#define YYDPRINTF(Args) \
  do {                  \
    if (yydebug)        \
      YYFPRINTF Args;   \
  } while (0)

#define YY_SYMBOL_PRINT(Title, Kind, Value, Location) \
  do {                                                \
    if (yydebug) {                                    \
      YYFPRINTF(stderr, "%s ", Title);                \
      yy_symbol_print(stderr, Kind, Value);           \
      YYFPRINTF(stderr, "\n");                        \
    }                                                 \
  } while (0)

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void yy_symbol_value_print(FILE* yyo, yysymbol_kind_t yykind, YYSTYPE const* const yyvaluep) {
  FILE* yyoutput = yyo;
  YY_USE(yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void yy_symbol_print(FILE* yyo, yysymbol_kind_t yykind, YYSTYPE const* const yyvaluep) {
  YYFPRINTF(yyo, "%s %s (", yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name(yykind));

  yy_symbol_value_print(yyo, yykind, yyvaluep);
  YYFPRINTF(yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void yy_stack_print(yy_state_t* yybottom, yy_state_t* yytop) {
  YYFPRINTF(stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++) {
    int yybot = *yybottom;
    YYFPRINTF(stderr, " %d", yybot);
  }
  YYFPRINTF(stderr, "\n");
}

#define YY_STACK_PRINT(Bottom, Top)    \
  do {                                 \
    if (yydebug)                       \
      yy_stack_print((Bottom), (Top)); \
  } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void yy_reduce_print(yy_state_t* yyssp, YYSTYPE* yyvsp, int yyrule) {
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %d):\n", yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++) {
    YYFPRINTF(stderr, "   $%d = ", yyi + 1);
    yy_symbol_print(stderr, YY_ACCESSING_SYMBOL(+yyssp[yyi + 1 - yynrhs]), &yyvsp[(yyi + 1) - (yynrhs)]);
    YYFPRINTF(stderr, "\n");
  }
}

#define YY_REDUCE_PRINT(Rule)              \
  do {                                     \
    if (yydebug)                           \
      yy_reduce_print(yyssp, yyvsp, Rule); \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
#define YYDPRINTF(Args) ((void)0)
#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
#define YY_STACK_PRINT(Bottom, Top)
#define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Context of a parse error.  */
typedef struct {
  yy_state_t* yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int yypcontext_expected_tokens(const yypcontext_t* yyctx, yysymbol_kind_t yyarg[], int yyargn) {
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default(yyn)) {
    /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
    int yyxbegin = yyn < 0 ? -yyn : 0;
    /* Stay within bounds of both yycheck and yytname.  */
    int yychecklim = YYLAST - yyn + 1;
    int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
    int yyx;
    for (yyx = yyxbegin; yyx < yyxend; ++yyx)
      if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror && !yytable_value_is_error(yytable[yyx + yyn])) {
        if (!yyarg)
          ++yycount;
        else if (yycount == yyargn)
          return 0;
        else
          yyarg[yycount++] = YY_CAST(yysymbol_kind_t, yyx);
      }
  }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}

#ifndef yystrlen
#if defined __GLIBC__ && defined _STRING_H
#define yystrlen(S) (YY_CAST(YYPTRDIFF_T, strlen(S)))
#else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T yystrlen(const char* yystr) {
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#endif
#endif

#ifndef yystpcpy
#if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#define yystpcpy stpcpy
#else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char* yystpcpy(char* yydest, const char* yysrc) {
  char* yyd = yydest;
  const char* yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T yytnamerr(char* yyres, const char* yystr) {
  if (*yystr == '"') {
    YYPTRDIFF_T yyn = 0;
    char const* yyp = yystr;
    for (;;)
      switch (*++yyp) {
        case '\'':
        case ',':
          goto do_not_strip_quotes;

        case '\\':
          if (*++yyp != '\\')
            goto do_not_strip_quotes;
          else
            goto append;

        append:
        default:
          if (yyres)
            yyres[yyn] = *yyp;
          yyn++;
          break;

        case '"':
          if (yyres)
            yyres[yyn] = '\0';
          return yyn;
      }
  do_not_strip_quotes:;
  }

  if (yyres)
    return yystpcpy(yyres, yystr) - yyres;
  else
    return yystrlen(yystr);
}
#endif

static int yy_syntax_error_arguments(const yypcontext_t* yyctx, yysymbol_kind_t yyarg[], int yyargn) {
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY) {
    int yyn;
    if (yyarg)
      yyarg[yycount] = yyctx->yytoken;
    ++yycount;
    yyn = yypcontext_expected_tokens(yyctx, yyarg ? yyarg + 1 : yyarg, yyargn - 1);
    if (yyn == YYENOMEM)
      return YYENOMEM;
    else
      yycount += yyn;
  }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int yysyntax_error(YYPTRDIFF_T* yymsg_alloc, char** yymsg, const yypcontext_t* yyctx) {
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char* yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments(yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount) {
#define YYCASE_(N, S) \
  case N:             \
    yyformat = S;     \
    break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
  }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen(yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi) {
      YYPTRDIFF_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyarg[yyi]]);
      if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
        yysize = yysize1;
      else
        return YYENOMEM;
    }
  }

  if (*yymsg_alloc < yysize) {
    *yymsg_alloc = 2 * yysize;
    if (!(yysize <= *yymsg_alloc && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
      *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
    return -1;
  }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char* yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount) {
        yyp += yytnamerr(yyp, yytname[yyarg[yyi++]]);
        yyformat += 2;
      } else {
        ++yyp;
        ++yyformat;
      }
  }
  return 0;
}

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void yydestruct(const char* yymsg, yysymbol_kind_t yykind, YYSTYPE* yyvaluep) {
  YY_USE(yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT(yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind) {
    case YYSYMBOL_STRING_LIT: /* STRING_LIT  */
#line 107 "client/gremlin_parser/parser/gremlin.y"
    {
      free(((*yyvaluep).as_string));
    }
#line 1274 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_graph_op: /* graph_op  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1282 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_prop_updates_list: /* prop_updates_list  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1290 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_prop_update: /* prop_update  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1298 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_drop_edge: /* drop_edge  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1306 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_add_vertex: /* add_vertex  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1314 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_prop_values_list: /* prop_values_list  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1322 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_add_edge: /* add_edge  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1330 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_specific_v: /* specific_v  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1338 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_specific_v_dot: /* specific_v_dot  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1346 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_has_label: /* has_label  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1354 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_v_path_pattern: /* v_path_pattern  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1362 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_v_path_pattern_dot: /* v_path_pattern_dot  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1370 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_condition_list: /* condition_list  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1378 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_condition_list_dot: /* condition_list_dot  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1386 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_condition: /* condition  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1394 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_edge_expr: /* edge_expr  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1402 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_edge_expr_dot: /* edge_expr_dot  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1410 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_edge_cond: /* edge_cond  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1418 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_has_expr: /* has_expr  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1426 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_number_lit: /* number_lit  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1434 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_value_cond: /* value_cond  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1442 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_property_id: /* property_id  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1450 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_filter_expr: /* filter_expr  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1458 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_filter_argument: /* filter_argument  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1466 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_schema_op: /* schema_op  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1474 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_v_label: /* v_label  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1482 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_string_lit: /* string_lit  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1490 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_s_vertex_op: /* s_vertex_op  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1498 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_prop_types_dot: /* prop_types_dot  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1506 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_prop_types_list: /* prop_types_list  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1514 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_prop_type_dot: /* prop_type_dot  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1522 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_e_label: /* e_label  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1530 "client/gremlin_parser/src/parser/parser.c"
    break;

    case YYSYMBOL_s_edge_op: /* s_edge_op  */
#line 103 "client/gremlin_parser/parser/gremlin.y"
    {
      ast_free(((*yyvaluep).as_ast));
    }
#line 1538 "client/gremlin_parser/src/parser/parser.c"
    break;

    default:
      break;
  }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

int yyparse(void) {
  yy_state_fast_t yystate = 0;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus = 0;

  /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

  /* Their size.  */
  YYPTRDIFF_T yystacksize = YYINITDEPTH;

  /* The state stack: array, bottom, top.  */
  yy_state_t yyssa[YYINITDEPTH];
  yy_state_t* yyss = yyssa;
  yy_state_t* yyssp = yyss;

  /* The semantic value stack: array, bottom, top.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE* yyvs = yyvsa;
  YYSTYPE* yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char* yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N) (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF((stderr, "Entering state %d\n", yystate));
  YY_ASSERT(0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST(yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT(yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
  {
    /* Get the current used size of the three stacks, in elements.  */
    YYPTRDIFF_T yysize = yyssp - yyss + 1;

#if defined yyoverflow
    {
      /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
      yy_state_t* yyss1 = yyss;
      YYSTYPE* yyvs1 = yyvs;

      /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
      yyoverflow(YY_("memory exhausted"), &yyss1, yysize * YYSIZEOF(*yyssp), &yyvs1, yysize * YYSIZEOF(*yyvsp),
                 &yystacksize);
      yyss = yyss1;
      yyvs = yyvs1;
    }
#else /* defined YYSTACK_RELOCATE */
    /* Extend the stack our own way.  */
    if (YYMAXDEPTH <= yystacksize)
      YYNOMEM;
    yystacksize *= 2;
    if (YYMAXDEPTH < yystacksize)
      yystacksize = YYMAXDEPTH;

    {
      yy_state_t* yyss1 = yyss;
      union yyalloc* yyptr = YY_CAST(union yyalloc*, YYSTACK_ALLOC(YY_CAST(YYSIZE_T, YYSTACK_BYTES(yystacksize))));
      if (!yyptr)
        YYNOMEM;
      YYSTACK_RELOCATE(yyss_alloc, yyss);
      YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#undef YYSTACK_RELOCATE
      if (yyss1 != yyssa)
        YYSTACK_FREE(yyss1);
    }
#endif

    yyssp = yyss + yysize - 1;
    yyvsp = yyvs + yysize - 1;

    YY_IGNORE_USELESS_CAST_BEGIN
    YYDPRINTF((stderr, "Stack size increased to %ld\n", YY_CAST(long, yystacksize)));
    YY_IGNORE_USELESS_CAST_END

    if (yyss + yystacksize - 1 <= yyssp)
      YYABORT;
  }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY) {
    YYDPRINTF((stderr, "Reading a token\n"));
    yychar = yylex();
  }

  if (yychar <= YYEOF) {
    yychar = YYEOF;
    yytoken = YYSYMBOL_YYEOF;
    YYDPRINTF((stderr, "Now at end of input.\n"));
  } else if (yychar == YYerror) {
    /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
    yychar = YYUNDEF;
    yytoken = YYSYMBOL_YYerror;
    goto yyerrlab1;
  } else {
    yytoken = YYTRANSLATE(yychar);
    YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
  }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0) {
    if (yytable_value_is_error(yyn))
      goto yyerrlab;
    yyn = -yyn;
    goto yyreduce;
  }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;

/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;

/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1 - yylen];

  YY_REDUCE_PRINT(yyn);
  switch (yyn) {
    case 2: /* query: SCHEMA DOT schema_op  */
#line 113 "client/gremlin_parser/parser/gremlin.y"
    {
      set_parse_result((yyvsp[0].as_ast));
      YYACCEPT;
    }
#line 1811 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 3: /* query: GRAPH DOT graph_op  */
#line 114 "client/gremlin_parser/parser/gremlin.y"
    {
      set_parse_result((yyvsp[0].as_ast));
      YYACCEPT;
    }
#line 1817 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 4: /* graph_op: specific_v_dot VALUES_F  */
#line 117 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_select((yyvsp[-1].as_ast));
    }
#line 1823 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 5: /* graph_op: specific_v_dot DROP_F  */
#line 118 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_drop_v((yyvsp[-1].as_ast));
    }
#line 1829 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 6: /* graph_op: drop_edge  */
#line 119 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1835 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 7: /* graph_op: add_vertex  */
#line 120 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1841 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 8: /* graph_op: add_edge  */
#line 121 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1847 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 9: /* graph_op: specific_v_dot prop_updates_list SEMICOLON  */
#line 122 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_update((yyvsp[-2].as_ast), (yyvsp[-1].as_ast));
    }
#line 1853 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 10: /* prop_updates_list: prop_update DOT prop_updates_list  */
#line 125 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_updates_list((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 1859 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 11: /* prop_updates_list: prop_update  */
#line 126 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_updates_list((yyvsp[0].as_ast), (void*)0);
    }
#line 1865 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 12: /* prop_update: PROPERTY L_PAR property_id COMMA number_lit R_PAR  */
#line 129 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_update((yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 1871 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 13: /* prop_update: PROPERTY L_PAR property_id COMMA string_lit R_PAR  */
#line 130 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_update((yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 1877 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 14: /* drop_edge: specific_v_dot OUT_E L_PAR string_lit R_PAR DOT DROP_F  */
#line 133 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_drop_e((yyvsp[-6].as_ast), (yyvsp[-3].as_ast), 1);
    }
#line 1883 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 15: /* drop_edge: specific_v_dot IN_E L_PAR string_lit R_PAR DOT DROP_F  */
#line 134 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_drop_e((yyvsp[-6].as_ast), (yyvsp[-3].as_ast), 0);
    }
#line 1889 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 16: /* add_vertex: ADD_VERTEX L_PAR string_lit COMMA prop_values_list R_PAR  */
#line 137 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_add_v((yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 1895 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 17: /* prop_values_list: string_lit COMMA prop_values_list  */
#line 140 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_values((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 1901 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 18: /* prop_values_list: number_lit COMMA prop_values_list  */
#line 141 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_values((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 1907 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 19: /* prop_values_list: string_lit  */
#line 142 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_values((yyvsp[0].as_ast), (void*)0);
    }
#line 1913 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 20: /* prop_values_list: number_lit  */
#line 143 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_values((yyvsp[0].as_ast), (void*)0);
    }
#line 1919 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 21: /* add_edge: ADD_EDGE L_PAR string_lit COMMA specific_v COMMA specific_v R_PAR  */
#line 146 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_graph_add_e((yyvsp[-5].as_ast), (yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 1925 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 22: /* specific_v: V_F DOT has_label DOT v_path_pattern  */
#line 149 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_specific_v((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 1931 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 23: /* specific_v: V_F DOT has_label  */
#line 150 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_specific_v((yyvsp[0].as_ast), (void*)0);
    }
#line 1937 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 24: /* specific_v_dot: V_F DOT has_label DOT v_path_pattern_dot  */
#line 153 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_specific_v((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 1943 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 25: /* specific_v_dot: V_F DOT has_label DOT  */
#line 154 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_specific_v((yyvsp[-1].as_ast), (void*)0);
    }
#line 1949 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 26: /* has_label: HAS_LABEL L_PAR string_lit R_PAR  */
#line 157 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[-1].as_ast);
    }
#line 1955 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 27: /* v_path_pattern: condition_list  */
#line 160 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1961 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 28: /* v_path_pattern: condition_list_dot edge_expr  */
#line 161 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_pair((yyvsp[-1].as_ast), (yyvsp[0].as_ast));
    }
#line 1967 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 29: /* v_path_pattern: edge_expr  */
#line 162 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1973 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 30: /* v_path_pattern_dot: condition_list_dot  */
#line 165 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1979 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 31: /* v_path_pattern_dot: condition_list_dot edge_expr_dot  */
#line 166 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_pair((yyvsp[-1].as_ast), (yyvsp[0].as_ast));
    }
#line 1985 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 32: /* v_path_pattern_dot: edge_expr_dot  */
#line 167 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1991 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 33: /* condition_list: condition  */
#line 170 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 1997 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 34: /* condition_list: condition DOT condition_list  */
#line 171 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_pair((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 2003 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 35: /* condition_list_dot: condition DOT condition_list_dot  */
#line 174 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_pair((yyvsp[-2].as_ast), (yyvsp[0].as_ast));
    }
#line 2009 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 36: /* condition_list_dot: condition DOT  */
#line 175 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_pair((yyvsp[-1].as_ast), (void*)0);
    }
#line 2015 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 37: /* condition: filter_expr  */
#line 178 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 2021 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 38: /* condition: has_expr  */
#line 179 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 2027 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 39: /* edge_expr: edge_cond DOT has_label  */
#line 182 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) =
          ast_create_condition_pair((yyvsp[-2].as_ast), ast_create_specific_v((yyvsp[0].as_ast), (void*)0));
    }
#line 2033 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 40: /* edge_expr: edge_cond DOT has_label DOT v_path_pattern  */
#line 183 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) =
          ast_create_condition_pair((yyvsp[-4].as_ast), ast_create_specific_v((yyvsp[-2].as_ast), (yyvsp[0].as_ast)));
    }
#line 2039 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 41: /* edge_expr_dot: edge_cond DOT has_label DOT  */
#line 186 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) =
          ast_create_condition_pair((yyvsp[-3].as_ast), ast_create_specific_v((yyvsp[-1].as_ast), (void*)0));
    }
#line 2045 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 42: /* edge_expr_dot: edge_cond DOT has_label DOT v_path_pattern_dot  */
#line 187 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) =
          ast_create_condition_pair((yyvsp[-4].as_ast), ast_create_specific_v((yyvsp[-2].as_ast), (yyvsp[0].as_ast)));
    }
#line 2051 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 43: /* edge_cond: OUT L_PAR string_lit R_PAR  */
#line 190 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_out((yyvsp[-1].as_ast));
    }
#line 2057 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 44: /* edge_cond: IN L_PAR string_lit R_PAR  */
#line 191 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_in((yyvsp[-1].as_ast));
    }
#line 2063 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 45: /* has_expr: HAS L_PAR property_id COMMA value_cond R_PAR  */
#line 194 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_has((yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 2069 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 46: /* number_lit: INTEGER_LIT  */
#line 197 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_int_literal((yyvsp[0].as_int));
    }
#line 2075 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 47: /* number_lit: DOUBLE_LIT  */
#line 198 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_double_literal((yyvsp[0].as_double));
    }
#line 2081 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 48: /* value_cond: number_lit  */
#line 201 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_EQ, (yyvsp[0].as_ast));
    }
#line 2087 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 49: /* value_cond: string_lit  */
#line 202 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_EQ, (yyvsp[0].as_ast));
    }
#line 2093 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 50: /* value_cond: NEQ L_PAR number_lit R_PAR  */
#line 203 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_NEQ, (yyvsp[-1].as_ast));
    }
#line 2099 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 51: /* value_cond: GT L_PAR number_lit R_PAR  */
#line 204 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_GT, (yyvsp[-1].as_ast));
    }
#line 2105 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 52: /* value_cond: LT L_PAR number_lit R_PAR  */
#line 205 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_LT, (yyvsp[-1].as_ast));
    }
#line 2111 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 53: /* value_cond: GTE L_PAR number_lit R_PAR  */
#line 206 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_GTE, (yyvsp[-1].as_ast));
    }
#line 2117 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 54: /* value_cond: LTE L_PAR number_lit R_PAR  */
#line 207 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_LTE, (yyvsp[-1].as_ast));
    }
#line 2123 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 55: /* value_cond: CONTAINING L_PAR string_lit R_PAR  */
#line 208 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_value_cond(AST_NODE_VALUE_COND_CONTAINS, (yyvsp[-1].as_ast));
    }
#line 2129 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 56: /* property_id: INTEGER_LIT  */
#line 211 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_property_id(ast_create_int_literal((yyvsp[0].as_int)));
    }
#line 2135 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 57: /* filter_expr: FILTER L_PAR filter_argument R_PAR  */
#line 214 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_filter((yyvsp[-1].as_ast));
    }
#line 2141 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 58: /* filter_argument: OR L_PAR filter_argument COMMA filter_argument R_PAR  */
#line 217 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_condition_or((yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 2147 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 59: /* filter_argument: v_path_pattern  */
#line 218 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 2153 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 60: /* schema_op: s_vertex_op  */
#line 221 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 2159 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 61: /* schema_op: s_edge_op  */
#line 222 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 2165 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 62: /* v_label: VERTEX_LABEL L_PAR string_lit R_PAR  */
#line 224 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[-1].as_ast);
    }
#line 2171 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 63: /* string_lit: STRING_LIT  */
#line 226 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_string_literal((yyvsp[0].as_string));
    }
#line 2177 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 64: /* s_vertex_op: v_label DOT DROP_F  */
#line 229 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_schema_drop_v((yyvsp[-2].as_ast));
    }
#line 2183 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 65: /* s_vertex_op: v_label DOT prop_types_dot CREATE_F  */
#line 230 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_schema_add_v((yyvsp[-3].as_ast), (yyvsp[-1].as_ast));
    }
#line 2189 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 66: /* prop_types_dot: %empty  */
#line 233 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (void*)0;
    }
#line 2195 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 67: /* prop_types_dot: PROPERTIES_F DOT prop_types_list  */
#line 234 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[0].as_ast);
    }
#line 2201 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 68: /* prop_types_list: prop_type_dot prop_types_list  */
#line 237 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_pair((yyvsp[-1].as_ast), (yyvsp[0].as_ast));
    }
#line 2207 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 69: /* prop_types_list: prop_type_dot  */
#line 238 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_pair((yyvsp[0].as_ast), (void*)0);
    }
#line 2213 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 70: /* prop_type_dot: INT32_F DOT  */
#line 241 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_int32();
    }
#line 2219 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 71: /* prop_type_dot: INT64_F DOT  */
#line 242 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_int64();
    }
#line 2225 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 72: /* prop_type_dot: DOUBLE_F DOT  */
#line 243 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_double();
    }
#line 2231 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 73: /* prop_type_dot: BOOL_F DOT  */
#line 244 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_bool();
    }
#line 2237 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 74: /* prop_type_dot: STRING_F DOT  */
#line 245 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_prop_types_string();
    }
#line 2243 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 75: /* e_label: EDGE_LABEL L_PAR string_lit R_PAR  */
#line 247 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = (yyvsp[-1].as_ast);
    }
#line 2249 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 76: /* s_edge_op: e_label DOT CREATE_F  */
#line 249 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_schema_add_e((yyvsp[-2].as_ast));
    }
#line 2255 "client/gremlin_parser/src/parser/parser.c"
    break;

    case 77: /* s_edge_op: e_label DOT DROP_F  */
#line 250 "client/gremlin_parser/parser/gremlin.y"
    {
      (yyval.as_ast) = ast_create_schema_drop_e((yyvsp[-2].as_ast));
    }
#line 2261 "client/gremlin_parser/src/parser/parser.c"
    break;

#line 2265 "client/gremlin_parser/src/parser/parser.c"

    default:
      break;
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT("-> $$ =", YY_CAST(yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK(yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp ? yytable[yyi] : yydefgoto[yylhs]);
  }

  goto yynewstate;

/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE(yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus) {
    ++yynerrs;
    {
      yypcontext_t yyctx = {yyssp, yytoken};
      char const* yymsgp = YY_("syntax error");
      int yysyntax_error_status;
      yysyntax_error_status = yysyntax_error(&yymsg_alloc, &yymsg, &yyctx);
      if (yysyntax_error_status == 0)
        yymsgp = yymsg;
      else if (yysyntax_error_status == -1) {
        if (yymsg != yymsgbuf)
          YYSTACK_FREE(yymsg);
        yymsg = YY_CAST(char*, YYSTACK_ALLOC(YY_CAST(YYSIZE_T, yymsg_alloc)));
        if (yymsg) {
          yysyntax_error_status = yysyntax_error(&yymsg_alloc, &yymsg, &yyctx);
          yymsgp = yymsg;
        } else {
          yymsg = yymsgbuf;
          yymsg_alloc = sizeof yymsgbuf;
          yysyntax_error_status = YYENOMEM;
        }
      }
      yyerror(yymsgp);
      if (yysyntax_error_status == YYENOMEM)
        YYNOMEM;
    }
  }

  if (yyerrstatus == 3) {
    /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

    if (yychar <= YYEOF) {
      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        YYABORT;
    } else {
      yydestruct("Error: discarding", yytoken, &yylval);
      yychar = YYEMPTY;
    }
  }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;

/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;

/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3; /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;) {
    yyn = yypact[yystate];
    if (!yypact_value_is_default(yyn)) {
      yyn += YYSYMBOL_YYerror;
      if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror) {
        yyn = yytable[yyn];
        if (0 < yyn)
          break;
      }
    }

    /* Pop the current state because it cannot handle the error token.  */
    if (yyssp == yyss)
      YYABORT;

    yydestruct("Error: popping", YY_ACCESSING_SYMBOL(yystate), yyvsp);
    YYPOPSTACK(1);
    yystate = *yyssp;
    YY_STACK_PRINT(yyss, yyssp);
  }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Shift the error token.  */
  YY_SYMBOL_PRINT("Shifting", YY_ACCESSING_SYMBOL(yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;

/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;

/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror(YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY) {
    /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
    yytoken = YYTRANSLATE(yychar);
    yydestruct("Cleanup: discarding lookahead", yytoken, &yylval);
  }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK(yylen);
  YY_STACK_PRINT(yyss, yyssp);
  while (yyssp != yyss) {
    yydestruct("Cleanup: popping", YY_ACCESSING_SYMBOL(+*yyssp), yyvsp);
    YYPOPSTACK(1);
  }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE(yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE(yymsg);
  return yyresult;
}

#line 252 "client/gremlin_parser/parser/gremlin.y"

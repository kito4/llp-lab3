SET(GREMLIN_PARSER_DIR ${llp-lab3_SOURCE_DIR}/client/gremlin_parser)

find_package(BISON)
find_package(FLEX)
if (${BISON_FOUND})
  message("Bison found")
  if (${FLEX_FOUND})
    message("Flex found")
    BISON_TARGET(parser ${GREMLIN_PARSER_DIR}/parser/gremlin.y ${GREMLIN_PARSER_DIR}/src/parser/parser.c
                 COMPILE_FLAGS -Wcex
                 DEFINES_FILE ${GREMLIN_PARSER_DIR}/include/gremlin_parser/parser/parser.h
                 VERBOSE 
                 REPORT_FILE ${GREMLIN_PARSER_DIR}/docs/bison.txt)
    FLEX_TARGET(lexer ${GREMLIN_PARSER_DIR}/lexer/gremlin.l ${GREMLIN_PARSER_DIR}/src/lexer/lexer.c
                DEFINES_FILE ${GREMLIN_PARSER_DIR}/include/gremlin_parser/lexer/lexer.h)
    ADD_FLEX_BISON_DEPENDENCY(lexer parser)
  else()
    message("Flex not found!")
  endif()
else ()
  message("Bison not found!")
endif()

set(GREMLIN_PARSER_SOURCES
  ${GREMLIN_PARSER_DIR}/src/api/ast_api.c
  ${GREMLIN_PARSER_DIR}/src/ast/ast.c
  ${GREMLIN_PARSER_DIR}/src/parser/parser_res.c
  ${GREMLIN_PARSER_DIR}/src/parser/parser.c
  ${GREMLIN_PARSER_DIR}/src/lexer/lexer.c
  PARENT_SCOPE
)

set(GREMLIN_PARSER_INCLUDES 
  ${GREMLIN_PARSER_DIR}/include/
  ${GREMLIN_PARSER_DIR}/include/gremlin_parser/api/
  ${GREMLIN_PARSER_DIR}/include/gremlin_parser/ast/
  ${GREMLIN_PARSER_DIR}/include/gremlin_parser/parser/
  ${GREMLIN_PARSER_DIR}/include/gremlin_parser/lexer/
  PARENT_SCOPE
)
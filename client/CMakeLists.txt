set(CLIENT_DIR ${llp-lab3_SOURCE_DIR}/client)

add_subdirectory(gremlin_parser)

set(SOURCES
  ${SHARE_SOURCES}
  ${GREMLIN_PARSER_SOURCES}
  ${CLIENT_DIR}/src/client.cpp
  ${CLIENT_DIR}/src/gremlin_ast_to_json.cpp
  ${CLIENT_DIR}/src/json_to_response.cpp
  ${CLIENT_DIR}/src/response.cpp
  ${CLIENT_DIR}/src/main.cpp
)

set(INCLUDES 
  ${SHARE_INCLUDES}
  ${GREMLIN_PARSER_INCLUDES}
  ${CLIENT_DIR}/include
)

add_library(clientlib ${SOURCES})
target_include_directories(clientlib PRIVATE ${INCLUDES})

add_executable(client ${CLIENT_DIR}/src/main.cpp)
target_link_libraries(client PRIVATE clientlib)
target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE valijson)
target_include_directories(client PRIVATE ${INCLUDES})
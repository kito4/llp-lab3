set(SERVER_DIR ${llp-lab3_SOURCE_DIR}/server)

add_subdirectory(database)

set(SOURCES
  ${SHARE_SOURCES}
  ${DATABASE_SOURCES}
  ${SERVER_DIR}/src/result_to_json.cpp
  ${SERVER_DIR}/src/json_to_database_query.cpp
  ${SERVER_DIR}/src/server.cpp
  ${SERVER_DIR}/src/storage_adapter.cpp
)

set(INCLUDES 
  ${SHARE_INCLUDES}
  ${DATABASE_INCLUDES}
  ${SERVER_DIR}/include
)

add_library(serverlib ${SOURCES})
target_include_directories(serverlib PRIVATE ${INCLUDES})

add_executable(server ${SERVER_DIR}/src/main.cpp)
target_link_libraries(server PRIVATE serverlib)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(server PRIVATE valijson)
target_include_directories(server PRIVATE ${INCLUDES})

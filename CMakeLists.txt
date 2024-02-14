cmake_minimum_required(VERSION 3.11)
project(llp-lab3 LANGUAGES C CXX)
set(CMAKE_CURRENT_BINARY_DIR, ./build)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include(FetchContent)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

add_subdirectory(share)
add_subdirectory(client)
add_subdirectory(server)
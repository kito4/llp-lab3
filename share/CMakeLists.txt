set(SHARE_DIR ${llp-lab3_SOURCE_DIR}/share)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)

FetchContent_Declare(valijson
    GIT_REPOSITORY https://github.com/tristanpenman/valijson
    GIT_TAG v1.0.2
)

FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(valijson)

SET(SHARE_SOURCES
    ${SHARE_DIR}/src/unix_tcp_socket.cpp
    ${SHARE_DIR}/src/validate.cpp
    ${SHARE_DIR}/src/windows_tcp_socket.cpp
    PARENT_SCOPE
) 

SET(SHARE_INCLUDES 
    ${valijson_SOURCE_DIR}/include
    ${json_SOURCE_DIR}/single_include
    ${SHARE_DIR}/include
    PARENT_SCOPE
)
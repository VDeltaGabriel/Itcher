cmake_minimum_required(VERSION 3.29)
project(itcher)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_DEMO, "Build terminal-based demo for itcher" ON)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

message("SRC_FILES ${SRC_FILES}")

file(GLOB LINUX_SRC ${CMAKE_SOURCE_DIR}/src/linux/*.c)

find_package(CURL REQUIRED)
find_package(cJSON REQUIRED)

#add_library(itcher SHARED ${SRC_FILES} ${LINUX_SRC})
add_executable(itcher ${SRC_FILES} ${LINUX_SRC} demo/main.c)
include_directories(${CURL_INCLUDE_DIR} ${CJSON_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(itcher ${CURL_LIBRARIES} ${CJSON_LIBRARIES})

if(UNIX)
    target_compile_definitions(itcher PUBLIC __LINUX__)
elseif (WIN32)
    target_compile_definitions(itcher PUBLIC __WINDOWS__)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(itcher PUBLIC DEBUG_BUILD)
    set(BUILD_TYPE DEBUG)
else ()
    target_compile_definitions(itcher PUBLIC RETAIL_BUILD)
    set(BUILD_TYPE RELEASE)
endif ()

set_target_properties(itcher
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${BUILD_TYPE}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${BUILD_TYPE}"
)

message("==== Build Information ====")
message("Build Type: ${BUILD_TYPE}")
message("===========================")
cmake_minimum_required(VERSION 3.1)
project(PizzaParlor)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_BINARY_DIR "build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ASSETS "${PROJECT_SOURCE_DIR}/assets")
add_definitions(-DASSETS=${ASSETS})

set(LIB "lib")
set(INCLUDES "include")

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

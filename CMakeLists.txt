cmake_minimum_required(VERSION 3.1)
project(RamblerGarage)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BINARY_DIR "build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ASSETS "${PROJECT_SOURCE_DIR}/assets")
add_definitions(-DASSETS=${ASSETS})

set(LIB "lib")
set(INCLUDES "include")
set(CONSOLE_SRC "ramblerConsole")
set(UI_SRC "ramblerUI")

add_subdirectory(${CONSOLE_SRC})
add_subdirectory(${UI_SRC})

aux_source_directory( ${LIB}/Vehicles LIB_LIST )
add_library ( Vehicles STATIC ${LIB_LIST} )
target_include_directories( Vehicles PUBLIC ${LIB}/Vehicles/include)


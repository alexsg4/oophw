cmake_minimum_required(VERSION 3.1)
project(ramblerConsole)
set (CMAKE_CXX_STANDARD 11)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE Vehicles )
target_include_directories(${PROJECT_NAME} PRIVATE ../include)

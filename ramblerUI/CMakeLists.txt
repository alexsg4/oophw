cmake_minimum_required(VERSION 3.1)
project(ramblerUI)
set (CMAKE_CXX_STANDARD 11)

if(WIN32 OR MSVC)
	set (PFLAGS "WIN32")
else()
	set(PFLAGS "")
endif()

find_package(wxWidgets REQUIRED COMPONENTS net core base adv)

if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
endif()

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${PFLAGS} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE Vehicles PRIVATE ${wxWidgets_LIBRARIES}) 
target_include_directories(${PROJECT_NAME} PRIVATE ../include)



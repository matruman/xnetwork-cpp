cmake_minimum_required(VERSION 3.12)

project(xnetwork)

set(EXECUTABLE_NAME server)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g -Og")

find_package(Boost REQUIRED)
include_directories("${Boost_INCLUDE_DIRS}")

add_executable(${EXECUTABLE_NAME}
	src/AbstractRoute.hpp
	src/DefaultRoute.hpp
	src/Listener.cpp
	src/Listener.hpp
	src/RequestHandler.cpp
	src/RequestHandler.hpp
	src/Router.hpp
	src/Session.cpp
	src/Session.hpp
	src/utils.cpp
	src/utils.hpp
	src/main.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(${EXECUTABLE_NAME} pthread)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${EXECUTABLE_NAME} wsock32 ws2_32)
endif()

cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_OUT ${CMAKE_CURRENT_SOURCE_DIR}/build CACHE PATH "Build directory" FORCE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_OUT} CACHE PATH "Executable directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_OUT} CACHE PATH "Library directory" FORCE)

project(BellPi)

# Project options
option(MakeTests "MakeTests" OFF)

# Fix flags
if(APPLE)
	add_definitions(-D__DARWIN_UNIX03 -DMACOSX)
endif()
if(CYGWIN)
	add_definitions(-D__CYGWIN__ -D__INSIDE_CYGWIN__)
endif()
if(WIN32)
	add_definitions(-D_WIN32)
endif()

# Add a list of path definitions
set(SOCKET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Sockets)
set(WIRINGPI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/wiringPi)

if(NOT WIN32 AND NOT CYGWIN)
	add_subdirectory(wiringPi)
endif()

add_subdirectory(Sockets)
add_subdirectory(BellServer)
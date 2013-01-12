cmake_minimum_required(VERSION 2.8.4)

project(BellServer)

# Include socket includes
include_directories(${SOCKET_INCLUDE_DIR})
include_directories(${WIRINGPI_INCLUDE_DIR})
link_directories(${LIBRARY_OUTPUT_PATH})

#Build a list of all sources for the server
set(SERVER_SRCS Main.cpp BellSocket.cpp BellServer.cpp)

# Add target and link sockets with this executable
add_executable(BellServer ${SERVER_SRCS})
target_link_libraries(BellServer sockets)

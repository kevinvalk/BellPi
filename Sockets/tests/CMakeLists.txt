cmake_minimum_required(VERSION 2.8.4)

set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/sockets CACHE PATH "Build directory" FORCE)
include_directories(${SOCKET_INCLUDE_DIR} ${SOCKET_INCLUDE_DIR}/../)
link_directories(${LIBRARY_OUTPUT_PATH})

SET(TESTS
	events
	resolve
	sockets_test
	base64
	semtest
	echoserver
	stressclient
	http
	httpd
	retry
	resume
	http_post
	x
	copy
	crlf
	https
	sloppy_http
	chunked
	threadstress
	listener
	httpd_test
	scanr
	json
	detach
)

FOREACH(test ${TESTS})
	ADD_EXECUTABLE(${test} ${test}.cpp)
	target_link_libraries(${test} sockets)
ENDFOREACH(test)

set(EXECUTABLE_OUTPUT_PATH ${B_EXECUTABLE_OUTPUT_PATH})
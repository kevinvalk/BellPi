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
	stressclient
	http
	retry
	resume
	x
	copy
	crlf
	sloppy_http
	chunked
	echoserver
	listener
	scanr
	http_post
	httpd
	json
	detach
)

# When we have openssl we can include some ssl tests
if(HAVE_OPENSSL)
	list(APPEND TESTS httpd_test https threadstress)
endif()

FOREACH(test ${TESTS})
	ADD_EXECUTABLE(${test} ${test}.cpp)
	target_link_libraries(${test} sockets)
ENDFOREACH(test)

set(EXECUTABLE_OUTPUT_PATH ${B_EXECUTABLE_OUTPUT_PATH})
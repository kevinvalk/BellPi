cmake_minimum_required(VERSION 2.8.4)

project(sockets)
 
# Version info
set(SOCKETS_VERSION_MAJOR 2)
set(SOCKETS_VERSION_MINOR 3.9.7)

# Options for sockets library
option(HAVE_OPENSSL "HAVE_OPENSSL" OFF)
option(NO_GETADDRINFO "NO_GETADDRINFO" ON)
option(ENABLE_RESOLVER "ENABLE_RESOLVER" ON)
option(ENABLE_RECONNECT "ENABLE_RECONNECT" ON)
option(ENABLE_DETACH "ENABLE_DETACH" ON)
option(ENABLE_EXCEPTIONS "ENABLE_EXCEPTIONS" ON)

# Sources for C++ Sockets library
set(SOCKETS_SRCS
	Ajp13Socket.cpp       AjpBaseSocket.cpp    Base64.cpp           Debug.cpp
	Event.cpp             EventHandler.cpp     EventTime.cpp        Exception.cpp
	File.cpp              FileStream.cpp       HTTPSocket.cpp       HttpBaseSocket.cpp
	HttpClientSocket.cpp  HttpDebugSocket.cpp  HttpGetSocket.cpp    HttpPostSocket.cpp
	HttpPutSocket.cpp     HttpRequest.cpp      HttpResponse.cpp     HttpTransaction.cpp
	HttpdCookies.cpp      HttpdForm.cpp        HttpdSocket.cpp      IEventOwner.cpp
	Ipv4Address.cpp       Ipv6Address.cpp      Json.cpp             Lock.cpp
	MemFile.cpp           Mutex.cpp            Parse.cpp            ResolvServer.cpp
	ResolvSocket.cpp      SSLInitializer.cpp   SctpSocket.cpp       SmtpdSocket.cpp
	Socket.cpp            SocketHandler.cpp    SocketHandlerEp.cpp  SocketHandlerThread.cpp
	SocketStream.cpp      SocketThread.cpp     StdoutLog.cpp        StreamSocket.cpp
	StreamWriter.cpp      TcpSocket.cpp        Thread.cpp           UdpSocket.cpp
	Utility.cpp           XmlDocument.cpp      XmlNode.cpp          XmlException.cpp
)

# Extend source not windows builds
if(NOT WIN32)
	list(APPEND SOCKETS_SRCS Semaphore.cpp)
endif()

# Possible undefinided variable fix
set(LIB_EAY_RELEASE 0)
set(SSL_EAY_RELEASE 0)
	
# Add the library
add_library(sockets STATIC ${SOCKETS_SRCS})

# Check for pthread package
find_package(Threads REQUIRED)

# Check if we really can use libssl and if so link it
if(HAVE_OPENSSL)
	find_package(OpenSSL)
	if(NOT OPENSSL_FOUND)
		set(HAVE_OPENSSL 0)
		message("Disabling openssl as we could not find it")
	endif()
endif()

target_link_libraries(sockets ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES})

# Generate the configuration
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sockets-config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/sockets-config.h)

# Make all the tests
if(MakeTests)
	add_subdirectory(tests)
endif()


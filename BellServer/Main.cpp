#include "BellServer.h"
#include "BellSocket.h"
#include <SocketHandler.h>
#include <ListenSocket.h>

#define BELL_PORT 8311
#define BELL_IP "0.0.0.0"

#define KEY_MAX 6
#define KEY_MASTER 0xDEADBEEF
#define KEY_VERSIONS {100, 200, 300, 400, 500, 600}

BellServer* bellServer;

int main()
{
	// The key versions
	uint32 keyVersions[KEY_MAX] = KEY_VERSIONS; 

	// Create the server
	bellServer = new BellServer(KEY_MASTER, keyVersions, KEY_MAX);

	// Create socket and handler
	SocketHandler handler;
	ListenSocket<BellSocket> listener(handler);

	if(listener.Bind(BELL_IP, BELL_PORT))
	{
		printf("Could not bind to %s:%d", BELL_IP, BELL_PORT);
		exit(-1);
	}
	

	// Add the socket to the handler
	handler.Add(&listener);
	
	// The main loop
	handler.Select(1,0);
	while(true)
	{
		handler.Select(1,0);
	}
}


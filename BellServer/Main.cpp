#include "BellServer.h"
#include "BellSocket.h"
#include <SocketHandler.h>

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
	BellSocket *bellSocket = new BellSocket(handler);

	bellSocket->SetDeleteByHandler();
	bellSocket->Open(BELL_IP, BELL_PORT);

	// Add the socket to the handler
	handler.Add(bellSocket);
	
	// The main loop
	handler.Select(1,0);
	while(handler.GetCount())
	{
		handler.Select(1,0);
	}
}


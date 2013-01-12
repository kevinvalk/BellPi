#include "BellServer.h"
#include "BellSocket.h"
#include <SocketHandler.h>
#include <ListenSocket.h>

#ifdef RASPBERRY
#include <wiringPi.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

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
	
	#ifdef RASPBERRY
	// Enable GPIO
	if(wiringPiSetup() < 0)
	{
			printf("Could not initialize wiringPi library");
			exit(-1);
	}
	#endif
	
	#ifdef __CYGWIN__
	uint32 timer = time(NULL);
	bool pinged = false;
	#endif
	// The main loop
	while(true)
	{
		handler.Select(0, 100000); // Sleeps for a 1/10 of a second
		
		// Check for GPIO signals
		for(uint32 i = 0; i < 7; i++)
		{
			bool hadRead = false;
			#ifdef __CYGWIN__
			uint32 s = ((time(NULL)-timer) % 5);
			if(s == 0 && !pinged)
			{
				pinged = true;
			}
			if(pinged) // Fire up every 5 seconds
			#endif
			#ifdef RASPBERRY
			if(digitalRead(i) == HIGH)
			#endif
			{
				printf("HIGH button %i\n", i);
				bellServer->handleButton(i);
				hadRead = true;
				
				#ifdef __CYGWIN__
				pinged = false;
				#endif
			}
			if(hadRead)
			#ifdef RASPBERRY
				delay(500); // Sleeps for 1/2 second
			#else
				sleep(1);
			#endif
		}
		
	}
}


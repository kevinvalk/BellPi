#include "ClientSocket.h"
#include <SocketHandler.h>


int main()
{
	SocketHandler handler;
	ClientSocket *server = new ClientSocket(h);

	server->SetDeleteByHandler();
	server->Open("localhost", 9002);
	handler.Add(p);
	handler.Select(1,0);
	while (.GetCount())
		handler.Select(1,0);
}


#include "ClientSocket.h"
#include <SocketHandler.h>


int main()
{
	SocketHandler h;
	ClientSocket *p = new ClientSocket(h);

	p -> SetDeleteByHandler();
	p -> Open("localhost", 9002);
	h.Add(p);
	h.Select(1,0);
	while (h.GetCount())
	{
		h.Select(1,0);
	}
}


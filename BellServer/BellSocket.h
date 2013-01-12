#ifndef BELL_SOCKET_H
#define BELL_SOCKET_H

#include <TcpSocket.h>
#include <ISocketHandler.h>
#include "Common.h"

class BellSocket : public TcpSocket
{
	public:
		BellSocket(ISocketHandler& );

		void OnRead();
		void quit();
};

#endif

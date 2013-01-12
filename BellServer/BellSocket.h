#ifndef BELL_SOCKET_H
#define BELL_SOCKET_H

#include <TcpSocket.h>
#include <ISocketHandler.h>
#include "Common.h"

class BellServer;

class BellSocket : public TcpSocket
{
	public:
		BellSocket(ISocketHandler& );

		void OnRead();
		void quit();
		
		// Handlers
		bool handleUnregister(Packet *packet);
		bool handleRegister(Packet *packet);
	
	private:
		uint32 key_;
		uint8 index_;
};
#endif

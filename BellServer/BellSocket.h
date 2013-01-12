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
		void OnDisconnect();
		void quit();
		
		// Handlers out
		void handleCall();
		
		// Handlers in
		bool handleUnregister(Packet *packet);
		bool handleRegister(Packet *packet);
	
	private:
		uint32 key_;
		uint8 index_;
		
		Packet *initPacket(PacketCmd cmd, uint32 size);
};
#endif

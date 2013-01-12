#include "BellSocket.h"
#include "BellServer.h"

// the constant TCP_BUFSIZE_READ is the maximum size of the standard input
// buffer of TcpSocket
#define RSIZE TCP_BUFSIZE_READ

BellSocket::BellSocket(ISocketHandler& h) : TcpSocket(h)
{
	key_ = 0;
}

void BellSocket::quit()
{
	SetCloseAndDelete();
}

void BellSocket::OnDisconnect()
{
	if(key_ != 0) // Unregister if this client was registered
		handleUnregister(NULL);
}

void BellSocket::OnRead()
{
	// Move it to ibuf
	TcpSocket::OnRead();
	uint32 length = ibuf.GetLength();
	
	// If we received something lets handle it
	if (length > 0)
	{
		Packet *packet = Packet::createPacket(length);
		ibuf.Read((char*)packet, length);
		
		// Check if this is an valid packet
		printf("Received packet with key %08X and index: %i\n", packet->key, packet->index);
		
		if(key_ == 0 && packet->cmd != REGISTER)
		{
			printf("This client is not yet registered so dropping the connection\n");
			SetCloseAndDelete();
		}
		else
		{
			if(packet->key != key_ && packet->cmd != REGISTER)
			{
				printf("This client has not the same key anymore DROP HIM!\n");
				SetCloseAndDelete();
			}
			else
			{
				bool isSuccess;
				
				// Lets handle this packet
				switch(packet->cmd)
				{
					case REGISTER:
						isSuccess = handleRegister(packet);
					break;
					case UNREGISTER:
						isSuccess = handleUnregister(packet);
					break;
				}
				
				if(!isSuccess)
				{
					printf("Error in handle function so dropping connection\n");
					SetCloseAndDelete();
				}
			}
		}
		Packet::deletePacket(packet);
	}
}

Packet *BellSocket::initPacket(PacketCmd cmd, uint32 size)
{
	Packet *packet = Packet::createPacket(PACKET_HEADER+size);
	packet->key = key_;
	packet->index = index_;
	packet->cmd = cmd;
	packet->length = 0;
	return packet;
}

void BellSocket::handleCall()
{
	// Build the call packet
	Packet *packet = initPacket(CALL, sizeof(time_t));
	packet->setDword(0, (uint32)time(NULL));
	
	printf("Called client: %08X\n", UniqueIdentifier());
	
	// Send it to this client
	SendBuf((char*)packet, packet->totalLength());
}

bool BellSocket::handleUnregister(Packet *packet)
{
	printf("Unregistering this client\n");
	if(!bellServer->unregisterClient(key_, UniqueIdentifier()))
	{
		printf("THIS CAN NEVER HAPPEN!!!\n");
		return false;
	}
	
	printf("Successfully unregistered this client\n");
	return true;
}

bool BellSocket::handleRegister(Packet *packet)
{
	printf("Registering this client\n");
	uint8 clientIndex = bellServer->keyToIndex(packet->key, packet->index);
	if(clientIndex != packet->index)
	{
		printf("Wrong key so dropping this client\n");
		return false;
	}
	
	if(bellServer->registerClient(packet->key, UniqueIdentifier(), this))
	{
		printf("Successfully registered this client\n");	
		key_ = packet->key;
		index_ = packet->index;
		return true;
	}
	
	return false;
}

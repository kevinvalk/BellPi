#include "BellClient.h"

Packet *BellClient::initPacket(PacketCmd cmd, uint32 size)
{
	Packet *packet = Packet::createPacket(PACKET_HEADER+size);
	packet->key = key_;
	packet->index = index_;
	packet->cmd = cmd;
	packet->length = 0;
	return packet;
}

void BellClient::handleRegister()
{
	Packet *packet = initPacket(REGISTER, 0);
	socket->write((char*)packet, packet->totalLength());
}
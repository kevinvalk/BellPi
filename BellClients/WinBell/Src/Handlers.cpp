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

void BellClient::handleCall(Packet *packet)
{
	if(!(sound->state() == Phonon::StoppedState || sound->state() == Phonon::PausedState || sound->state() == Phonon::ErrorState))
		if(sound->currentTime() < 1500)
			return;

	// Parse bell time
	QDateTime timestamp;
	timestamp.setTime_t(packet->getDword(0));
	

	// Show tooltip
	tray->showMessage(tr("Dingdong om ")+timestamp.toString(Qt::SystemLocaleShortDate)+"!", tr("Er staat iemand aan de deur!"), QSystemTrayIcon::NoIcon, 3000);

	// Start sound
	sound->stop();
	sound->seek(0);
	sound->play();
}
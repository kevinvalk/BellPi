#include "BellClient.h"
#include <Windows.h>

BellClient::BellClient(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	recvPacket = Packet::createPacket(200);

	// Create the system context menu
	menu = new QMenu(this);
	menu->addAction(tr("Show"), this, SLOT(show()));
	menu->addAction(tr("Close"), application, SLOT(quit()));

	// Create system tray
	tray = new QSystemTrayIcon(this);
	tray->setIcon(QIcon(":/img/icon.png"));
	tray->setContextMenu(menu);
	tray->show();
	
	// Create timed loop
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(10);

	// Define
	key_ = 0xDEADBE8B;
	index_ = 0;

	// Define sound system
	sound = new Phonon::MediaObject(this);
	sound->setCurrentSource(Phonon::MediaSource(":/sound/default.mp3"));
	Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::Path path = Phonon::createPath(sound, audioOutput);

	// Create the socket
	socket = new QTcpSocket(parent);
	socket->connectToHost("192.168.1.3", 8311);

	// Register us
	handleRegister();
}

BellClient::~BellClient()
{
	tray->hide();
	Packet::deletePacket(recvPacket);
}

bool BellClient::event(QEvent *event)
{
	
	switch(event->type())
	{
		case QEvent::WindowStateChange:
			if(isMinimized())
				QTimer::singleShot(0, this, SLOT(hide()));
		break;
		case QEvent::Show:
			if(isMinimized())
			{
				showNormal();
				event->ignore();
				return false;
			}
		break;
		case QEvent::Close:
			hide();
			event->ignore();
			return false;
		break;
	}
	return QMainWindow::event(event);
}

void BellClient::update()
{
	// Check for packets
	int size = socket->read((char*)recvPacket, 200);

	if(size > 0)
	{
		// Handle packet
		int i = 0;

		// Check if this packet is mine
		if(recvPacket->key == key_)
		{
			switch(recvPacket->cmd)
			{
				case CALL:
					sound->stop();
					sound->seek(0);
					sound->play();
				break;
			}
		}
	}

}
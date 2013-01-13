#include "BellClient.h"
#include <Windows.h>

BellClient::BellClient(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{

	tray = nullptr;

	// Read settings
	QSettings settings("config.ini", QSettings::IniFormat);
	host_ = settings.value("Connection/host").toString();
	port_ = settings.value("Connection/port").toInt();
	key_ = settings.value("Connection/clientKey").toInt();
	index_ = settings.value("Connection/bellNo", 255).toInt();
	soundPath_ = settings.value("Sound/path", ":/sound/default.mp3").toString();

	// Close if not all settings are given
	if(host_ == "" || port_ == 0 || key_ == 0 || index_ == 255)
	{
		//application->deleteLater();
		QMetaObject::invokeMethod(application, "quit", Qt::QueuedConnection);
		return;
	}


	ui.setupUi(this);

	recvPacket = Packet::createPacket(200);

	// Create the system context menu
	menu = new QMenu(this);
	//menu->addAction(tr("Show"), this, SLOT(show())); Disabled for now perhaps for latter stage
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

	// Define sound system
	sound = new Phonon::MediaObject(this);
	sound->setCurrentSource(Phonon::MediaSource(soundPath_));
	Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::Path path = Phonon::createPath(sound, audioOutput);
	audioOutput->setVolumeDecibel(0); // play as is

	// Create the socket
	socket = new QTcpSocket(parent);
	socket->connectToHost(host_, port_);

	// Register us
	handleRegister();
}

BellClient::~BellClient()
{
	QSettings settings("config.ini", QSettings::IniFormat);
	settings.setValue("Connection/host", host_);
	settings.setValue("Connection/port", port_);
	settings.setValue("Connection/clientKey", key_);
	settings.setValue("Connection/bellNo", index_);
	settings.setValue("Sound/path", soundPath_);
	
	if(tray != nullptr)
	{
		tray->hide();
		Packet::deletePacket(recvPacket);
	}
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
		// Check if this packet is mine
		if(recvPacket->key == key_)
		{
			switch(recvPacket->cmd)
			{
				case CALL: handleCall(recvPacket); break;
			}
		}
	}
}
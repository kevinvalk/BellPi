#include "BellClient.h"
#include <Windows.h>

BellClient::BellClient(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

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
	timer->start(50);

	// Create the socket
	socket = new QTcpSocket(parent);
	socket->connectToHost("localhost", 8311);
}

BellClient::~BellClient()
{
	tray->hide();
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

}
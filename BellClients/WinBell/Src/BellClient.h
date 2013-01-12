#ifndef BELLCLIENT_H
#define BELLCLIENT_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QString>
#include <QVector>
#include <QMenu>
#include <QFile>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QDataStream>
#include <QListWidget>
#include <QList>
#include <QTcpSocket>
#include <Phonon/phonon>
#include "ui_Main.h"
#include "..\..\..\BellServer\Common.h"

class BellClient : public QMainWindow
{
	Q_OBJECT

public:
	BellClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~BellClient();

	// Handlers out
	Packet *initPacket(PacketCmd cmd, uint32 size);
	void handleRegister();
	

public slots:
	void update();

private:
	Ui::BellClientClass ui;
	QMenu *menu;
	QSystemTrayIcon *tray;
	QTimer *timer;
	QTcpSocket *socket;

	Packet *recvPacket;

	// Sound output
	Phonon::MediaObject *sound;

	// Client info
	uint32 key_;
	uint8 index_;

protected:
	bool event(QEvent *event);
};

extern QApplication *application;
#endif // BELLCLIENT_H

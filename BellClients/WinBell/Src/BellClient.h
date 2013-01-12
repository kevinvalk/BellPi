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
#include "ui_Main.h"
#include "typedef.h"

class BellClient : public QMainWindow
{
	Q_OBJECT

public:
	BellClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~BellClient();

public slots:
	void update();

private:
	Ui::BellClientClass ui;
	QMenu *menu;
	QSystemTrayIcon *tray;
	QTimer *timer;
	QTcpSocket *socket;

protected:
	bool event(QEvent *event);
};

extern QApplication *application;
#endif // BELLCLIENT_H

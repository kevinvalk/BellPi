#include "BellClient.h"
#include <QtGui/QApplication>

QApplication *application;
int main(int argc, char *argv[])
{
	application = new QApplication(argc, argv);
	BellClient w;
	int ret = application->exec();
	delete application;
	return ret;
}

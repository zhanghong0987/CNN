#include "Cnn.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Cnn w;
	w.show();
	return a.exec();
}

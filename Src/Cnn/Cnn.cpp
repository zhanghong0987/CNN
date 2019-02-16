#include "Cnn.h"
#include "MNISTDlg.h"

Cnn::Cnn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Cnn::on_actionViewMNIST_triggered()
{
	QMNISTDlg dlg(this);
	if (dlg.exec() == QDialog::Rejected)
		return;

}

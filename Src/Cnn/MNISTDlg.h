#pragma once

#include <QDialog>
#include "ui_MNISTDlg.h"
#include "ReadMNIST.h"
#include <QLabel>

class QMNISTDlg : public QDialog
{
	Q_OBJECT

public:
	QMNISTDlg(QWidget *parent = Q_NULLPTR);
	~QMNISTDlg();

	mnist_data *m_pData;
	unsigned int m_count;

private:
	Ui::QMNISTDlg ui;

	int m_nImage;
	QLabel **m_arrWidgetImage;
	QLabel **m_arrWidgetLabel;
	QString m_sIniFile;

private slots:
	void on_btnOpen_clicked();
	void on_scrollBar_actionTriggered(int action);
	void on_scrollBar_sliderMoved(int k);
	void Repaint(int k);

};


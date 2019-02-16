#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Cnn.h"

class Cnn : public QMainWindow
{
	Q_OBJECT

public:
	Cnn(QWidget *parent = Q_NULLPTR);

private:
	Ui::CnnClass ui;

private slots:
	void on_actionViewMNIST_triggered();
};

#pragma once

#include <QtWidgets/QMainWindow>
#include<QSharedPointer>
#include "ui_TestUI.h"
#include "RSFSW26Driver.h"

class TestUI : public QMainWindow
{
	Q_OBJECT

public:
	TestUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::TestUIClass ui;
	QSharedPointer<RSFSW26Driver> dev_;

private slots:
	void on_btnConnect_clicked();
	void on_btnSendOrder_clicked();
};

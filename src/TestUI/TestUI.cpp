#include "TestUI.h"
#include<string>
using std::string;

TestUI::TestUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void TestUI::on_btnConnect_clicked()
{
	string devName{ ui.editSrcName->text().toStdString() };
	dev_ = QSharedPointer<RSFSW26Driver>(new RSFSW26Driver{ devName });
}

void TestUI::on_btnSendOrder_clicked()
{
	string orderS{ ui.textOrder->document()->toPlainText().toStdString() };
	dev_->setOrder(orderS);

	auto buf{ dev_->readString() };
	ui.textOrderShow->setPlainText(QString::fromStdString(buf));
}

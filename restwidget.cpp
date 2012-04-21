#include "restwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextDocument>
#include <QtNetwork/QNetworkAccessManager>

RestWidget::RestWidget(QWidget *parent) :
    QWidget(parent)
{
    server_url = "http://whatever";
    user = "team1";
    status = "idle";

    serverLabel = new QLabel;
    userLabel = new QLabel;
    statusLabel = new QLabel;

    serverLabel->setText("ServerURL: " + server_url);
    userLabel->setText("Current User: " + user);
    statusLabel->setText("Status: " + status);
    //DEFINE THE OUTPUT AREA:
    xmloutput = new QListWidget();
    xmloutput->addItem("ready");
    xmloutput->addItem("for");
    xmloutput->addItem("Action...");

    //SET UP THE NETWORK CONNECTION:
    netManager = new QNetworkAccessManager(this);



    //SET THE LAYOUT:
    QGridLayout *layout = new QGridLayout();

    layout->addWidget(serverLabel,0,0);
    layout->addWidget(userLabel,0,1);
    layout->addWidget(statusLabel,0,2);
    layout->addWidget(xmloutput,1,0,1,3);

    setLayout(layout);

    xmloutput->addItem("hullo");



}
//SIGNAL FUNCTIONS:


//SLOT FUNCTIONS:
void RestWidget::getNewOrder(){
    //connect to server and get the order:
    //TODO
    //load the recieved data into the xmlDOM:
    //TODO
    //make order vector and emit signal with order vector:

    xmloutput->addItem("hullo");
    //emit sendOrder(currentOrder);
}

void RestWidget::deleteOrder(int value){

}





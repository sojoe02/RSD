#include "restwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextDocument>
#include <QtNetwork/QNetworkAccessManager>
#include <QDateTime>

RestWidget::RestWidget(QWidget *parent) :
    QWidget(parent)
{
    server_url = "http://localhost:8080/restservlet/sample/...";
    user = "team1";
    status = "idle";

    serverLabel = new QLabel;
    userLabel = new QLabel;
    statusLabel = new QLabel;
    currentOrder = new std::vector<int>;



    serverLabel->setText("ServerURL: " + server_url);
    userLabel->setText("Current User: " + user);
    statusLabel->setText("Status: " + status);

    currentOrder = new std::vector<int>;

    //test area:
    QPushButton *TestButton = new QPushButton(QApplication::translate("PackML","Test Connection"));
    QObject::connect(TestButton, SIGNAL(pressed()),this,SLOT(getNewOrder()));

    //DEFINE THE OUTPUT AREA:
    xmloutput = new QListWidget();
    xmloutput->addItem("ready");
    xmloutput->addItem("for");
    xmloutput->addItem("Action...");

    //SET UP THE NETWORK CONNECTION:
    netManager = new QNetworkAccessManager(this);

    QObject::connect(netManager, SIGNAL(finished(QNetworkReply *)),
                                SLOT(requestFinished(QNetworkReply *)));



    //SET THE LAYOUT:
    QGridLayout *layout = new QGridLayout();

    layout->addWidget(serverLabel,0,0);
    layout->addWidget(userLabel,0,1);
    layout->addWidget(statusLabel,0,2);
    layout->addWidget(TestButton,2,0);
    layout->addWidget(xmloutput,1,0,1,3);

    setLayout(layout);
}
//SIGNAL FUNCTIONS:


//SLOT FUNCTIONS:
void RestWidget::getNewOrder(){
    //connect to server and get the order:
    xmloutput->addItem(QTime::currentTime().toString() +" : Requesting new order from server");

    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " +
                         QByteArray(QString("%1:%2").arg(user).arg(password).toAscii().toBase64())
                     );
    request.setRawHeader("Accept", "application/xml");
    request.setRawHeader("Content-Type", "application/xml");

    request.setUrl(QUrl(server_url));

    QNetworkReply *reply = netManager->get(request);


    //load the recieved data into the xmlDOM:
    //TODO
    //make order vector and emit signal with order vector:

    //xmloutput->addItem("hullo");
    //emit sendOrder(currentOrder);
}

void RestWidget::requestFinished(QNetworkReply *reply){

    if(reply->error()>0){
        xmloutput->addItem(QTime::currentTime().toString() +" : " + reply->errorString());

    } else{
        QByteArray data = reply->readAll();
        QDomDocument doc;
        doc.setContent(data);
        QDomNodeList nodes = doc.elementsByTagName("message");

        if(nodes.size()>0){
            xmloutput->addItem(nodes.at(0).toElement().text());
        }
    }
}

void RestWidget::deleteOrder(int value){

}





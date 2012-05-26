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
    //server_url = "http://httpbin.org/get";
    server_url = "http://192.168.0.100/orders/";
    user = "team1";
    status = "idle";
    password = "nothing";

    serverLabel = new QLabel;
    userLabel = new QLabel;
    statusLabel = new QLabel;

    orderIDs = new QVector<QString>(100);
    currentOrder = new QVector<int>(10);

    //currentOrder = new std::vector<int>;

    serverLabel->setText("ServerURL: " + server_url);
    userLabel->setText("Current User: " + user);
    statusLabel->setText("Status: " + status);

    //currentOrder = new std::vector<int>;

    //test area:
    QPushButton *TestButton = new QPushButton(QApplication::translate("PackML","Get Orders"));
    QPushButton *handleOrderTest = new QPushButton(QApplication::translate("PackML","Handle Order"));

    QObject::connect(TestButton, SIGNAL(pressed()),this,SLOT(getOrderUrls()));
    QObject::connect(handleOrderTest,SIGNAL(pressed()),this,SLOT(getNewOrder()));



    //DEFINE THE OUTPUT AREA:
    xmloutput = new QListWidget();
    xmloutput->addItem("ready");
    xmloutput->addItem("for");
    xmloutput->addItem("Action...");

    dataOutput = new QTextEdit;

    dataOutput->setText("Nothing to see here!");

    //SET UP THE NETWORK CONNECTION:
    netManager2 = new QNetworkAccessManager(this);

    //QObject::connect(netManager, SIGNAL(finished(QNetworkReply *)),this,




    //QObject::connect(netManager2, SIGNAL(finished(QNetworkReply *)),this,
    //                            SLOT(testRequest(QNetworkReply *)));

    //SET THE LAYOUT:
    QGridLayout *layout = new QGridLayout();

    layout->addWidget(serverLabel,0,0);
    layout->addWidget(userLabel,0,1);
    layout->addWidget(statusLabel,0,2);
    layout->addWidget(TestButton,2,0);
    layout->addWidget(xmloutput,1,0,1,3);
    layout->addWidget(dataOutput,3,0,3,3);
    layout->addWidget(handleOrderTest,2,1);

    setLayout(layout);
}
//SIGNAL FUNCTIONS:

//start by retrieving the order list:
void RestWidget::getOrderUrls(){

    QObject::connect(netManager2, SIGNAL(finished(QNetworkReply *)),this,
                     SLOT(parseOrderUrls(QNetworkReply *)));

    orderIDs->clear();

    //First define the request:
    QNetworkRequest request;
    request.setRawHeader("Authorization", "Basic " +
                         QByteArray(QString("%1:%2").arg(user).arg(password).toAscii().toBase64())
                         );
    request.setRawHeader("Accept", "application/xml");
    request.setRawHeader("Content-Type", "application/xml");

    request.setUrl(QUrl(server_url));

    //Wait for a reply:
    QNetworkReply *reply = netManager2->get(request);

}

void RestWidget::parseOrderUrls(QNetworkReply *reply){

    if(reply->error()>0){
        xmloutput->addItem(QTime::currentTime().toString() +" : " + reply->errorString());
        emit connectionError();

    } else{
        QByteArray data = reply->readAll();
        QDomDocument doc;

        dataOutput->setText(data);

        doc.setContent(data);

        QDomNodeList orderNodes = doc.elementsByTagName("order");

        for(int i = 0; i < orderNodes.size(); i++){
            xmloutput->addItem(orderNodes.at(i).toElement().text());
            orderIDs->append(orderNodes.at(i).toElement().text());
        }
        order_ptr = 0; //reset the order pointer.
    }
    QObject::disconnect(netManager2, SIGNAL(finished(QNetworkReply*)),this, SLOT(parseOrderUrls(QNetworkReply*)));
}

//orderhandling stuff

void RestWidget::getNewOrder(){
    xmloutput->addItem("getting new order:");

    //First define the request:
    QNetworkRequest request;

    if(!orderIDs->empty()){
        request.setUrl(QUrl(orderIDs->at(order_ptr)));

        QObject::connect(netManager2, SIGNAL(finished(QNetworkReply *)),this,
                         SLOT(parseOrderInfo(QNetworkReply *)));

        order_ptr++;

        if(order_ptr >= orderIDs->size()){
            order_ptr = 0; //if the order ptr moves out of bounds start over.
        }
        //Wait for a reply:
        QNetworkReply *reply = netManager2->get(request);
    } else{
        emit noOrderError();
        xmloutput->addItem("No order urls present");
    }

}

void RestWidget::parseOrderInfo(QNetworkReply *reply){

    QObject::disconnect(netManager2, SIGNAL(finished(QNetworkReply*)),this, SLOT(parseOrderInfo(QNetworkReply*)));

    xmloutput->addItem("Parsing order info");

    if(reply->error()>0){
        xmloutput->addItem(QTime::currentTime().toString() +" : " + reply->errorString());
        emit connectionError();

    } else{
        QByteArray data = reply->readAll();
        QDomDocument doc;

        dataOutput->setText(data);
        xmloutput->addItem(data);
        doc.setContent(data);

        QString ready = doc.elementsByTagName("status").item(0).toElement().text();


        if(QString::compare(ready,"ready",Qt::CaseInsensitive)  == 0){
            if(getThisOrder(reply->url())){

                QString reds = doc.elementsByTagName("red").item(0).toElement().text();
                currentOrder->append(reds.toInt());

                QString blues = doc.elementsByTagName("blue").item(0).toElement().text();
                currentOrder->append(blues.toInt());

                QString yellows = doc.elementsByTagName("yellow").item(0).toElement().text();
                currentOrder->append(yellows.toInt());

            }
            else{
                emit noTicketError();
            }
        }

    }


}

//test if the order is availible (yeah its synchronous!):

bool RestWidget::getThisOrder(QUrl url){

    QByteArray putData;
    putData.append("taking&");
    putData.append("ticket");

    QNetworkRequest request;

    request.setUrl(url);

    QNetworkReply *reply = netManager2->put( request,putData );

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));

    // Execute the event loop here, now we will wait here until readyRead() signal is emitted
    // which in turn will trigger event loop quit.
    loop.exec();

    currentTicket = "none";

    if(reply->error()>0){
        xmloutput->addItem(QTime::currentTime().toString() +" : " + reply->errorString());
        emit connectionError();

    } else{
        QByteArray data = reply->readAll();
        QDomDocument doc;

        dataOutput->setText(data);
        doc.setContent(data);
        xmloutput->addItem(data);

        currentTicket = doc.elementsByTagName("ticket").item(0).toElement().text();

        if(QString::compare("none",currentTicket) == 0){
            return false;
        }

    }
}









#include "restwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QTextDocument>
#include <QtNetwork/QNetworkAccessManager>
#include <QDateTime>
#include <QDebug>

RestWidget::RestWidget(QWidget *parent) :
    QWidget(parent)
{
    //server_url = "http://httpbin.org/get";
    server_url = "http://192.168.0.100";
    user = "team1";
    status = "idle";
    password = "nothing";

    currentTicket = "none";

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
    QPushButton *testLog = new QPushButton(QApplication::translate("PackMl", "Log"));

    QObject::connect(TestButton, SIGNAL(pressed()),this,SLOT(getOrderUrls()));
    QObject::connect(handleOrderTest,SIGNAL(pressed()),this,SLOT(getNewOrder()));
    QObject::connect(testLog,SIGNAL(pressed()),this,SLOT(testLog()));

    //DEFINE THE OUTPUT AREA:
    xmloutput = new QListWidget();
    xmloutput->addItem("ready");
    xmloutput->addItem("for");
    xmloutput->addItem("Action...");

    dataOutput = new QTextEdit;

    dataOutput->setText("Nothing to see here!");

    //SET UP THE NETWORK CONNECTION:
    netManager2 = new QNetworkAccessManager(this);

    //SET THE LAYOUT:
    QGridLayout *layout = new QGridLayout();

    layout->addWidget(serverLabel,0,0);
    layout->addWidget(userLabel,0,1);
    layout->addWidget(statusLabel,0,2);
    layout->addWidget(TestButton,2,0);
    layout->addWidget(xmloutput,1,0,1,3);
    layout->addWidget(dataOutput,3,0,3,3);
    layout->addWidget(handleOrderTest,2,1);
    layout->addWidget(testLog,2,2);

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

    request.setUrl(QUrl(server_url+"/orders/"));

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

        order_url = orderIDs->at(order_ptr);

        request.setUrl(QUrl(order_url));

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
            emit noTicketError();
            return false;
        }

    }
}

void RestWidget::orderDone(){


    if(QString::compare("none",currentTicket)== 0){
        emit noTicketToDeleteError();
        qDebug() << "Emiting no ticket to delete error";
        return;
    } else{
        //first to the delete on the server:
        qDebug() << "deleting order to:" << order_url << "/" << currentTicket;
        QNetworkRequest request;
        request.setUrl(QUrl(order_url + "/" + currentTicket));
        netManager2->deleteResource(request);
        qDebug() << "posting order log to" << order_url;
        //then log the order:
    }

}

void RestWidget::updateLog(QString comment, QString event){

    //QNetworkRequest request;
    //request.setUrl(QUrl(server_url +"/log"));

    //make the log xml:
    QDomDocument doc;

    QDomProcessingInstruction instr = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    doc.appendChild(instr);

    QDomElement root = doc.createElement( "log_entry" );
    doc.appendChild( root );

    QDomElement timeNode = doc.createElement("time");
    //timeNode.setNodeValue(QDateTime::currentDateTime().toString());
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    timeNode.appendChild(doc.createTextNode(date.toString("yyyy-MM-dd") + " " + time.toString()));
    root.appendChild(timeNode);

    QDomElement eventNode = doc.createElement("event");
    eventNode.appendChild(doc.createTextNode(event));
    root.appendChild(eventNode);

    QDomElement cell_idNode = doc.createElement("cell_id");
    cell_idNode.appendChild(doc.createTextNode("1"));
    root.appendChild(cell_idNode);

    QDomElement commentNode = doc.createElement("comment");
    commentNode.appendChild(doc.createTextNode(comment));
    root.appendChild(commentNode);

    qDebug() << doc.toString();

    QByteArray putData;
    putData.append(doc.toString());

    QNetworkRequest request;

    request.setUrl(QUrl(server_url +"/log"));

    QObject::connect(netManager2, SIGNAL(finished(QNetworkReply *)),this,
                     SLOT(receiveLogReply(QNetworkReply*)));

    QNetworkReply *reply = netManager2->post( request,putData );

}


void RestWidget::receiveLogReply(QNetworkReply *reply){

    QObject::disconnect(netManager2, SIGNAL(finished(QNetworkReply*)),this, SLOT(receiveLogReply(QNetworkReply*)));


    if(reply->error()>0){
        xmloutput->addItem(QTime::currentTime().toString() +" : " + reply->errorString());
        qDebug() << "no connection";
        emit connectionError();

    } else{

        qDebug() << "receiving response";

        QByteArray data = reply->readAll();
        QDomDocument doc;

        dataOutput->setText(data);
        doc.setContent(data);
        xmloutput->addItem(data);

        QString response = data;

        if(QString::compare("Created",response) == 0){
            qDebug()<<"not log received";
            emit logNotReceived();
        }

    }
    qDebug() << "logging done";
}

void RestWidget::testLog(){
    qDebug() << "testing the log function";
    updateLog("testing the log please ignore", "PML_Execute");

}








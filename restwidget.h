#ifndef RESTWIDGET_H
#define RESTWIDGET_H

#include <vector>
#include <QtGui>
#include <QDebug>
#include <QThread>
#include <QtCore/QUrl>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>
#include <QtXml/QDomDocument>
#include <QLabel>
#include <QVector>



class RestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RestWidget(QWidget *parent = 0, QListWidget *output=0);
    
signals:
    void sendOrder(QVector<int> *order); //will be used by getNewOrder slot!
    void connectionError();
    void noOrderError();
    void noTicketError();
    void noTicketToDeleteError();
    void logNotReceived();
    void loggingdone();
    void orderReportDone();



    
public slots:

    void getOrderUrls();
    void parseOrderUrls(QNetworkReply *reply);

    void getNewOrder();
    void parseOrderInfo(QNetworkReply *reply);
    //void takeOrder(QNetworkReply *reply);

    void orderDone();
    void testLog();

    void updateLog(QString comment, QString event);
    void receiveLogReply(QNetworkReply *reply);

private:
    bool getThisOrder(QUrl url);

    QString server_url;
    QString order_url;
    QString currentTicket;

    int order_ptr; //for tracking what order we are currently at.

    QString user;
    QString password; //not sure if needed!
    QString status;



    QVector<QString> *orderIDs;
    QVector<int> *currentOrder;

    QLabel *serverLabel;
    QLabel *statusLabel;
    QLabel *userLabel;

    QListWidget *xmloutput;
    QTextEdit *dataOutput;

    //QNetworkAccessManager *netManager;

    QNetworkAccessManager *netManager2;




    //QNetworkRequest *request;

    //std::vector<int> *currentOrder;
};

#endif // RESTWIDGET_H

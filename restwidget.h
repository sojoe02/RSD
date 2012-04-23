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



class RestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RestWidget(QWidget *parent = 0);
    
signals:
    void sendOrder(std::vector<int> *order); //will be used by getNewOrder slot!
    void connectionError();
    
public slots:
    void getNewOrder();    
    void testConnection();
    void deleteOrder(int value);

    void testRequest(QNetworkReply *reply);
    void getRequest(QNetworkReply *reply);




private:



    QString server_url;
    QString user;
    QString password; //not sure if needed!
    QString status;


    QLabel *serverLabel;
    QLabel *statusLabel;
    QLabel *userLabel;

     QListWidget *xmloutput;
     QTextEdit *dataOutput;

     QNetworkAccessManager *netManager;

     QNetworkAccessManager *netManager2;




    //QNetworkRequest *request;

    std::vector<int> *currentOrder;
};

#endif // RESTWIDGET_H

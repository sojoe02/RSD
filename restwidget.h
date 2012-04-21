#ifndef RESTWIDGET_H
#define RESTWIDGET_H

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
#include <vector>


class RestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RestWidget(QWidget *parent = 0);
    
signals:
    void sendOrder(std::vector<int> *order); //will be used by getNewOrder slot!
    
public slots:
    void getNewOrder();
    void deleteOrder(int value);


private:
    QString server_url;
    QString user;
    QString password; //not sure if needed!
    QString status;


    QLabel *serverLabel;
    QLabel *statusLabel;
    QLabel *userLabel;

    QListWidget *xmloutput;

    QNetworkAccessManager *netManager;
    QNetworkRequest *request;

    std::vector<int> *currentOrder;
};

#endif // RESTWIDGET_H

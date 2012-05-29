#ifndef OEEWIDGET_H
#define OEEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QElapsedTimer>

class OEEWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OEEWidget(QWidget *parent = 0);
    
signals:
    void error(int i);
    
public slots:
    void inputErr();
    void orderDone();
    void systemStopped();
    void systemStarted();
    void systemRunning();

    void orderStarted();

    void updateOEE();

private:
    QPushButton *button;
    QLabel *label;
    QLabel *OEEoutput;
    double OEEnumber;
    QVBoxLayout *layout;

    QElapsedTimer downtimer;
    QElapsedTimer cycletimer;
    QElapsedTimer operatingTime;



    qint64 totalOrders;
    qint64 faultyOrders;
    qint64 uptime;
    qint64 downtime;
    static const qint64 idealcycletime = 100000;


    
};

#endif // OEEWIDGET_H

#ifndef OEEWIDGET_H
#define OEEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTime>

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
    double cycletime;


    QTime downtimer;
    QTime cycletimer;
    QTime operatingtimer;

    int totalOrders;
    int faultyOrders;
    int uptime;
    int downtime;
    static const int idealcycletime = 10000;
    static const int plannedproductiontime=100;


    
};

#endif // OEEWIDGET_H

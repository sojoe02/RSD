#include "oeewidget.h"
#include "QtGui"
#include <QDebug>

OEEWidget::OEEWidget(QWidget *parent) :
    QWidget(parent)
{
    button = new QPushButton("Register Errors", this);
    button->setBaseSize(130,30);
    //button->setMaximumWidth(80);

    connect(button,SIGNAL(pressed()),this,SLOT(inputErr()));

    //set up a template for the OEE output:
    QString fonttemplate = tr("<font color='%1' size='%2'>%3</font>");


    OEEoutput = new QLabel(this);


    label = new QLabel(this);
    layout = new QVBoxLayout(this);
    layout->addWidget(button);
    layout->addWidget(label);
    layout->addWidget(OEEoutput);
    // layout->addWidget(OEEnumber);

    //this->setMaximumSize(150,200);
    this->setLayout(layout);
    OEEnumber = 0;
    QString tmp = QString::number(OEEnumber);

    OEEoutput->setText( fonttemplate.arg( "green", "12", tmp));
    //OEEnumber->setText( fonttemplate.arg( "red", "14","00" ));

    QTime time;

    //start all the timers:
    downtimer.start();
    cycletimer.start();
    operatingtimer.start();

    time.start();
    // operation
    qDebug() << time.elapsed();
    qDebug() << time.currentTime();
    operatingtimer.start();

    cycletime = 10000;
    faultyOrders = 0;
    totalOrders = 0;

    updateOEE();
}



void OEEWidget::inputErr(){
    bool ok;
    QInputDialog *inputdialog = new QInputDialog();

    int err = inputdialog->getInteger(this,tr("enter amount of faulty orders since last")
                                      ,tr("integer:"),1,0,100,1,&ok);
    if(ok){
        label->setText(tr("errors since last: %1 ").arg(err));
    }

    inputdialog->deleteLater();


}

void OEEWidget::updateOEE(){

    //calculate cyclenumber:
    double performance;

    performance = double(idealcycletime)/ double(cycletime);
    qDebug() << double(idealcycletime);
    qDebug() << double(cycletime);
    qDebug() << "performance is: " << performance;

    double availability;
    uptime = operatingtimer.elapsed()-downtime;
    //Availability = Operating Time / Planned Production Time
    availability = (double(uptime)-double(downtime)) / double(plannedproductiontime);
    qDebug() << "availability is: " << availability;

    double quality;
    quality = (double(totalOrders)-double(faultyOrders))/ double(totalOrders);
    qDebug() << "quality is: " << quality;

    qDebug() << "OEE is" << OEEnumber;
}

void OEEWidget::systemStopped(){
    downtimer.restart();
}

void OEEWidget::systemRunning(){
    downtime = downtimer.elapsed();
}

void OEEWidget::systemStarted(){
    operatingtimer.restart();
}

void OEEWidget::orderStarted(){
    cycletimer.restart();
}

void OEEWidget::orderDone(){
    cycletime = (cycletimer.elapsed()-cycletime)/cycletime;
}





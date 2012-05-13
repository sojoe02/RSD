#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "qextserialport.h"


class SerialComm : public QWidget
{
    Q_OBJECT
public:
    explicit SerialComm(QWidget *parent = 0);
    int sendString(QString string);

private:

    QextSerialPort* port;
    QString device;


};

#endif // SERIALCOMM_H

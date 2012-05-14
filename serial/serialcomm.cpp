#include "serialcomm.h"
#include "qextserialport.h"
#include "QtGui"

SerialComm::SerialComm(QWidget *parent, QString device) :
    QWidget(parent), device(device)
{
    port = new QextSerialPort(device);


}

int SerialComm::sendString(QString string){

    port->open(QIODevice::ReadWrite);

    if(port->isOpen()){
        port->setBaudRate(BAUD9600);
        port->setParity(PAR_EVEN);
        port->setFlowControl(FLOW_OFF);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);
    } else return(-1);

    QByteArray ba = string.toLatin1();
    const char *message = ba.data();

    port->write(message);

    return 1;

}

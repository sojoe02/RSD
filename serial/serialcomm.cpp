#include "serialcomm.h"
#include "qextserialport.h"
#include "QtGui"

SerialComm::SerialComm(QWidget *parent, QString device) :
    QWidget(parent), device(device)
{
    port = new QextSerialPort(device);
}

void SerialComm::closeSerial(){
    port->close();
}

void SerialComm::initSerial(){
    port->open(QIODevice::ReadWrite);
}

int SerialComm::sendString(QString string){

    if(port->isOpen()){
        port->setBaudRate(BAUD9600);
        port->setParity(PAR_EVEN);
        port->setFlowControl(FLOW_OFF);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);
    } else return(-1);

    QByteArray ba = string.toLatin1();
    const char *message = ba.data();

    char output_buffer[64];
    int i, message_length;
    message_length = string.size();

    for(i=0;i<message_length;i++){
        output_buffer[i] = message[i];
    }

    port->write(output_buffer,message_length);

    return 1;

}

int SerialComm::debugSendString(QString string){

    int messageLength = string.size();

    qDebug()<<messageLength;

    port->open(QIODevice::ReadWrite);

    if(port->isOpen()){
        port->setBaudRate(BAUD9600);
        port->setParity(PAR_EVEN);
        port->setFlowControl(FLOW_OFF);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);
        QByteArray ba = string.toLatin1();
        //const char *message = ba.data();

        //port->write(message,messageLength);

        //port->writeData(message,64);
    } else return(-1);

    char output_buffer[64];
    int i, message_length;
    message_length = string.size();

    for(i=0;i<message_length;i++){
        output_buffer[i] = string.at(i).toLatin1();
        qDebug() << output_buffer[i];
    }

    qDebug()<<"message length is: " <<message_length;

    port->write(output_buffer,message_length);

    port->close();

    return 1;

}

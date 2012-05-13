#include "oeewidget.h"
#include "QtGui"

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
    this->setMaximumSize(150,200);
    this->setLayout(layout);

    OEEoutput->setText( fonttemplate.arg( "green", "12","OEE : ##" ) );


}

void OEEWidget::inputErr(){
    bool ok;
    QInputDialog *inputdialog = new QInputDialog();

    int err = inputdialog->getInteger(this,tr("enter amount of faulty orders since last")
                                      ,tr("integer:"),25,0,100,1,&ok);
    if(ok){
        label->setText(tr("errors since last: %1 ").arg(err));
    }

    inputdialog->deleteLater();


}

#include "oeewidget.h"
#include "QtGui"

OEEWidget::OEEWidget(QWidget *parent) :
    QWidget(parent)
{
    button = new QPushButton("Register Errors", this);
    button->setMaximumWidth(80);

    connect(button,SIGNAL(pressed()),this,SLOT(inputErr()));

    label = new QLabel(this);
    layout = new QVBoxLayout(this);
    layout->addWidget(button);
    layout->addWidget(label);
    this->setMaximumSize(150,200);
    this->setLayout(layout);


}

void OEEWidget::inputErr(){
    bool ok;
    QInputDialog *inputdialog = new QInputDialog();

    int err = inputdialog->getInteger(this,tr("enter amount of faulty orders since last")
                                      ,tr("integer:"),25,0,100,1,&ok);
    if(ok){
        label->setText(tr("errors since last: %1 ").arg(err));
    }
}

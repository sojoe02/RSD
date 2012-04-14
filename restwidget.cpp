#include "restwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

RestWidget::RestWidget(QWidget *parent) :
    QWidget(parent)
{
    QPushButton *button1 = new QPushButton(QApplication::translate("restwidget", "this is restwidget button"));
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(button1);
    setLayout(layout);


}

#include "rsdmainwindow.h"
#include "packmlw.h"
#include "restwidget.h"
#include "oeewidget.h"



RSDMainWindow::RSDMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //DEFINE WIDGETS:
    QPushButton *button1 = new QPushButton(QApplication::translate("rsdmainwindow", "This belongs to main window"));
    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *central = new QWidget();
    PackMLw *packml = new PackMLw();
    RestWidget *rwidget = new RestWidget();
    OEEWidget *oeewidget = new OEEWidget();


    layout->addWidget(packml);
    layout->addWidget(oeewidget);
    layout->addWidget(button1);
    layout->addWidget(rwidget);


    central->setLayout(layout);

    setCentralWidget(central);

}

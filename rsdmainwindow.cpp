#include "rsdmainwindow.h"
#include "packmlw.h"
#include "restwidget.h"
#include "oeewidget.h"
#include "debugwidget.h"



RSDMainWindow::RSDMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //DEFINE WIDGETS:
    //QPushButton *button1 = new QPushButton(QApplication::translate("rsdmainwindow", "This belongs to main window"));
    QGridLayout *layout = new QGridLayout();
    QWidget *central = new QWidget();

    RestWidget *rwidget = new RestWidget();

    //qDebug() << "What";

    QTabWidget *tabWidget = new QTabWidget();


    PackMLw *packml = new PackMLw(this,rwidget);
    packml->setMaximumWidth(700);

    QHBoxLayout *mlayout = new QHBoxLayout();
    mlayout->addWidget(packml);
    mlayout->addWidget(new OEEWidget());

    QWidget *main = new QWidget();

    main->setLayout(mlayout);


    tabWidget->addTab(main, tr("main window"));
    //tabWidget->addTab(new OEEWidget(), tr("OEE"));
    tabWidget->addTab(new DebugWidget(),tr("Debug"));
    tabWidget->addTab(rwidget, tr("Rest"));

    //    RestWidget *rwidget = new RestWidget();
    //    PackMLw *packml = new PackMLw(this,rwidget);
    //    OEEWidget *oeewidget = new OEEWidget();

    layout->addWidget(tabWidget);
    //    layout->addWidget(packml,0,0);
    //    layout->addWidget(oeewidget,0,1);
    //    layout->addWidget(rwidget,1,0,1,2);


    central->setLayout(layout);

    setCentralWidget(central);

}

TEMPLATE = app
CONFIG += console
CONFIG += qt
INCLUDEPATH += /usr/include/opencv2,usr/lib

include(qextserialport-1.2beta1/src/qextserialport.pri)



SOURCES += main.cpp \
    packmlw.cpp \
    rsdmainwindow.cpp \
    restwidget.cpp \
    oeewidget.cpp \
    visionwidget.cpp \
    vision/VisionSystem.cpp \
    serial/serialcomm.cpp\
    plccomms/rsd_server.cpp \
    plccomms/serverthread.cpp \
    debugwidget.cpp\
    serial/serialrobot.cpp\
    serial/serial_fct.cpp



HEADERS += \
    packmlw.h \
    rsdmainwindow.h \
    restwidget.h \
    oeewidget.h \
    visionwidget.h \
    vision/VisionSystem.h \
    serial/serialcomm.h \
    plccomms/rsd_server.h \
    plccomms/serverthread.h \
    debugwidget.h \
    serial/serialrobot.h\
    serial/SerialStream.h\
    serial/serial_fct.h

OTHER_FILES +=

RESOURCES += \
    packml-icons.qrc

FORMS +=
QT += network xml

CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L/usr/lib -lserial


#INCLUDEPATH += /usr/lib
#DEPENDPATH += /usr/lib

#unix:!macx:!symbian: LIBS += -L$$PWD/../../../../usr/lib/ -lserial

#INCLUDEPATH += $$PWD/../../../../usr/include
#DEPENDPATH += $$PWD/../../../../usr/include

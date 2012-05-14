TEMPLATE = app
CONFIG += console
CONFIG += qt
INCLUDEPATH += /usr/include/opencv2

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
    debugwidget.cpp
    #serial/serial_fct.cpp


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
    debugwidget.h
    #serial/serial_functions.h




OTHER_FILES +=

RESOURCES += \
    packml-icons.qrc

FORMS +=
QT += network xml

CONFIG += link_pkgconfig
PKGCONFIG += opencv


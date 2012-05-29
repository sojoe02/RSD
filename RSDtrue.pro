TEMPLATE = app
CONFIG += console
CONFIG += qt
INCLUDEPATH += /usr/include/opencv2,usr/lib

SOURCES += main.cpp \
    packmlw.cpp \
    rsdmainwindow.cpp \
    restwidget.cpp \
    oeewidget.cpp \
    visionwidget.cpp \
    vision/VisionSystem.cpp \
    debugwidget.cpp\
    serial/serialrobot.cpp\
    serial/serial_fct.cpp\
    serial/serial_fct2.cpp \
    orderlogic.cpp \
    frame.cpp



HEADERS += \
    packmlw.h \
    rsdmainwindow.h \
    restwidget.h \
    oeewidget.h \
    visionwidget.h \
    vision/VisionSystem.h \
    debugwidget.h \
    serial/serialrobot.h\
    serial/SerialStream.h\
    serial/serial_fct.h\
    serial/serial_fct2.h \
    orderlogic.h \
    frame.h

OTHER_FILES +=

RESOURCES += \
    packml-icons.qrc

FORMS +=
QT += network xml

CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L/usr/lib -lserial

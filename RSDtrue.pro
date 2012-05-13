TEMPLATE = app
CONFIG += console
CONFIG += qt
INCLUDEPATH += /usr/include/opencv2

SOURCES += main.cpp \
    packmlw.cpp \
    rsdmainwindow.cpp \
    restwidget.cpp \
    oeewidget.cpp \
    visionwidget.cpp \
    vision/VisionSystem.cpp

HEADERS += \
    packmlw.h \
    rsdmainwindow.h \
    restwidget.h \
    oeewidget.h \
    visionwidget.h \
    vision/VisionSystem.h

OTHER_FILES +=

RESOURCES += \
    packml-icons.qrc

FORMS +=
QT += network xml

CONFIG += link_pkgconfig
PKGCONFIG += opencv


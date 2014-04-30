QT       += core gui
QT       += widgets

TARGET = timeLabel
TEMPLATE = lib

DEFINES += EX_LIBRARY

HEADERS += \
    typedef.h \
    bufffunctions.h \
    timelabel.h \
    declare_global.h

SOURCES += \
    bufffunctions.cpp \
    timelabel.cpp

FORMS += \
    timelabel.ui


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

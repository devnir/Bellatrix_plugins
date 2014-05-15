QT       += core gui
QT       += widgets

TARGET = SatView
TEMPLATE = lib

DEFINES += EX_LIBRARY

HEADERS += \
    typedef.h \
    bufffunctions.h \
    main.h \
    declare_global.h

SOURCES += \
    bufffunctions.cpp \
    main.cpp

FORMS += \
    SatView.ui


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    res.qrc

QT       += core gui
QT       += widgets

TARGET = Graphic
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
    Graphic.ui


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

include ( c:/Qwt-6.1.0/features/qwt.prf )

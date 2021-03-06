QT       += core gui
QT       += widgets

TARGET = PluginName
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
    PluginName.ui


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

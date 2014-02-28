QT       += core gui
QT       += widgets

TARGET = versionForm
TEMPLATE = lib

DEFINES += EX_LIBRARY

INCLUDEPATH += ../bellatrix/src/

HEADERS += \
    versionform.h \
    ../bellatrix/src/declare_global.h \
    ../BuffFunctions/typedef.h \
    typedef.h \
    bufffunctions.h

SOURCES += \
    versionform.cpp \
    bufffunctions.cpp

FORMS += \
    versionform.ui


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

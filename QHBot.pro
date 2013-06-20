#-------------------------------------------------
#
# Project created by QtCreator 2012-06-14T16:59:18
#
#-------------------------------------------------

QT+=core gui network xml

TARGET = QHBot
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qhbot.cpp \
    qhbotuser.cpp \
    qhbotusermanager.cpp \
    qhbotcommands.cpp \
    qhbotgroup.cpp

INCLUDEPATH += $$quote(qxmpp/include)

win32 {
    LIBS += -L$$quote($$_PRO_FILE_PWD_/qxmpp/lib) -lqxmpp0
}

unix
{
    LIBS += -lqxmpp0
}

HEADERS += \
    qhbot.h \
    qhbotuser.h \
    qhbotusermanager.h \
    qhbotcommands.h \
    qhbotgroup.h

RESOURCES += \
    resource.qrc

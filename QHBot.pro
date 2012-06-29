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
LIBS += -lqxmpp -ldnsapi

HEADERS += \
    qhbot.h \
    qhbotuser.h \
    qhbotusermanager.h \
    qhbotcommands.h \
    qhbotgroup.h

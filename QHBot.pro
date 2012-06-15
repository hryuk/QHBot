#-------------------------------------------------
#
# Project created by QtCreator 2012-06-14T16:59:18
#
#-------------------------------------------------

QT+=core gui network

TARGET = QHBot
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += $$quote(qxmpp/include)
LIBS += -lqxmpp

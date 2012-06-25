#include "qhbotuser.h"

QHBotUser::QHBotUser(QObject *parent): QObject(parent)
{
}

void QHBotUser::setNick(QString nick)
{
}

void QHBotUser::setJID(QString jid)
{
}

void QHBotUser::setPresence(QXmppPresence presence)
{
}

QString QHBotUser::getNick()
{
    //TODO
    return QString();
}

QString QHBotUser::getJID()
{
    //TODO
    return QString();
}

QXmppPresence QHBotUser::getPresence()
{
    return this->Presence;
}

#include "qhbotuser.h"

QHBotUser::QHBotUser(QObject *parent): QObject(parent)
{
}

void QHBotUser::setNick(QString nick)
{
    this->nick=nick;
}

void QHBotUser::setJID(QString jid)
{
    this->jid=jid;
}

void QHBotUser::setPresence(QXmppPresence Presence)
{
    this->Presence=Presence;
}

QString QHBotUser::getNick()
{
    return this->nick;
}

QString QHBotUser::getJID()
{
    return this->jid;
}

QXmppPresence QHBotUser::getPresence()
{
    return this->Presence;
}

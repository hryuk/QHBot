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
    return this->nick;
}

QString QHBotUser::getJID()
{
    return this->jid;
}

QXmppPresence QHBotUser::getPresence()
{
    return this->presence;
}

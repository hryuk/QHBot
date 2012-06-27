#include "qhbotuser.h"

QHBotUser::QHBotUser(QObject *parent): QObject(parent)
{
}

void QHBotUser::setNick(QString nick)
{
    this->nick=nick;
    emit nickChange(this->jid,this->nick);
}

void QHBotUser::setJID(QString jid)
{
    this->jid=jid;
}

void QHBotUser::setPresence(QString ResourceName,QXmppPresence Presence)
{
    if(nodos.contains(ResourceName)){
        nodos[ResourceName] = Presence;
    }else{
        nodos.insert(ResourceName,Presence);
    }
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
QXmppPresence QHBotUser::getPresence(QString resource)
{
    return nodos.value(resource);
}

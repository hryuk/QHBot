#include "qhbotuser.h"

QHBotUser::QHBotUser(QString jid)
{
    this->jid=jid;
    this->available=false;
}

QString QHBotUser::getJID()
{
    return this->jid;
}

void QHBotUser::setPresence(QString resource, Status status)
{
    resources[resource]=status;

    if(!resources.values().contains(Online))
    {
        available=false;
        return;
    }

    QMap<QString,Status>::iterator i;
    for(i=resources.begin();i!=resources.end();i++)
    {
        if(i.value()==Online)
        {
            this->available=true;
            this->activeResource=i.key();
            return;
        }
    }
}
/*
QString QHBotUser::getUsername()
{
    return this->username;
}
*/
QString QHBotUser::getResource()
{
    return activeResource;
}

bool QHBotUser::isAvailable()
{
    return available;
}

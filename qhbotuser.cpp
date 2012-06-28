#include "qhbotuser.h"
#include "qhbotusermanager.h"

QHBotUser::QHBotUser(QObject *parent): QObject(parent)
{
}
QHBotUser::QHBotUser(const QXmppRosterIq::Item &item, QObject *parent): QObject(parent){
    this->jid = item.bareJid();
    this->nick = item.name();
}

void QHBotUser::setNick(QString newNick)
{
    this->nick=newNick;
    emit nickChange(this->jid,this->nick);

    /*
    QHBotUserManager* manager = ((QHBotUserManager*)parent());
    manager->updateNick(this->jid,this->nick);
    */
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
}

QString QHBotUser::getNick()
{
    return this->nick;
}

QString QHBotUser::getJID()
{
    return this->jid;
}
QMap<QString, QXmppPresence> QHBotUser::getPresence()
{
    return nodos;
}
QXmppPresence QHBotUser::getPresence(QString resource)
{
    return nodos.value(resource);
}
bool QHBotUser::isAvalible(){
    bool avalible = false;
    foreach(QXmppPresence presence,nodos.values()){
        if(presence.type() == QXmppPresence::Available){
            avalible = true;
            break;
        }
    }
    return avalible;
}
bool QHBotUser::isAvalible(QString resourceName){
    return nodos.contains(resourceName)?(nodos.value(resourceName).type() == QXmppPresence::Available):false;
}

QString QHBotUser::getLastResourceUsed(){
    return lastResourceUsed;
}
void QHBotUser::setLastResourceUsed(QString resourceName){
    lastResourceUsed = resourceName;
}

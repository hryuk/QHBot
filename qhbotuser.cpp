#include "qhbotuser.h"
#include "qhbotgroup.h"
#include "qhbotusermanager.h"

QHBotUser::QHBotUser(QObject *parent): QObject(parent)
{
}
QHBotUser::QHBotUser(const QXmppRosterIq::Item &item, QObject *parent): QObject(parent){
    this->jid = item.bareJid();
    this->nick = item.name();
    this->Snooze = false;
    //Si no hay nick en el roster, se usara  el usuario como nick
    if(nick == "")nick = jid.split("@").at(0);
}

void QHBotUser::setNick(QString newNick)
{
    this->nick=newNick;
    emit nickChange(this->jid,this->nick);
}

void QHBotUser::setJID(QString jid)
{
    this->jid=jid;
}
void QHBotUser::update(QXmppRosterIq::Item item)
{

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

bool QHBotUser::isAvailable(){
    bool available = false;
    foreach(QXmppPresence presence,nodos.values())
    {
        if(presence.type() == QXmppPresence::Available)
        {
            available = true;
            break;
        }
    }
    return available;
}

bool QHBotUser::isAvailable(QString resourceName)
{
    return nodos.contains(resourceName)?(nodos.value(resourceName).type() == QXmppPresence::Available):false;
}

void QHBotUser::setLastResourceUsed(QString resourceName)
{
    lastResourceUsed = resourceName;
}

void QHBotUser::setSnooze(bool status)
{
    this->Snooze = status;
}

bool QHBotUser::isSnoozing()
{
    return this->Snooze;
}
bool QHBotUser::isGroupMember(QString groupName){
    bool isMember = false;
    for(int i = 0;i<memberGroups.count();i++){
        if(memberGroups.at(i)->getName() == groupName){
            isMember = true;
            break;
        }
    }
    return isMember;
}
void QHBotUser::addToGroup(QHBotGroup& grupo){
    //Si no es ya miembro lo agrego
    if(!isGroupMember(grupo.getName())){
        memberGroups.append(&grupo);
        //Lo agrego tambien al objeto group
        grupo.addMember(*this);
    }
}
void QHBotUser::delToGroup(QString grupoName){
    //busco el grupo y lo borro de la lista
    for(int i = 0;i<memberGroups.count();i++){
        if(memberGroups.at(i)->getName() == grupoName){
            //Primero borro al user del grupo y luego borro el grupo de la lista de grupos miembro
            QHBotGroup* groupToDel = memberGroups.at(i);
            memberGroups.removeAt(i);
            groupToDel->removeMember(*this);
            break;
        }
    }
}

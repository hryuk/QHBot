#include "qhbotgroup.h"
#include "qhbotuser.h"

QHBotGroup::QHBotGroup(QString &name, QObject *parent) :
    QObject(parent)
{
    this->name = name;
}

void QHBotGroup::removeMember(QHBotUser &user)
{
    members.removeOne(&user);
}

void QHBotGroup::removeMember(QString jid_or_nick)
{
    //Si contiene la @ es un jido. si no es un nick
    if(jid_or_nick.contains("@")){
        for(int i = 0;i<members.count();i++){
            if(members.at(i)->getJID() == jid_or_nick){
                members.removeAt(i);
                break;
            }
        }
    }
    else
    {
        for(int i = 0;i<members.count();i++){
            if(members.at(i)->getNick() == jid_or_nick){
                members.removeAt(i);
            }
        }
    }
}

void QHBotGroup::addMember(QHBotUser &user)
{
    if(!isMember(user))members.append(&user);
}

void QHBotGroup::grantPrivilege(int priv)
{
}

void QHBotGroup::revokePrivilege(int priv)
{
}
QHBotUser* QHBotGroup::getMember(QString &jid){
    QHBotUser* member = 0;
    for(int i = 0;i<members.count();i++){
        if(members.at(i)->getJID() == jid){
            member = members.at(i);
            break;
        }
    }
    return member;
}

QString QHBotGroup::getName(){
    return this->name;
}
bool QHBotGroup::isMember(QHBotUser &user){
   return members.contains(&user);
   /*
    bool userFound = false;
    //Busco el usuario en la lista de miembros
    QHBotUser* currentUser;
    for(int i = 0;i<members.count();i++ ){
        currentUser = members.at(i);
        if(currentUser->getJID() == user.getJID()){
            userFound = true;
            break;
        }
    }
    return userFound;*/
}

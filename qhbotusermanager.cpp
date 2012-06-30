#include "qhbotusermanager.h"
#include "qhbot.h"

QHBotUserManager::QHBotUserManager(QXmppRosterManager* RosterManager, QObject *parent): QObject()
{
    this->RosterManager=RosterManager;
    connect(RosterManager,SIGNAL(presenceChanged(const QString&,const QString&)),this,SLOT(updateUserPresence(const QString&,const QString&)));
    connect(RosterManager,SIGNAL(rosterReceived ()),this,SLOT(populateUsers()));
    //Roster update y push
    connect(RosterManager,SIGNAL(itemAdded(const QString&)),this,SLOT(updateUserList(const QString&)));
    connect(RosterManager,SIGNAL(itemChanged(const QString&)),this,SLOT(updateUserList(const QString&)));
    connect(RosterManager,SIGNAL(itemRemoved(const QString&)),this,SLOT(updateUserList(const QString&)));
}

void QHBotUserManager::populateUsers()
{
    foreach(QString jid,RosterManager->getRosterBareJids())
    {
        //FIXME: "limpiar" jid?
        QXmppRosterIq::Item item=RosterManager->getRosterEntry(jid);
        QHBotUser* user=new QHBotUser(item,this);
        //Aqui se rellena la lista de usuarios, no se recivio todavia la presencia de los usuarios
        /*
        //Guardo la presencia de todos los usuarios
        foreach(QString resourceName,RosterManager->getResources(jid))
        {
            user->setPresence(resourceName,RosterManager->getPresence(jid,resourceName));
        }*/

        connect(user,SIGNAL(nickChange(const QString&,const QString&)),this,SLOT(updateNick(const QString&,const QString&)));
        this->users.append(user);
    }
}
void QHBotUserManager::updateUserList(const QString &bareJid){
    QHBotUser* user;
    //Si esta lo modificamos
    if((user = getUser(bareJid))){
        QXmppRosterIq::Item item = RosterManager->getRosterEntry(bareJid);
        //Si esta vacio, modificamos el roster, boramos el roster
        if(item.bareJid() == ""){
            users.removeOne(user);
            delete user;
        }
        else //Modificamos el user
        {

        }
    }
    else //Si no esta lo añadimos
    {
        //Creo un nuevo usuario
        user = new QHBotUser(RosterManager->getRosterEntry(bareJid),this);
        connect(user,SIGNAL(nickChange(const QString&,const QString&)),this,SLOT(updateNick(const QString&,const QString&)));
        this->users.append(user);
    }
}

void QHBotUserManager::updateNick(const QString& bareJid,const QString& newNick)
{
    //qDebug()<<"Update Nick!";
    RosterManager->renameItem(bareJid,newNick);
}

void QHBotUserManager::updateUserPresence(const QString &bareJid, const QString &resource)
{
    QHBotUser* user=this->getUser(bareJid);
    if(user==0) return;
    user->setPresence(resource,RosterManager->getPresence(bareJid,resource));
}

bool QHBotUserManager::inviteUser(QString jid)
{
    return RosterManager->subscribe(jid);
}

void QHBotUserManager::removeUser(QHBotUser &user)
{
    RosterManager->unsubscribe(user.getJID());
    //FIXME: eliminar de la lista de users
}

void QHBotUserManager::removeUser(QString jid)
{
    RosterManager->unsubscribe(jid);
    //FIXME: eliminar de la lista de users
}

QHBotUser* QHBotUserManager::getUser(QString jid)
{
    foreach(QHBotUser* user,this->users)
    {
        if(user->getJID()==jid)
        {
            return user;
        }
    }

    return 0;
}

QList<QHBotUser*> QHBotUserManager::getUsers()
{
    return this->users;
}
QHBotGroup* QHBotUserManager::getGroup(QString name){
    foreach(QHBotGroup* group,this->groups)
    {
        /*if(group->getName()==name)
        {
            return group;
        }*/
    }

    return 0;
}

QList<QHBotGroup*> QHBotUserManager::getGroups(){
    return QList<QHBotGroup*>();
}

void QHBotUserManager::addGroup(QHBotGroup& grupo){

}

void QHBotUserManager::removeGroup(QString name){

}

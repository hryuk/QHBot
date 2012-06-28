#include "qhbotusermanager.h"
#include "qhbot.h"

QHBotUserManager::QHBotUserManager(QXmppRosterManager* RosterManager, QObject *parent): QObject(parent)
{
    this->RosterManager=RosterManager;
    connect(RosterManager,SIGNAL(presenceChanged(const QString&,const QString&)),this,SLOT(updateUserPresence()));
    connect(RosterManager,SIGNAL(rosterReceived ()),this,SLOT(populateUsers()));
}

void QHBotUserManager::populateUsers()
{
    foreach(QString jid,RosterManager->getRosterBareJids())
    {
        //FIXME: "limpiar" jid?
        QXmppRosterIq::Item item=RosterManager->getRosterEntry(jid);
        QHBotUser* user=new QHBotUser(item,this);
        //Guardo la presencia de todos los usuarios
        foreach(QString resourceName,RosterManager->getResources(jid)){
            user->setPresence(resourceName,RosterManager->getPresence(jid,resourceName));
        }
        connect(user,SIGNAL(QHBotUser::nickChange(QString&,QString&)),this,SLOT(updateNick(QString&,QString&)));
        this->users.append(user);
    }
}
void QHBotUserManager::updateNick(const QString& bareJid,const QString& newNick)
{
    QXmppRosterIq::Item* item = new QXmppRosterIq::Item(RosterManager->getRosterEntry(bareJid));
    QXmppRosterIq* rosterSet = new QXmppRosterIq();
    item->setGroups( RosterManager->getRosterEntry(bareJid).groups());
    item->setName(newNick);
    //item->setSubscriptionType(QXmppRosterIq::Item::Remove);
    rosterSet->setType(QXmppIq::Set);
    rosterSet->addItem(*item);

    //emit sendRosterIq(rosterSet);
    QHBot* bot = ((QHBot*)parent());
    bot->sendIQ(rosterSet);
}

void QHBotUserManager::updateUserPresence(const QString &bareJid, const QString &resource)
{
    QHBotUser* user=this->getUser(bareJid);
    if(user==0) return;
    user->setPresence(resource,RosterManager->getPresence(bareJid,resource));
}

bool QHBotUserManager::inviteUser(QString jid)
{

    return RosterManager->subscribe("zero@h-sec.org");
    //return RosterManager->subscribe(jid);
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

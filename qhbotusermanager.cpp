#include "qhbotusermanager.h"

QHBotUserManager::QHBotUserManager(QXmppRosterManager* RosterManager, QObject *parent): QObject(parent)
{
    this->RosterManager=RosterManager;
    connect(RosterManager,SIGNAL(presenceChanged(const QString&,const QString&)),this,SLOT(updateUserPresence()));
    connect(RosterManager,SIGNAL(rosterReceived ()),this,SLOT(populateUsers()));
}

void QHBotUserManager::populateUsers()
{
    QStringList bareJids=RosterManager->getRosterBareJids();
    foreach(QString jid,bareJids)
    {
        //FIXME: "limpiar" jid?
        QHBotUser* user=new QHBotUser();
        user->setJID(jid);
        user->setNick(jid);
        //FIXME: tener en cuenta todos los resources?
        user->setPresence(RosterManager->getPresence(jid,RosterManager->getResources(jid).at(0)));
        this->users.append(user);
    }
}

void QHBotUserManager::updateUserPresence(const QString &bareJid, const QString &resource)
{
    QHBotUser* user=this->getUser(bareJid);
    if(user==0) return;
    user->setPresence(RosterManager->getPresence(bareJid,resource));
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

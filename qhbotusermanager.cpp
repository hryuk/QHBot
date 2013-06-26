#include "qhbotusermanager.h"
#include "qhbot.h"

QHBotUserManager::QHBotUserManager(QXmppRosterManager* RosterManager, QObject *parent): QObject(parent)
{
    this->RosterManager=RosterManager;
    connect(RosterManager,SIGNAL(presenceChanged(const QString&,const QString&)),this,SLOT(updateUserPresence(const QString&,const QString&)));
    connect(RosterManager,SIGNAL(rosterReceived ()),this,SLOT(populateUsers()));
    connect(RosterManager,SIGNAL(itemAdded(const QString&)),this,SLOT(addUser(const QString&)));
    connect(RosterManager,SIGNAL(itemRemoved(const QString&)),this,SLOT(removeUser(const QString&)));
}

void QHBotUserManager::populateUsers()
{
    foreach(QHBotUser* user,this->users)
    {
        user->deleteLater();
    }
    users.clear();

    foreach(QString jid,RosterManager->getRosterBareJids())
    {
        users.append(new QHBotUser(jid));
    }
}

void QHBotUserManager::updateUserPresence(const QString &bareJid, const QString &resource)
{
    QHBotUser* user=getUser(bareJid);
    if(user==0) return;

    qDebug()<<"CAMBIO PRESENCIA!!!";

    QXmppPresence presence=RosterManager->getPresence(bareJid,resource);
    if(presence.type()!=QXmppPresence::Available)
    {
        if(user->resources.contains(resource))
        {
            qDebug()<<"1!!!";
            user->setPresence(resource,QHBotUser::Offline);
        }
        else
        {
            qDebug()<<"2!!!";
            user->resources.insert(resource,QHBotUser::Offline);
        }
        return;
    }

    switch(presence.availableStatusType())
    {
        case QXmppPresence::Status::Online:
        case QXmppPresence::Status::Chat:
            if(user->resources.contains(resource))
            {
                qDebug()<<"3!!!";
                user->setPresence(resource,QHBotUser::Online);
            }
            else
            {
                qDebug()<<"4!!!";
                user->resources.insert(resource,QHBotUser::Online);
            }
        break;

        case QXmppPresence::Status::Away:
        case QXmppPresence::Status::DND:
        case QXmppPresence::Status::Invisible:
            if(user->resources.contains(resource))
            {
                qDebug()<<"5!!!";
                user->setPresence(resource,QHBotUser::Offline);
            }
            else
            {
                qDebug()<<"6!!!";
                user->resources.insert(resource,QHBotUser::Offline);
            }
        break;
    }
}

void QHBotUserManager::addUser(const QString &bareJid)
{
    QHBotUser* user=new QHBotUser(bareJid);
    this->users.append(user);
}

bool QHBotUserManager::inviteUser(QString jid)
{
    return RosterManager->subscribe(jid);
}

void QHBotUserManager::removeUser(const QString &bareJid)
{
    RosterManager->unsubscribe(bareJid);

    foreach(QHBotUser* user,this->users)
    {
        if(user->getJID()==bareJid)
        {
            users.removeOne(user);
        }
    }
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

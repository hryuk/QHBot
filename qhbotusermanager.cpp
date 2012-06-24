#include "qhbotusermanager.h"

QHBotUserManager::QHBotUserManager(QXmppRosterManager* RosterManager, QObject *parent): QObject(parent)
{
    connect(RosterManager,SIGNAL(presenceChanged(const QString&,const QString&)),this,SLOT(updateUserPresence()));
    connect(RosterManager,SIGNAL(rosterReceived ()),this,SLOT(populateUsers()));
}

void QHBotUserManager::populateUsers()
{

}

void QHBotUserManager::updateUserPresence(const QString &bareJid, const QString &resource)
{

}

void QHBotUserManager::inviteUser(QString jid)
{

}

void QHBotUserManager::removeUser(QHBotUser &user)
{
}

void QHBotUserManager::removeUser(QString jid)
{
}

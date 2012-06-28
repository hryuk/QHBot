#ifndef QHBOTUSERMANAGER_H
#define QHBOTUSERMANAGER_H

#include <QObject>
#include <QList>
#include <QXmppRosterManager.h>

#include <QXmppRosterManager.h>
#include "qhbotuser.h"
#include "qhbotgroup.h"

class QHBotUser;

class QHBotUserManager : public QObject
{
    Q_OBJECT
public:
    explicit QHBotUserManager(QXmppRosterManager* RosterManager,QObject *parent = 0);

private:
    QList<QHBotUser*> users;
    QList<QHBotGroup*> groups;
    QXmppRosterManager* RosterManager;
    
signals:
    void sendRosterIq(QXmppIq* iq);
    
public slots:
    void populateUsers();
    void updateNick(const QString& bareJid,const QString& newNick);
    void updateUserPresence(const QString &bareJid,const QString &resource);
    bool inviteUser(QString jid);
    void removeUser(QHBotUser &user);
    void removeUser(QString jid);
    QHBotUser* getUser(QString jid);
    QList<QHBotUser*> getUsers();
    
};

#endif // QHBOTUSERMANAGER_H

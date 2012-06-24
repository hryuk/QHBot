#ifndef QHBOTUSERMANAGER_H
#define QHBOTUSERMANAGER_H

#include <QObject>
#include <QList>
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
    
public slots:
    void populateUsers();
    void updateUserPresence(const QString &bareJid,const QString &resource);
    bool inviteUser(QString jid);
    void removeUser(QHBotUser &user);
    void removeUser(QString jid);
    QHBotUser* getUser(QString jid);
};

#endif // QHBOTUSERMANAGER_H

#ifndef QHBOTUSERMANAGER_H
#define QHBOTUSERMANAGER_H

#include <QObject>
#include <QList>
#include <QXmppRosterManager.h>

#include "qhbotuser.h"

class QHBotUser;

class QHBotUserManager : public QObject
{
    Q_OBJECT
public:
    explicit QHBotUserManager(QXmppRosterManager* RosterManager,QObject *parent = 0);
    QHBotUser* getUser(QString jid);
    QList<QHBotUser*> getUsers();

private:
    QList<QHBotUser*> users;
    QXmppRosterManager* RosterManager;
    
signals:
    /*
    void requestSendRosterIq(QXmppIq* iq);
    */
    
public slots:
    void populateUsers();
    void updateUserPresence(const QString &bareJid,const QString &resource);
    bool inviteUser(QString jid);

private slots:
    void addUser(const QString&);
    void removeUser(const QString&);
    
};

#endif // QHBOTUSERMANAGER_H

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
    QHBotUser* getUser(QString jid);
    QList<QHBotUser*> getUsers();
    QHBotGroup* getGroup(QString name);
    QList<QHBotGroup*> getGroups();


private:
    QList<QHBotUser*> users;
    QList<QHBotGroup*> groups;
    QXmppRosterManager* RosterManager;
    
signals:
    /*
    void requestSendRosterIq(QXmppIq* iq);
    */
    
public slots:
    void populateUsers();
    void updateNick(const QString& bareJid,const QString& newNick);
    void updateUserPresence(const QString &bareJid,const QString &resource);
    void updateUserList(const QString& bareJid);
    bool inviteUser(QString jid);
    void removeUser(QHBotUser &user);
    void removeUser(QString jid);
    void addGroup(QHBotGroup& grupo);
    void removeGroup(QString name);
    
};

#endif // QHBOTUSERMANAGER_H

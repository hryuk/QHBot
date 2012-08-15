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
    bool inviteUser(QString jid);
    void removeUser(QHBotUser &user);
    void removeUser(QString jid);
    QHBotGroup& addGroup(QString name);
    void removeGroup(QString name);
private slots:
    void addMemberToGroup(QHBotUser &user,QHBotGroup& grupo);
    void delMemberToGroup(QHBotUser &user,QHBotGroup& grupo);
    void addUser(const QString&);
    void changeUser(const QString&);
    void deleteUser(const QString&);
    
};

#endif // QHBOTUSERMANAGER_H

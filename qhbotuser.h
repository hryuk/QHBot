#ifndef QHBOTUSER_H
#define QHBOTUSER_H

#include <QObject>
#include <QXmppRosterIq.h>
#include <QXmppPresence.h>
//#include "qhbotgroup.h"

class QHBotUser : public QObject
{
    Q_OBJECT
public:
    explicit QHBotUser(QXmppRosterIq* Item,QObject *parent = 0);/*
    void addGroup(QString& name);
    void addGroup(QHBotGroup& grupo);
    void addGroups(QList<QString>& toAdd);
    void addGroups(QList<QHBotGroup>& toAdd);
    void delGroup(QString& name);
    void delGroup(QHBotGroup& name);
    void delGroups(QList<QString>& toDel);
    void delGroups(QList<QHBotGroup>& toDel);*/
    const QString& getJID();
    void setName(const QString&);
    const QString& getName();
    const QList<QString>& getGroups();
    QXmppPresence getPresence();
    void setPresence(QXmppPresence& toSet);

    bool isGroupMember(QString& groupName);
    QXmppRosterIq::Item& getRosterItem();
    bool IsAdmin();
private:
    QXmppPresence Presence;
    QXmppRosterIq::Item* userData;
    
signals:
    
public slots:
    
};

#endif // QHBOTUSER_H

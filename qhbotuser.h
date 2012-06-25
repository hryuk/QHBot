#ifndef QHBOTUSER_H
#define QHBOTUSER_H

#include <QObject>
#include <QXmppPresence.h>
#include <QXmppRosterIq.h>

#include "qhbotgroup.h"

class QHBotUser : public QObject
{
    Q_OBJECT
public:
    explicit QHBotUser(QObject *parent = 0);
    explicit QHBotUser(QXmppRosterIq* Item,QObject *parent = 0);

private:
    QXmppPresence Presence;
    QXmppRosterIq::Item* UserData;
    
signals:
    
public slots:  
    void setNick(QString nick);
    void setJID(QString jid);
    void setPresence(QXmppPresence presence);
    QString getNick();
    QString getJID();
    QXmppPresence getPresence();

    /*
    const QString& getJID();
    void setName(const QString&);
    const QString& getName();
    const QList<QString>& getGroups();
    QXmppPresence getPresence();
    void setPresence(QXmppPresence& toSet);

    bool isGroupMember(QString& groupName);
    QXmppRosterIq::Item& getRosterItem();
    bool IsAdmin();
    */
    
};

#endif // QHBOTUSER_H

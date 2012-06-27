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
    //No tiene sentido como slot porque solo recupera un valor
    QXmppPresence getPresence();
    QXmppPresence getPresence(QString resource);

private:
    QXmppPresence Presence;
    QString jid;
    QString nick;
    QMap<QString,QXmppPresence> nodos;
    
signals:
    void nickChange(QString jid,QString newNickName);
    
public slots:  
    void setNick(QString nick);
    void setJID(QString jid);
    void setPresence(QString ResourceName,QXmppPresence Presence);
    QString getNick();
    QString getJID();

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

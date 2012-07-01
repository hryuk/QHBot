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
    QHBotUser(const QXmppRosterIq::Item &item, QObject* parent = 0);
    //No tiene sentido como slot porque solo recupera un valor
    QMap<QString,QXmppPresence> getPresence();
    QXmppPresence getPresence(QString resource);
    QString getLastResourceUsed();
    bool isAvailable();
    bool isAvailable(QString resourceName);
    bool isSnoozing();
    void setSnooze(bool);//Snoozing para los usuarios.

private:
    QString jid;
    QString nick;
    QString lastResourceUsed;
    QMap<QString,QXmppPresence> nodos;
    bool Snooze;
    //QList<QHBotGroup> groups;
    
signals:
    void nickChange(const QString& jid,const QString& newNickName);
    
public slots:
    void setLastResourceUsed(QString resourceName);
    void setNick(QString newNick);
    void setJID(QString jid);
    void update(QXmppRosterIq::Item item);
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

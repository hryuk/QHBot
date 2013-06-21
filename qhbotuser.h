#ifndef QHBOTUSER_H
#define QHBOTUSER_H

#include <QObject>
#include <QXmppPresence.h>
#include <QXmppRosterIq.h>

//#include "qhbotgroup.h"

class QHBotGroup;
class QHBotUserManager;
class QHBotUser : public QObject
{
    Q_OBJECT
public:

    explicit QHBotUser(QObject *parent = 0);
    QHBotUser(const QXmppRosterIq::Item &item, QHBotUserManager& userManager);
    //No tiene sentido como slot porque solo recupera un valor
    QMap<QString,QXmppPresence> getPresence();
    QXmppPresence getPresence(QString resource);
    QString getLastResourceUsed();
    bool isAvailable();
    bool isAvailable(QString resourceName);
    bool isSnoozing();
    void setSnooze(bool);//Snoozing para los usuarios.
    bool isGroupMember(QString groupName);
    void addToGroup(QHBotGroup& grupo);
    void delToGroup(QString grupoName);
    void delToGroup(QHBotGroup& grupo);

private:
    QString jid;
    QString nick;
    QString lastResourceUsed;
    QMap<QString,QXmppPresence> nodos;
    QList<QHBotGroup*> memberGroups;
    bool Snooze;
    
signals:
    void nickChange(const QString& jid,const QString& newNickName);
    void statusChanged(bool snoozing);
    
public slots:
    void setLastResourceUsed(QString resourceName);
    void setNick(QString newNick);
    void setJID(QString jid);
    void update(QXmppRosterIq::Item item);
    void setPresence(QString ResourceName,QXmppPresence Presence);
    QString getNick();
    QString getJID();

private slots:
    
};

#endif // QHBOTUSER_H

#ifndef QHBOTUSERMANAGER_H
#define QHBOTUSERMANAGER_H

#include <QObject>

#include <QXmppRosterManager.h>
#include "qhbotuser.h"
#include "qhbotgroup.h"

class QHBotUserManager : public QObject
{
    Q_OBJECT
public:
    explicit QHBotUserManager(QXmppRosterManager& RosterManager,QObject *parent = 0);
    
signals:
    
public slots:
    void presenceUpdate(const QString& bareJid, const QString& resource);

private:
    QXmppRosterManager* rosterManager;
    QList<QHBotUser> users;
    QList<QHBotGroup> groups;

    
};

#endif // QHBOTUSERMANAGER_H

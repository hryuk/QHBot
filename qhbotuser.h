#ifndef QHBOTUSER_H
#define QHBOTUSER_H

#include <QObject>
#include <QXmppPresence.h>
#include <QXmppRosterIq.h>

#include "qhbotusermanager.h"

class QHBotUser : public QObject
{
    Q_OBJECT

    enum Status{Online,Offline};

public:
    QHBotUser(QString jid);
    friend class QHBotUserManager;

private:
    QString jid;
    QString username;
    QMap<QString,Status> resources;
    void setPresence(QString resource,Status status);
    bool available;
    QString activeResource;
    
signals:
    void presenceChanged(Status);
    
public slots:
    bool isAvailable();
    QString getJID();
    QString getResource();
    //QString getUsername();
};

#endif // QHBOTUSER_H

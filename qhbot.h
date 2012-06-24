#ifndef QHBOT_H
#define QHBOT_H

#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>
#include <QXmppRosterManager.h>

#include "qhbotusermanager.h"

class QHBot : public QXmppClient
{
    Q_OBJECT

public:
    QHBot(QObject *parent = 0);
    ~QHBot();

private:
    QHBotUserManager* UserManager;

public slots:
    /*void messageReceived(const QXmppMessage&);
    void sendMsgBroadcast(const QXmppMessage&);*/

signals:
    /*void needMsgBroadcast(const QXmppMessage&);*/
};




#endif // QHBOT_H

#ifndef QHBOT_H
#define QHBOT_H

#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>
#include <QXmppRosterManager.h>

#include "qhbotusermanager.h"
#include "qhbotcommands.h"

class QHBot : public QXmppClient
{
    Q_OBJECT

public:
    QHBot(QObject *parent = 0);
    ~QHBot();

private:
    QHBotUserManager* UserManager;
    QHBotCommands* Commands;

public slots:
    void messageReceived(const QXmppMessage&);
    void sendMsgBroadcast(const QXmppMessage&);

signals:
    void needMsgBroadcast(const QXmppMessage&);
    void textMsgReceived(const QXmppMessage&);
    void commandReceived(const QXmppMessage&);

};




#endif // QHBOT_H
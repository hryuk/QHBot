#ifndef QHBOT_H
#define QHBOT_H

#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>
#include <QXmppRosterManager.h>
#include <QThread>
#include <QMutex>

#include "qhbotcommands.h"
#include "qhbotusermanager.h"

/* Pequeño trick, clase solo usada para simular un sleep */
class SleepingThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

/* Clase principal, herada de QXmppClient, por lo que encapsula
   la funcionalidad completa de un cliente XMPP */
class QHBot : public QXmppClient
{
    Q_OBJECT

public:
    QHBot(QObject *parent = 0);
    ~QHBot();

private:
    QHBotUserManager* UserManager;
    QHBotCommands* Commands;
    QMutex mutex;
    SleepingThread sleep;

public slots:
    void messageReceived(const QXmppMessage&);
    void sendBroadcast(const QXmppMessage&);
    void sendMessage(QString jid,QString  msg);
    void sendRosterIq(QXmppIq* iq);

signals:
    void requestBroadcast(const QXmppMessage&);
    void textMsgReceived(const QXmppMessage&);
    void commandReceived(const QXmppMessage&);
};







#endif // QHBOT_H

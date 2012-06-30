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

/* Pequeño trick, clase solo usada para simular un sleep*/
class SleepingThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

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
    void sendMsgBroadcast(const QXmppMessage&);
    void sendMsg(QString jid,QString  msg);
    void sendIQ(QXmppIq* iq);

signals:
    void needMsgBroadcast(const QXmppMessage&);
    void textMsgReceived(const QXmppMessage&);
    void commandReceived(const QXmppMessage&);
};







#endif // QHBOT_H

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

/* Peque�o trick, clase solo usada para simular un sleep*/
class SleeperThread : public QThread
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
    SleeperThread sleep;

public slots:
    void messageReceived(const QXmppMessage&);
    void sendMsgBroadcast(const QXmppMessage&);
    void sendIQ(QXmppIq* iq);

signals:
    void needMsgBroadcast(const QXmppMessage&);
    void textMsgReceived(const QXmppMessage&);
    void commandReceived(const QXmppMessage&);

};







#endif // QHBOT_H

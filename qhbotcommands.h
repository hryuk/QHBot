#ifndef QHBOTCOMMANDS_H
#define QHBOTCOMMANDS_H

#include <QObject>
#include <QXmppMessage.h>
#include <QDebug>

#include "qhbotusermanager.h"

class QHBotCommands : public QObject
{
    Q_OBJECT
public:
    explicit QHBotCommands(QHBotUserManager* UserManager,QObject *parent = 0);

private:
    QHBotUserManager* UserManager;
    QStringList commands;
signals:

    
public slots:
    bool isCommand(const QXmppMessage& msg);
    bool runCommand(const QXmppMessage& msg);

private slots:
    void runCmdHello(const QStringList &arg);
    void runCmdInvite(const QStringList &arg);
    // /setNick <jid> <newNick>
    void runCmdSetNick(const QStringList &arg);
    
};

#endif // QHBOTCOMMANDS_H

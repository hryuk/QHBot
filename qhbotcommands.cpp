#include "qhbotcommands.h"

QHBotCommands::QHBotCommands(QHBotUserManager* UserManager, QObject *parent): QObject(parent)
{
    this->UserManager=UserManager;
    this->commands<<"hello"<<"invite";
}

bool QHBotCommands::isCommand(const QXmppMessage &msg)
{
    if(msg.body().startsWith('/')) return true;
    else return false;
}

bool QHBotCommands::runCommand(const QXmppMessage &msg)
{
    QString txtMsg=msg.body();


    if(txtMsg.startsWith("/"+commands[0]))
    {
        this->runCmdHello(msg);
        return true;
    }
    else if(txtMsg.startsWith("/"+commands[1]))
    {
        this->runCmdInvite("/"+commands[2]);
        return true;
    }

    return false;
}

void QHBotCommands::runCmdHello(const QXmppMessage &msg)
{
    //TODO
}

void QHBotCommands::runCmdInvite(const QXmppMessage &msg)
{
    //TODO
}

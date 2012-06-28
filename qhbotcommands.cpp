#include "qhbotcommands.h"

QHBotCommands::QHBotCommands(QHBotUserManager* UserManager, QObject *parent): QObject(parent)
{
    this->UserManager=UserManager;
    this->commands<<"hello"<<"invite"<<"setNick";
}

bool QHBotCommands::isCommand(const QXmppMessage &msg)
{
    if(msg.body().startsWith("/")) return true;
    else return false;
}

bool QHBotCommands::runCommand(const QXmppMessage &msg)
{
    QString txtMsg=msg.body();
    QStringList arg = txtMsg.split(" ");


    int i = 0,index = 0;
    if(txtMsg.startsWith("/"+commands[index = i++]))
    {
        this->runCmdHello(msg);
        return true;
    }
    else if(txtMsg.startsWith("/"+commands[index = i++]))
    {
        this->runCmdInvite("/"+commands[index]);
        return true;
    }
    else if(txtMsg.startsWith("/"+commands[index = i++]))
    {
        arg.removeAt(0);
        this->runCmdSetNick(arg);
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
    //TODO: comprobar jid!!!
    QString body=msg.body();
    body.replace("/invite ","");

    UserManager->inviteUser(body);
}
void QHBotCommands::runCmdSetNick(const QStringList &arg){
    const QString& jid = arg.at(0);
    const QString& newNick = arg.at(1);

    UserManager->getUser(jid)->setNick(newNick);
}

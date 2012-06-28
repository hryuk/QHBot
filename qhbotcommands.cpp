#include "qhbotcommands.h"

QHBotCommands::QHBotCommands(QHBotUserManager* UserManager, QObject *parent): QObject(parent)
{
    this->UserManager=UserManager;
    this->commands<<"hello"<<"invite"<<"setnick";
}

bool QHBotCommands::isCommand(const QXmppMessage &msg)
{
    if(msg.body().startsWith("/")) return true;
    else return false;
}

bool QHBotCommands::runCommand(const QXmppMessage &msg)
{
    qDebug()<<"Run command!!";

    QStringList arg=msg.body().split(" ");
    QString CommandName=arg.at(0);
    arg.removeAt(0);

    int i=0;
    if(CommandName=="/"+commands[i++])
    {
        this->runCmdHello(arg);
        return true;
    }
    else if(CommandName=="/"+commands[i++])
    {
        this->runCmdInvite(arg);
        return true;
    }
    else if(CommandName=="/"+commands[i++])
    {
        this->runCmdSetNick(arg);
        return true;
    }

    return false;
}

void QHBotCommands::runCmdHello(const QStringList &arg)
{
    //TODO
}

void QHBotCommands::runCmdInvite(const QStringList &arg)
{
    QRegExp rx("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}$ ");
    if(!rx.exactMatch(arg.at(0))) return;
    UserManager->inviteUser(arg.at(0));
}
void QHBotCommands::runCmdSetNick(const QStringList &arg)
{
    const QString& jid = arg.at(0);
    const QString& newNick = arg.at(1);

    UserManager->getUser(jid)->setNick(newNick);
}

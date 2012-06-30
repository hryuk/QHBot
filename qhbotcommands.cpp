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
    QString from = msg.from();
    arg.removeAt(0);

    int i=0;
    if(CommandName=="/"+commands[i++])
    {
        this->runCmdHello(arg,from);
        return true;
    }
    else if(CommandName=="/"+commands[i++])
    {
        this->runCmdInvite(arg,from);
        return true;
    }
    else if(CommandName=="/"+commands[i++])
    {
        this->runCmdSetNick(arg,from);
        return true;
    }

    return false;
}

void QHBotCommands::runCmdHello(const QStringList &arg, const QString &from)
{
    //TODO
}

void QHBotCommands::runCmdInvite(const QStringList &arg, const QString &from)
{
    QRegExp rx("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if(!rx.exactMatch(arg.at(0))) return;
    UserManager->inviteUser(arg.at(0));
}
void QHBotCommands::runCmdSetNick(const QStringList &arg, const QString &from)
{
    const QString& jid = arg.at(0);
    const QString& newNick = arg.at(1);

    UserManager->getUser(jid)->setNick(newNick);
    emit messageRequest(from,"H-SEC BOT\n"+jid+" es ahora conocido como: "+newNick);

}

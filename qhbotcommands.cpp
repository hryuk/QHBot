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

void QHBotCommands::runCommand(const QXmppMessage &msg)
{
    qDebug()<<"Run command!!";

    QStringList arg=msg.body().split(" ");
    QString CommandName=arg.at(0);
    QString from = msg.from();
    arg.removeAt(0);

    int i=0;
    if(CommandName=="/"+commands[i++])
    {
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdHello(arg,from);
        return;
    }
    else if(CommandName=="/"+commands[i++])
    {
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdInvite(arg,from);
        return;
    }
    else if(CommandName=="/"+commands[i++])
    {
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdSetNick(arg,from);
        return;
    }

    qWarning()<<"Comando "+CommandName+" no encontrado";

    return;
}

void QHBotCommands::runCmdHello(const QStringList &arg, const QString &from)
{
    emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast","Soy un bot!"));

}

void QHBotCommands::runCmdInvite(const QStringList &arg, const QString &from)
{
    QRegExp rx("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if(!rx.exactMatch(arg.at(0))) return;
    if(UserManager->inviteUser(arg.at(0)))
    {
        qDebug()<<arg.at(0)<<" ha sido invitado";
        emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast","Soy un bot!"));
    }
}
void QHBotCommands::runCmdSetNick(const QStringList &arg, const QString &from)
{
    const QString& jid=arg.at(0);
    const QString& newNick=arg.at(1);

    UserManager->getUser(jid)->setNick(newNick);

    emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",jid+" es ahora conocido como "+newNick));
}

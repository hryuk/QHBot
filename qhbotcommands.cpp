#include "qhbotcommands.h"

QHBotCommands::QHBotCommands(QHBotUserManager* UserManager, QObject *parent): QObject(parent)
{
    this->UserManager=UserManager;
    this->commands<<"invite"<<"help"<<"list";
}

bool QHBotCommands::isCommand(const QXmppMessage &msg)
{
    if(msg.body().startsWith("$") || msg.body().startsWith("/") ) return true;
    else return false;
}

void QHBotCommands::runCommand(const QXmppMessage &msg)
{
    qDebug()<<"Run command!!";

    QStringList arg=msg.body().split(QRegExp("\\s+"));

    QString CommandName = arg.at(0);
    QString from = msg.from().split("/").at(0);
    CommandName.remove(0,1);

    arg.removeAt(0);

    switch(commands.indexOf(CommandName,0))
    {
        case -1://Si no encuentra el comando.
            qWarning()<<"Comando " + CommandName+ " no encontrado";
            break;

        case 0://invite
            if(!admList.contains(from)) return;
            qDebug()<< "Ejecutando commando "+CommandName;
            this->runCmdInvite(arg);
            break;

        case 1://help
            qDebug()<< "Ejecutando commando "+CommandName;
            this->runCmdHelp(from);

        case 2://list
            qDebug()<<"Ejecutando comando "+CommandName;
            this->runCmdList(from);
        break;


    }
}

void QHBotCommands::runCmdInvite(const QStringList &arg)
{
    QRegExp rx("^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}$");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if(arg.length() < 1) return;
    if(!rx.exactMatch(arg.at(0))) return;

    if(UserManager->inviteUser(arg.at(0)))
    {
        qDebug()<<arg.at(0)<<" ha sido invitado";
        emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",arg.at(0)+" ha sido invitado"));
    }
}
void QHBotCommands::runCmdHelp(const QString &from)
{
    QStringList help;
    help<<QString("/list: Lista los usuarios suscritos al bot y su estado\n");
    help<<QString("/help: Muestra este mensaje de ayuda\n");
    if(admList.contains(from))
    {
        help<<QString("/invite <email>: Invita a un nuevo usuario\n");
    }

    emit messageRequest(QXmppMessage("bot@h-sec.org",from,help.join("")));
}

void QHBotCommands::runCmdList(const QString &from)
{
    QStringList UserList;
    foreach(QHBotUser* u,UserManager->getUsers())
    {
        QString jid=u->getJID();
        QStringList jidChunk;
        jidChunk<<jid.split("@").at(0);
        jidChunk<<jid.split("@").at(1).split("."+jid.split(".").last()).at(0);
        jidChunk<<jid.split(".").last();

        QString userString;
        userString+=u->isAvailable()?"[+]":"[-]";
        userString+="["+u->getJID()+"]";

        if(admList.contains(from))
        {
            userString+="     <"+jidChunk[0]+"[at]"+jidChunk[1]+"[dot]"+jidChunk[2]+">";
        }

        UserList.append(userString);
    }

    UserList.sort();

    emit messageRequest(QXmppMessage("",from,"\n"+UserList.join("\n")));
}

void QHBotCommands::setAdmList(QStringList admList)
{
    this->admList=admList;
}

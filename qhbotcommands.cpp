#include "qhbotcommands.h"

QHBotCommands::QHBotCommands(QHBotUserManager* UserManager, QObject *parent): QObject(parent)
{
    this->UserManager=UserManager;
    this->commands<<"hello"<<"invite"<<"setnick"<<"snooze"<<"list";
}

bool QHBotCommands::isCommand(const QXmppMessage &msg)
{
    if(msg.body().startsWith("$") || msg.body().startsWith("/") ) return true;
    else return false;
}

void QHBotCommands::runCommand(const QXmppMessage &msg)
{
    qDebug()<<"Run command!!";

    QStringList arg=msg.body().split(" ");
    QString CommandName = arg.at(0);
    QString from = msg.from();
    //FIXME: FIX PERMISOS
    QString fromEmail = from.split("/").at(0);
    CommandName.remove(0,1);

    arg.removeAt(0);

    switch(commands.indexOf(CommandName,0))
    {
    case -1://Si no encuentra el comando.
        qWarning()<<"Comando " + CommandName+ " No Encontrado";
        break;

    case 0://Si recibe hello
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdHello(arg);
        break;

    case 1://Si recibe invite
        //FIXME: FIX PERMISOS
        if(!admList.contains(fromEmail)) return;
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdInvite(arg);
        break;

    case 2://Si recibe setnick
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdSetNick(arg, fromEmail);
        break;

    case 3:
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdSnoozing(arg,from);
        break;

    case 4:
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdList(arg,from);

    }
}

void QHBotCommands::runCmdHello(const QStringList &arg)
{
    emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast","Soy un bot!"));
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
void QHBotCommands::runCmdSetNick(const QStringList &arg, const QString &from)
{
    if(arg.length() < 2 || UserManager->getUser(arg.at(0)) == NULL) //No esta en la lista? No hacemos nada.
        return;

    QString jid=arg.at(0); //Si el FIX PERMISOS se elimina, esto podría ser const.

    /* FIXME: FIX PERMISOS */
    if(!admList.contains(from)){
        jid = from;
    }
    /* END FIXME */

    const QString& newNick=arg.at(1);


    UserManager->getUser(jid)->setNick(newNick);

    emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",jid+" es ahora conocido como "+newNick));
}

void QHBotCommands::runCmdSnoozing(const QStringList &arg,const QString &from)
{
    if(arg.length() > 0 && (arg.at(0)=="on" || arg.at(0)=="off")){
        UserManager->getUser(from.split("/").at(0))->setSnooze(arg.at(0)=="on");
        emit messageRequest(QXmppMessage("", from, "Modo snooze "+arg.at(0)));
    }
}

void QHBotCommands::runCmdList(const QStringList &arg, const QString &from)
{
    QStringList UserList;
    foreach(QHBotUser* u,UserManager->getUsers())
    {
        UserList.append(QString("["+u->getNick()+"] ("+u->getJID()+")"));
        UserList.last().insert(0,u->isAvailable()?"[+]":"[-]");
    }

    UserList.sort();

    emit messageRequest(QXmppMessage("",from,"\n"+UserList.join("\n")));
}

// FIXME: FIX PERMISOS
void QHBotCommands::setAdmList(QStringList admList)
{
    this->admList = admList;
}

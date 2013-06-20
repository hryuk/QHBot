#include "qhbotcommands.h"

QHBotCommands::QHBotCommands(QHBotUserManager* UserManager, QObject *parent): QObject(parent)
{
    this->UserManager=UserManager;
    this->commands<<"hello"<<"invite"<<"setnick"<<"help"<<"list"<<"setquote"<<"loadquote"<<"busy"<<"back"<<"source"<<"nick";
    this->runCmdLoadQuotes();
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
    QString from = msg.from().split("/").at(0);
    CommandName.remove(0,1);

    arg.removeAt(0);

    switch(commands.indexOf(CommandName,0))
    {
    case -1://Si no encuentra el comando.
        qWarning()<<"Comando " + CommandName+ " No Encontrado";
        break;

    case 0://hello
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdHello();
        break;

    case 1://invite
        if(!admList.contains(from)) return;
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdInvite(arg);
        break;

    case 2://setnick
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdSetNick(arg,from);
        break;

    case 3://help
        qDebug()<< "Ejecutando commando "+CommandName;
        this->runCmdHelp(from);
    break;

    case 4://list
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdList(from);
    break;

    case 5://setquote
        /*
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdSetQuote(arg);
        */
    break;

    case 6://loadquotes
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdLoadQuotes();
    break;

    case 7://busy
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdBusy(from);
    break;

    case 8://back
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdBack(from);
    break;

    case 9://source
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdSource(from);
    break;

    case 10://nick
        qDebug()<<"Ejecutando comando "+CommandName;
        this->runCmdNick(arg,from);
    break;
    }
}

void QHBotCommands::runCmdHello()
{
    if(this->quotes.isEmpty())
    {
        emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast","No tengo frases... Que planeas que diga?"));
    }
    else
    {
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());

        emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",quotes.at((qrand()%quotes.size()))));
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

void QHBotCommands::runCmdNick(const QStringList &arg, const QString &from)
{
    if(arg.length() != 1) return;

    //Si no es un nick válido, no hacemos nada
    QRegExp rx("[a-z0-9_\\-\\[\\]]{2,15}");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if(!rx.exactMatch(arg.at(0))) return;

    QString lastNick=UserManager->getUser(from)->getNick();
    UserManager->getUser(from)->setNick(arg.at(0));

    emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",lastNick+" es ahora conocido como "+arg.at(0)));
}

void QHBotCommands::runCmdSetNick(const QStringList &arg, const QString &from)
{

    if(arg.length() != 2 || UserManager->getUser(arg.at(0))==NULL) return;


    if(!admList.contains(from) && from!=arg.at(0)) return;

    //Si no es un nick válido, no hacemos nada
    QRegExp rx("[a-z0-9_\\-\\[\\]]{2,15}");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    if(!rx.exactMatch(arg.at(1))) return;


    QString lastNick=UserManager->getUser(arg.at(0))->getNick();
    UserManager->getUser(arg.at(0))->setNick(arg.at(1));

    emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",lastNick+" es ahora conocido como "+arg.at(1)));
}

void QHBotCommands::runCmdHelp(const QString &from)
{
    QStringList help;
    help<<QString("\n/hello: Hace que el bot salude\n");
    help<<QString("/help: Muestra este mensaje de ayuda\n");
    help<<QString("/list: Lista los usuarios suscritos al bot y su estado\n");
    help<<QString("/busy: Te pone ausente\n");
    help<<QString("/back: Quita el estado de ausencia\n");
    help<<QString("/source: Muestra donde se aloja el código del bot\n");
    if(admList.contains(from))
    {
        help<<QString("/setnick <email> <nick>: Cambia el nick a un usuario en concreto\n");
        help<<QString("/invite <email>: Invita a un nuevo usuario\n");
        help<<QString("/setquote: \n");
        help<<QString("/loadquote: Carga las frases del archivo quotes.dat\n");
    }

    emit messageRequest(QXmppMessage("bot@h-sec.org",from,help.join("")));
}

void QHBotCommands::runCmdSource(const QString &from)
{
    QString sourceMsg="Código disponible en https://github.com/hzeroo/QHBot";

    emit messageRequest(QXmppMessage("bot@h-sec.org",from,sourceMsg));
}

void QHBotCommands::runCmdBusy(const QString &from)
{
    if(!UserManager->getUser(from)->isSnoozing())
    {
        emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",UserManager->getUser(from)->getNick()+" está ahora ausente"));
        UserManager->getUser(from)->setSnooze(true);
    }
}

void QHBotCommands::runCmdBack(const QString &from)
{
    if(UserManager->getUser(from)->isSnoozing())
    {
        UserManager->getUser(from)->setSnooze(false);
        emit messageRequest(QXmppMessage("bot@h-sec.org","broadcast",UserManager->getUser(from)->getNick()+" ha vuelto"));
    }
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
        UserList.append(QString("["+u->getNick()+"]     <"+jidChunk[0]+"[at]"+jidChunk[1]+"[dot]"+jidChunk[2]+"> "+(u->isSnoozing()?"     (busy)":"")));
        UserList.last().insert(0,u->isAvailable()?"[+]":"[-]");
    }

    UserList.sort();

    emit messageRequest(QXmppMessage("",from,"\n"+UserList.join("\n")));
}

void QHBotCommands::setAdmList(QStringList admList)
{
    this->admList=admList;
}

void QHBotCommands::runCmdLoadQuotes()
{
    QFile file("quotes.dat");
    QString quote;

    this->quotes.clear();

    file.open(QIODevice::ReadWrite | QIODevice::Append);

    QTextStream in_out(&file);

    in_out.seek(0);

    quote = in_out.readLine();

    while(!quote.isNull())
    {
        quotes.append(quote);
        quote = in_out.readLine();
    }

    file.close();
}

void QHBotCommands::runCmdSetQuote(const QStringList &arg) // To Write quotes inside quotes.dat file.
{
    QFile file("quotes.dat");
    QString quote = arg.at(0);

    for(int i = 1; i<arg.size(); i++)
        quote+=arg.at(i)+" ";

    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream out(&file);

    out<<quote<<endl;

    file.close();

    this->runCmdLoadQuotes();
}

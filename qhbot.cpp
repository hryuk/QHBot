#include "qhbot.h"

QHBot::QHBot(QObject *parent): QXmppClient(parent)
{
    connect(this,SIGNAL(messageReceived(const QXmppMessage&)),SLOT(messageReceived(const QXmppMessage&)));
    connect(this,SIGNAL(requestBroadcast(const QXmppMessage&)),SLOT(sendBroadcast(const QXmppMessage&)));

    UserManager=new QHBotUserManager(&this->rosterManager());
    Commands=new QHBotCommands(UserManager);

    connect(Commands,SIGNAL(messageRequest(const QXmppMessage&)),this,SLOT(sendMessage(const QXmppMessage&)));
    connect(this,SIGNAL(commandReceived(const QXmppMessage&)),Commands,SLOT(runCommand(const QXmppMessage&)));

    QXmppVCardIq vCard;
    vCard.setNickName("Claptrap");
    vCard.setEmail("bot@h-sec.org");
    vCard.setFirstName("Claptrap");
    vCard.setLastName("Claptrap");
    vCard.setUrl("http://foro.h-sec.org");
    vCardManager().setClientVCard(vCard);
}

QHBot::~QHBot()
{

}

void QHBot::setAdminList(QStringList admList)
{
    this->Commands->setAdmList(admList);
}

void QHBot::messageReceived(const QXmppMessage& message)
{
    /* TODO: Asegurarse de si esto es necesario */
    /* Eliminamos el /resource del JID */
    QString from=message.from();
    from=from.mid(0,from.indexOf('/'));

    /* Si el mensaje está vacío lo descartamos */
    QString msg = message.body();
    if(msg.isEmpty()) return;

    /* TODO: Manejar los mensajes de error */
    /* Si el mensaje es un mensaje de error lo descartamos */
    if(message.type()!=QXmppMessage::Chat) return;

    /* TODO: Comprobar el grupo, no todos lo usuarios del roster son usuarios autorizados*/
    /* Nos aseguramos de que el mensaje está en la lista de usuarios */
    if(this->rosterManager().getRosterBareJids().contains(from))
    {
        qDebug()<<"Mensaje de: "+from;

        /* Lanzamos signals para ejecutar un comando o difundir el mensaje según corresponda */
        if(Commands->isCommand(message))
        {
            emit commandReceived(message);
        }
        else
        {
            emit requestBroadcast(message);
        }
    }
}

void QHBot::sendMessage(const QXmppMessage &msg)
{
    if(msg.to()=="broadcast")
    {
        qDebug()<<"Es necesario emitir mensaje difusión";
        emit requestBroadcast(msg);
    }
    else
    {
        qDebug()<<"Enviando mensaje";
        sendPacket(QXmppMessage("", msg.to(), "[Claptrap]: "+msg.body()));
    }
}

void QHBot::sendBroadcast(const QXmppMessage &msg)
{
    /* Bloqueamos el mutex para que solo haya un hilo ejecutando esta función */
    QMutexLocker locker(&mutex);

    /* Delay entre mensaje y mensaje */
    sleep.msleep(100);

    /* Obtenemos Nick y Jid del usuario remitente */
    QString JidFrom;
    QString NameFrom;
    if(msg.from()=="bot@h-sec.org")
    {
        JidFrom="bot@h-sec.org";
        NameFrom="[Claptrap]";
    }
    else
    {
        QHBotUser* UserFrom=UserManager->getUser(msg.from().mid(0,msg.from().indexOf('/')));
        JidFrom=UserFrom->getJID();
        NameFrom=UserFrom->getJID();
    }

    /* Recorremos la lista de usuarios*/
    foreach(QHBotUser* UserTo,UserManager->getUsers())
    {
        /* Para reenviar, usuario tiene que estar conectado y no ser el remitente */
        if(UserTo->isAvailable() && UserTo->getJID()!=JidFrom)
        {
            qDebug()<<"Reenviando a "+UserTo->getJID();

            /* Delay entre reenvíos del mismo mensaje */
            sleep.msleep(100);

            /* Reenviamos el mensaje al usuario */
            sendPacket(QXmppMessage("",UserTo->getJID()+"/"+UserTo->getResource(),NameFrom+": "+msg.body()));
        }
    }
}


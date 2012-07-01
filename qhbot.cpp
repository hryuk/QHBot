#include "qhbot.h"

QHBot::QHBot(QObject *parent): QXmppClient(parent)
{
    connect(this,SIGNAL(messageReceived(const QXmppMessage&)),SLOT(messageReceived(const QXmppMessage&)));
    connect(this,SIGNAL(requestBroadcast(const QXmppMessage&)),SLOT(sendBroadcast(const QXmppMessage&)));

    UserManager=new QHBotUserManager(&this->rosterManager());
    Commands=new QHBotCommands(UserManager);

    connect(Commands,SIGNAL(messageRequest(QString,QString)),this,SLOT(sendMessage(QString,QString)));
    connect(this,SIGNAL(commandReceived(const QXmppMessage&)),Commands,SLOT(runCommand(const QXmppMessage&)));

    /*
    connect(UserManager,SIGNAL(requestSendRosterIq(QXmppIq*)),this,SLOT(sendRosterIq(QXmppIq*)));
    */
}

QHBot::~QHBot()
{

}

/*
void QHBot::sendRosterIq(QXmppIq* iq)
{
    iq->setTo(this->configuration().domain());
    printf("\n");
    this->sendPacket(*iq);
    printf("\n");
    delete iq;
}
*/

/* Slot que es llamado cuando se recive un nuevo mensaje */
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

    /* TODO: Comprobar el grupo, no todos lo usuarios del roster son usuarios reales*/
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

/* Envía un mensaje a un único usuario por su JID */
void QHBot::sendMessage(QString jid,QString  msg)
{
    sendPacket(QXmppMessage("",jid,msg,""));
}

/* Envía un mensaje de difusión, que llega a todos los usuarios de la lista */
void QHBot::sendBroadcast(const QXmppMessage &msg)
{
    /* Bloqueamos el mutex para que solo haya un hilo ejecutando esta función */
    QMutexLocker locker(&mutex);

    /* Delay entre mensaje y mensaje */
    sleep.msleep(100);

    /* Obtenemos el usuario remitente */
    QHBotUser* UserFrom = UserManager->getUser(msg.from().mid(0,msg.from().indexOf('/')));

    /* Recorremos la lista de usuarios*/
    foreach(QHBotUser* UserTo,UserManager->getUsers())
    {
        /* Para reenviar, usuario tiene que estar conectado y no ser el remitente */
        if(UserTo->isAvalible() && UserTo->getJID()!=UserFrom->getJID())
        {
            qDebug()<<"Reenviando a "+UserTo->getJID();

            /* Delay entre reenvíos del mismo mensaje */
            sleep.msleep(100);

            /* Reenviamos el mensaje al usuario */
            sendPacket(QXmppMessage("",UserTo->getJID(),UserFrom->getNick()+": "+msg.body()));
        }
    }
}


#include "qhbot.h"

QHBot::QHBot(QObject *parent): QXmppClient(parent)
{
    connect(this,SIGNAL(messageReceived(const QXmppMessage&)),SLOT(messageReceived(const QXmppMessage&)));
    connect(this,SIGNAL(needMsgBroadcast(const QXmppMessage&)),SLOT(sendMsgBroadcast(const QXmppMessage&)));

    UserManager=new QHBotUserManager(&this->rosterManager(),this);
    Commands=new QHBotCommands(UserManager);

    connect(UserManager,SIGNAL(sendRosterIq(QXmppIq*)),this,SLOT(sendIQ(QXmppIq*)));
    connect(this,SIGNAL(commandReceived(const QXmppMessage&)),Commands,SLOT(runCommand(const QXmppMessage&)));
}

QHBot::~QHBot()
{

}

void QHBot::sendIQ(QXmppIq* iq)
{
    iq->setTo(this->configuration().domain());
    printf("\n");
    this->QXmppClient::sendPacket(*iq);
    printf("\n");
    delete iq;
}

void QHBot::messageReceived(const QXmppMessage& message)
{
    QString from=message.from();
    from=from.mid(0,from.indexOf('/'));

    QString msg = message.body();
    if(msg.isEmpty()) return;

    if(message.type()!=QXmppMessage::Chat) return;

    if(this->rosterManager().getRosterBareJids().contains(from))
    {
        //qDebug()<<"msg de: "+from;
        if(Commands->isCommand(message))
        {
            emit commandReceived(message);
        }
        else
        {
            emit needMsgBroadcast(message);
        }
    }
}

void QHBot::sendMsgBroadcast(const QXmppMessage &msg)
{
    QMutexLocker locker(&mutex);

    sleep.msleep(100);
    QString jidFrom=msg.from().mid(0,msg.from().indexOf('/'));
    QHBotUser* userFrom = UserManager->getUser(jidFrom);
    foreach(QHBotUser* user,UserManager->getUsers())
    {
        if(user->isAvalible())
        {
            if(user->getJID()!=jidFrom)
            {
                qDebug()<<"Reenviando a "+user->getJID();
                sleep.msleep(100);
                //this->QXmppClient::sendPacket(QXmppMessage("",user->getJID()+(user->isAvalible(user->getLastResourceUsed())?user->getLastResourceUsed():""),jidFrom.mid(0,jidFrom.indexOf("@"))+": "+msg.body()));
                this->QXmppClient::sendPacket(QXmppMessage("",user->getJID()+(user->isAvalible(user->getLastResourceUsed())?user->getLastResourceUsed():""),userFrom->getNick()+": "+msg.body()));
            }
        }

    }
}


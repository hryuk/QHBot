#include "qhbot.h"

QHBot::QHBot(QObject *parent): QXmppClient(parent)
{
    connect(this,SIGNAL(messageReceived(const QXmppMessage&)),SLOT(messageReceived(const QXmppMessage&)));
    connect(this,SIGNAL(needMsgBroadcast(const QXmppMessage&)),SLOT(sendMsgBroadcast(const QXmppMessage&)));

    UserManager=new QHBotUserManager(&this->rosterManager());
    Commands=new QHBotCommands(UserManager);
    connect(UserManager,SIGNAL(QHBotUserManager::sendRosterIq(QXmppRosterIq* iq)),this,SLOT(sendPacket(QXmppPacket*)));

    connect(this,SIGNAL(commandReceived(QXmppMessage&)),Commands,SLOT(runCommand(QXmppMessage&)));
}

QHBot::~QHBot()
{

}
void QHBot::sendPacket(QXmppPacket* paquete){
    this->QXmppClient::sendPacket(*paquete);
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
    QString jidFrom=msg.from().mid(0,msg.from().indexOf('/'));
    foreach(QHBotUser* user,UserManager->getUsers())
    {
        if(user->getJID()!=jidFrom)
        {
            qDebug()<<"Reenviando a "+user->getJID();
            QString txtMsg=msg.body();
            QString jidTo=user->getJID();
            SleeperThread sleep;
            sleep.msleep(100);
            this->QXmppClient::sendPacket(QXmppMessage("",jidTo,jidFrom.mid(0,jidFrom.indexOf("@"))+": "+msg.body()));
 //           this->sendMessage(user->getJID(),jidFrom+": "+msg.body());
        }
    }
}


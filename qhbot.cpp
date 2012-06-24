#include "qhbot.h"

QHBot::QHBot(QObject *parent): QXmppClient(parent)
{
    connect(this,SIGNAL(messageReceived(const QXmppMessage&)),SLOT(messageReceived(const QXmppMessage&)));
    connect(this,SIGNAL(needMsgBroadcast(const QXmppMessage&)),SLOT(sendMsgBroadcast(const QXmppMessage&)));

    UserManager=new QHBotUserManager(&this->rosterManager());
    Commands=new QHBotCommands(UserManager);
}

QHBot::~QHBot()
{

}


void QHBot::messageReceived(const QXmppMessage& message)
{
    QString from=message.from();
    from=from.mid(0,from.indexOf('/'));

    QString msg = message.body();
    if(msg.isEmpty()) return;

    if(this->rosterManager().getRosterBareJids().contains(from))
    {
        if(Commands->isCommand(msg))
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

    foreach(QString u,this->rosterManager().getRosterBareJids())
    {
        if(u!=msg.from().mid(0,msg.from().indexOf('/')))
        {
            qDebug()<<"Reenviando a "+u;
            this->sendMessage(u,msg.body());
        }
    }
}


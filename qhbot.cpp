#include "qhbot.h"

QHBot::QHBot(QObject *parent): QXmppClient(parent)
{
    connect(this,SIGNAL(messageReceived(const QXmppMessage&)),SLOT(messageReceived(const QXmppMessage&)));
}

QHBot::~QHBot()
{

}

void QHBot::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg = message.body();

    sendPacket(QXmppMessage("", from,msg));
}

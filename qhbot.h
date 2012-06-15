#ifndef QHBOT_H
#define QHBOT_H

#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>

class QHBot : public QXmppClient
{
    Q_OBJECT

public:
    QHBot(QObject *parent = 0);
    ~QHBot();

private:

public slots:
    void messageReceived(const QXmppMessage&);
};




#endif // QHBOT_H

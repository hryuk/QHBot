#ifndef QHBOTUSER_H
#define QHBOTUSER_H

#include <QObject>
#include <QXmppPresence.h>

class QHBotUser : public QObject
{
    Q_OBJECT
public:
    explicit QHBotUser(QObject *parent = 0);

private:
    QString nick;
    QString jid;
    QXmppPresence presence;
    
signals:
    
public slots:
    void setNick(QString nick);
    void setJID(QString jid);
    void setPresence(QXmppPresence presence);
    QString getNick();
    QString getJID();
    QXmppPresence getPresence();
};

#endif // QHBOTUSER_H

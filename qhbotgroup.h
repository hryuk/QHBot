#ifndef QHBOTGROUP_H
#define QHBOTGROUP_H

#include <QObject>

#include "qhbotuser.h"

class QHBotUser;

class QHBotGroup : public QObject
{
    Q_OBJECT
public:
    explicit QHBotGroup(QString& name,QObject *parent = 0);
    QString getName();
    QHBotUser* getMember(QString& jid);
    bool isMember(QHBotUser &user);

private:
	QString name;
    QList<int> privs;
    QList<QHBotUser*> members;
    
public slots:
    void grantPrivilege(int priv);
    void revokePrivilege(int priv);
    void addMember(QHBotUser &user);
    void removeMember(QHBotUser &user);
    void removeMember(QString jid_or_nick);
signals:
    void memberAdded(QHBotUser &user,QHBotGroup& grupo);
    void memberDeleted(QHBotUser &user,QHBotGroup& grupo);
};

#endif // QHBOTGROUP_H

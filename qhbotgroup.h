#ifndef QHBOTGROUP_H
#define QHBOTGROUP_H

#include <QObject>

#include "qhbotuser.h"

class QHBotGroup : public QObject
{
    Q_OBJECT
public:
    explicit QHBotGroup(QObject *parent = 0);

private:
    QList<int> privs;
    QList<QHBotUser> members;
    
signals:
    
public slots:
    void grantPrivilege(int priv);
    void revokePrivilege(int priv);
    void addMember(QHBotUser &user);
    void addMember(QString jid);
    void removeMember(QHBotUser &user);
    void removeMember(QString jid_or_nick);
};

#endif // QHBOTGROUP_H

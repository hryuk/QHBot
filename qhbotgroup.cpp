#include "qhbotgroup.h"
#include "qhbotuser.h"

QHBotGroup::QHBotGroup(QString &name, QObject *parent) :
    QObject(parent)
{
}

void QHBotGroup::removeMember(QHBotUser &user)
{
}

void QHBotGroup::removeMember(QString jid_or_nick)
{
}

void QHBotGroup::addMember(QHBotUser &user)
{
}

void QHBotGroup::addMember(QString jid)
{
}

void QHBotGroup::grantPrivilege(int priv)
{
}

void QHBotGroup::revokePrivilege(int priv)
{
}

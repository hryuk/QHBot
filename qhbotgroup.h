#ifndef QHBOTGROUP_H
#define QHBOTGROUP_H

#include <QObject>
#include "qhbotuser.h"

//class QHBotUser;
class QHBotGroup : public QObject
{
    Q_OBJECT
public:
    explicit QHBotGroup(QString& name,QObject *parent = 0);
    void addMember(QHBotUser& user);
    void delMember(QHBotUser& user);
private:
    QString name;
    QList<QHBotUser> member;
signals:
    
public slots:
    
};

#endif // QHBOTGROUP_H

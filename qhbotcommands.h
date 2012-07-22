#ifndef QHBOTCOMMANDS_H
#define QHBOTCOMMANDS_H

#include <QObject>
#include <QXmppMessage.h>
#include <QDebug>

#include "qhbotusermanager.h"

class QHBotCommands : public QObject
{
    Q_OBJECT
public:
    explicit QHBotCommands(QHBotUserManager* UserManager,QObject *parent = 0);

private:
    QHBotUserManager* UserManager;
    QStringList commands;
    QStringList admList;
signals:
    /**
      \brief Esta señal es emitida siempre que un comando necesite enviar un mensaje de
      texto a un usuario. Si Broadcast es
      **/
    void messageRequest(const QXmppMessage& msg);
    
public slots:
    /**
      \brief Determina si un mensaje contiene un comando ejecutable por el bot.

      Retorna true si el mensaje contiene un comando ejecutable por el bot, false en caso contrario.
      **/
    bool isCommand(const QXmppMessage& msg);

    /**
      \brief Ejecuta el comando contenido en el mensaje msg. Responde a la señal QHBot::commandReceived().
      **/
    void runCommand(const QXmppMessage& msg);

    void setAdmList(QStringList admList);

private slots:
    void runCmdHello(const QStringList &arg);
    void runCmdInvite(const QStringList &arg);
    // /setNick <jid> <newNick>
    void runCmdSetNick(const QStringList &arg, const QString &from);
    void runCmdSnoozing(const QStringList &arg, const QString &from);
    void runCmdList(const QStringList &arg,const QString &from);
    
};

#endif // QHBOTCOMMANDS_H

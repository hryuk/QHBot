#ifndef QHBOT_H
#define QHBOT_H

#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>
#include <QXmppRosterManager.h>
#include <QThread>
#include <QMutex>
#include <QXmppVCardManager.h>
#include <QXmppVCardIq.h>
#include <QFile>

#include "qhbotcommands.h"
#include "qhbotusermanager.h"

/**
  \brief Pequeño trick, clase solo usada para simular un sleep.
  El propósito de esta clase es proporcionar una línea de código la cual
  haya que esperar a que termine, sirviendo así de sleep.
  **/
class SleepingThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

/**
  \brief Clase principal. Esta clase se expone a los mensajes entrantes del servidor XMPP
  al que se conecta y se encarga de procesarlos. Hereda de QXmppClient, por lo que encapsula
   la funcionalidad completa de un cliente XMPP.
  **/
class QHBot : public QXmppClient
{
    Q_OBJECT

public:
    QHBot(QObject *parent = 0);
    ~QHBot();

private:
    QHBotUserManager* UserManager;
    QHBotCommands* Commands;
    QMutex mutex;
    SleepingThread sleep;

public slots:
    /**
      \brief Este método es llamado cada vez que se recibe un mensaje del servidor. Determina si
      un mensaje es un mensaje de texto o un comando y lo trata como tal.

      Este método emite dos señales diferentes, dependiendo de el propósito de el mensaje recibido.
      Se emitiran las señales QHBot::textMsgReceived(const QXmppMessage&) y
      QHBot::commandReceived(const QXmppMessage&) para mensajes de texto y comandos respectivamente.
      **/
    void messageReceived(const QXmppMessage&);

    /**
      \brief Envía un mensaje de difusión, que llega a todos los usuarios de la lista en QHBotUserManager,
      excluyendo al remitente. Responde a la señal QHBot::requestBroadcast(const QXmppMessage&).
      **/
    void sendBroadcast(const QXmppMessage&);

    /**
      \brief Envía un mensaje a un único usuario por su jid o emite una señal de broadcast
      si el campo QXmppMessage.To()="broadcast"
      QHBotCommands::messageRequest(const QXmppMessage &msg).
      **/
    void sendMessage(const QXmppMessage &msg);

    //FIXME: FIX PERMISOS
    void setAdminList(QStringList admList);

    //void sendRosterIq(QXmppIq* iq);

signals:
    /**
      \brief Esta señal es emitida cada vez que un mensaje recibido necesita ser difundido a toda
      la lista de usuarios.
      **/
    void requestBroadcast(const QXmppMessage&);

    /**
      \brief Esta señal es emitida cada vez que un mensaje recibido es identificado como un comando
      reconocido por el bot que necesita ser ejecutado.
      **/
    void commandReceived(const QXmppMessage&);
};







#endif // QHBOT_H

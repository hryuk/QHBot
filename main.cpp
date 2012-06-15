#include <QtCore/QCoreApplication>
#include <QXmppClient.h>
#include <QXmppLogger.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::StdoutLogging);

    QXmppClient client;
    client.connectToServer("qhsecbot@gmail.com","****");

    return a.exec();
}

#include <QtCore/QCoreApplication>
#include <QXmppClient.h>
#include <QXmppLogger.h>

#include "qhbot.h"

void mMsgOut(QtMsgType type,const char* msg)
{
    switch (type)
    {
        case QtDebugMsg:
            fprintf(stdout,"Debug: %s\n",msg);
            break;
        case QtWarningMsg:
            fprintf(stdout,"Warning: %s\n",msg);
            break;
        case QtCriticalMsg:
            fprintf(stdout,"Critical: %s\n",msg);
            break;
        case QtFatalMsg:
            fprintf(stdout,"Fatal: %s\n",msg);
            abort();
    }
}

int main(int argc,char* argv[])
{
    QCoreApplication a(argc, argv);

    qInstallMsgHandler(mMsgOut);

    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::StdoutLogging);

    QHBot bot;
    bot.connectToServer("qhsecbot@gmail.com","hsecbot1234");
    //bot.connectToServer("admin@arkangelhack.es","admin");
    //bot.configuration().setStreamSecurityMode(QXmppConfiguration::TLSDisabled);

    return a.exec();
}



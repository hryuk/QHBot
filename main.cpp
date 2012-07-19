#include <QtCore/QCoreApplication>
#include <QXmppClient.h>
#include <QXmppLogger.h>
#include <QSettings>

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
    QCoreApplication a(argc,argv);
    QCoreApplication::setOrganizationName("H-Sec");
    QCoreApplication::setOrganizationDomain("H-Sec.org");
    QCoreApplication::setApplicationName("QHBot");

    qInstallMsgHandler(mMsgOut);

    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::StdoutLogging);

    QHBot bot;
    QXmppConfiguration config;

    QSettings settings("QHBot.ini",QSettings::IniFormat);
    settings.beginGroup("Connection");
    config.setHost(settings.value("Host").toString());
    config.setDomain(settings.value("Domain").toString());
    config.setUser(settings.value("User").toString());
    config.setPassword(settings.value("Password").toString());
    config.setPort(settings.value("Port").toInt());
    //settings.endGroup(); FIXME: FIX PERMISOS

    bot.connectToServer(config);

    /* FIXME: FIX PERMISOS */
    qDebug()<<"AdmList contiene: "<<settings.value("Admlist").toString();
    QStringList admins(settings.value("Admlist").toString().split(" "));
    bot.setAdminList(admins);
    settings.endGroup();
    /* FIXME: FIX PERMISOS */
    return a.exec();
}



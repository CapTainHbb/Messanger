#include <XmppServer.hpp>


XmppServer::XmppServer(const QString& domain, QObject *parent)
: QXmppServer(parent)
{

    logger.setLoggingType(QXmppLogger::StdoutLogging);
    auto roster_handler_extension = new XmppServerExtensionRosterHandler();
    addExtension(roster_handler_extension);
    setDomain(domain);
    setLogger(&logger);
    setPasswordChecker(&checker);
    listenForClients();
    listenForServers();
}


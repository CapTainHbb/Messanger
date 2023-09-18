#include <XmppClient.hpp>

XmppClient::XmppClient(QObject *parent) :
        QXmppClient(parent),
        roster_manager(findExtension<QXmppRosterManager>())
{
    logger()->setLoggingType(QXmppLogger::StdoutLogging);
    connect(this, &QXmppClient::connected, this, &XmppClient::on_connected_to_server);
    connect(this, &QXmppClient::disconnected, this, &XmppClient::on_disconnected_from_server);
    connect(this, &QXmppClient::error, this, &XmppClient::on_error_connection_to_server);
    connect(roster_manager, &QXmppRosterManager::itemAdded,
            this, &XmppClient::on_item_added);
}

XmppClient::~XmppClient()
{

}

void XmppClient::on_request_to_connect_server(const QString& username,
                                  const QString& password,
                                  const QString& domain)
{
    QString jid{ username + "@" + domain };
    try {
        connectToServer(jid, password);
        emit connection_result(State::ConnectingState);
    }
    catch (...) {
        emit connection_result(State::DisconnectedState);
    }
}

void XmppClient::on_connected_to_server()
{
    emit connection_result(State::ConnectedState);
}

void XmppClient::on_disconnected_from_server()
{
    emit connection_result(State::DisconnectedState);
}

void XmppClient::on_error_connection_to_server(Error error)
{
    emit connection_result(QXmppClient::State::DisconnectedState);
}

void XmppClient::on_item_added(const QString &bareJid)
{
    qDebug("on_item_added: %s", qPrintable(bareJid));
}

void XmppClient::on_request_add_contact(const QString& contact_jid)
{
    qDebug("on_request_add_contact: %s", qPrintable(contact_jid));
    roster_manager->addItem(contact_jid);
}

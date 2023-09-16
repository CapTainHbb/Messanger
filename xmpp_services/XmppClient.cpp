#include <XmppClient.hpp>

XmppClient::XmppClient()
{
    client.logger()->setLoggingType(QXmppLogger::StdoutLogging);
    connect(&client, &QXmppClient::connected, this, &XmppClient::on_connected_to_server);
    connect(&client, &QXmppClient::disconnected, this, &XmppClient::on_disconnected_from_server);
    connect(&client, &QXmppClient::error, this, &XmppClient::on_error_connection_to_server);
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
        client.connectToServer(jid, password);
        emit connection_result(QXmppClient::State::ConnectingState);
    }
    catch (...) {
        emit connection_result(QXmppClient::State::DisconnectedState);

    }
}


void XmppClient::on_connected_to_server()
{
    emit connection_result(QXmppClient::State::ConnectedState);
}

void XmppClient::on_disconnected_from_server()
{
    emit connection_result(QXmppClient::State::DisconnectedState);
}

void XmppClient::on_error_connection_to_server(QXmppClient::Error error)
{
    emit connection_result(QXmppClient::State::DisconnectedState);
}

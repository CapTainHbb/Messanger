#pragma once

#include <QObject>
#include <QXmppQt6/QXmppClient.h>
#include <QXmppQt6/QXmppLogger.h>
#include <QXmppQt6/QXmppMessage.h>

#include <iostream>
#include <stdexcept>

class XmppClient : public QObject
{
    Q_OBJECT

public:
    XmppClient();
    ~XmppClient();

signals:
    void connection_result(QXmppClient::State status);

public slots:
    void on_request_to_connect_server(const QString& username,
                                  const QString& password,
                                  const QString& domain);

    void on_connected_to_server();
    void on_disconnected_from_server();
    void on_error_connection_to_server(QXmppClient::Error error);

private:
    QXmppClient client;
};

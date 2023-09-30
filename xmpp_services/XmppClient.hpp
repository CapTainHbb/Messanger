#pragma once

#include <QObject>
#include <QXmppQt6/QXmppClient.h>
#include <QXmppQt6/QXmppLogger.h>
#include <QXmppQt6/QXmppMessage.h>
#include <QXmppQt6/QXmppRosterManager.h>
#include <QXmppQt6/QXmppTask.h>

#include <iostream>
#include <stdexcept>

class QXmppRosterManager;

class XmppClient : public QXmppClient
{
    Q_OBJECT

public:
    XmppClient(QObject *parent = nullptr);
    ~XmppClient();

    QXmppRosterManager *roster_manager;

signals:
    void connection_result(QXmppClient::State status);
    void add_received_contact(const QString& contact_jid);

public slots:
    void on_request_to_connect_server(const QString& username,
                                  const QString& password,
                                  const QString& domain);

    void on_connected_to_server();
    void on_disconnected_from_server();
    void on_error_connection_to_server(QXmppClient::Error error);

    void on_roster_received();

    void on_item_added(const QString &bareJid);

    void on_request_add_contact(const QString& contact_jid);

};

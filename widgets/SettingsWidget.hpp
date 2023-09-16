#pragma once
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

#include <XmppClient.hpp>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget() = default;

    void connect_signals_to_slots();

    QFormLayout *layout{ nullptr };
    void init_layout();

    QLineEdit *username_text_input{nullptr };
    void init_username_widget();

    QLineEdit *password_text_input{nullptr };
    void init_password_widget();

    QLineEdit *domain_name_text_input{nullptr };
    void init_domain_name_widget();

    QPushButton *connect_to_server_button{ nullptr };
    void init_connect_to_server_widget();


    QLabel *connection_result_label{ nullptr };
    void init_connection_result_widget();

    QXmppClient::State get_last_connection_result() const;

signals:
    void request_to_connect_server(const QString& username, const QString& password, const QString& domain);

public slots:
    void on_click_connect_to_server_button();
    void on_connection_result_received(QXmppClient::State status);

private:
    QXmppClient::State last_connection_result{ QXmppClient::State::DisconnectedState };

    XmppClient xmpp_client{ };
};


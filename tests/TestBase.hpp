#pragma once

#include <XmppServer.hpp>
#include <QTest>
#include <QWidget>
#include <QTimer>
#include <QProcess>
#include <QSignalSpy>
#include <mainwindow.h>
#include <iostream>
#include <chrono>
#include <thread>

#define PATH_TO_XMPP_SERVER_APP "../../xmpp_services/XmppServer"

#define XMPP_TEST_CLIENT_JID        "captainhb@127.0.0.1"
#define XMPP_TEST_CLIENT_USERNAME   "captainhb"
#define XMPP_TEST_CLIENT_PASSWORD   "captainhb"
#define XMPP_SERVER_ADDRESS         "127.0.0.1"

class TestBase : public QObject
{
    Q_OBJECT

protected:
    MainWindow main_window;

    GeneralModel *general_model{ nullptr };

    ContactListWidget *get_contact_list_wiget() const;
    AddContactWidget *get_add_contact_widget() const;
    ChatListWidget *get_chat_list_widget() const;
    LeftDrawer *get_left_drawer_widget() const;
    ActiveChat *get_active_chat_widget() const;
    MiddleStack *get_middle_stack_widget() const;
    SettingsWidget *get_settings_widget() const;
    XmppClient *get_xmpp_client();

    void add_contact_to_model(const Contact& contact) const;
    Contact get_contact_from_model(const Contact& contact) const;

    GeneralModel *get_general_model();
    void set_general_model(GeneralModel *model);

    XmppServer server{ "127.0.0.1" };
    XmppClient xmpp_test_client;

    QList<Contact> test_contacts{ };
    void create_test_contacts();

public:
    TestBase(/* args */);
    ~TestBase();
};


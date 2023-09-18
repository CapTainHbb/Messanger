#pragma once

#include <QTest>
#include <QWidget>
#include <QTimer>
#include <mainwindow.h>
#include <iostream>
#include <chrono>
#include <thread>


class TestBase : public QObject
{
    Q_OBJECT
private:
    /* data */

protected:
    MainWindow main_window;
    QList<Contact> test_contacts;
    GeneralModel *general_model{ nullptr };

    ContactListWidget *get_contact_list_wiget() const;
    AddContactWidget *get_add_contact_widget() const;
    ChatListWidget *get_chat_list_widget() const;
    LeftDrawer *get_left_drawer_widget() const;
    ActiveChat *get_active_chat_widget() const;
    MiddleStack *get_middle_stack_widget() const;
    SettingsWidget *get_settings_widget() const;

    void create_test_contacts();
    void create_test_chats();

    void add_contact(QString contact_name);
    Contact get_contact(QString contact_name);

    GeneralModel *get_general_model();
    void set_general_model(GeneralModel *model);

    void connect_to_server(const QString& username,
                           const QString& password,
                           const QString& domain_name);

public:
    TestBase(/* args */);
    ~TestBase();
};


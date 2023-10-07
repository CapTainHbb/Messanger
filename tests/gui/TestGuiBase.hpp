#pragma once

#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

#include <TestBase.hpp>

class TestGuiBase : public TestBase
{
    Q_OBJECT;

protected:
    void double_click_on_contact(const Contact& contact);

    void select_chat(const Contact& contact);
   
    void right_click_on_chat(const Contact& contact);
    void left_click_on_delete_chat();

    void add_contact_from_gui(const Contact& contact);

    void fill_text_input(const QString& text, QWidget* widget);

    void left_click_on_widget(QWidget* widget);

    void connect_to_server_from_gui(const QString& username,
                                    const QString& password,
                                    const QString& domain_name,
                                    QXmppClient::State desired_state = QXmppClient::State::ConnectedState);

    void create_test_contacts_from_gui();

    void create_test_chats_from_gui(const QString& pre_text = "hi");

protected slots:
    virtual void initTestCase() = 0;
    
};

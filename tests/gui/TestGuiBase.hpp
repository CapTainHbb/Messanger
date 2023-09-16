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

    void fill_text_input(const QString& text, QWidget* widget);

    ContactListWidget *get_contact_list_wiget() const;
    ChatListWidget *get_chat_list_widget() const;
    LeftDrawer *get_left_drawer_widget() const;
    ActiveChat *get_active_chat_widget() const;
    MiddleStack *get_middle_stack_widget() const;
    SettingsWidget *get_settings_widget() const;

protected slots:
    virtual void initTestCase() = 0;
    
};

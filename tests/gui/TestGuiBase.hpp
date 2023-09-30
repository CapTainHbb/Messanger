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

    void add_contact_from_gui(const QString& jid);

    void fill_text_input(const QString& text, QWidget* widget);

    void left_click_on_widget(QWidget* widget);

protected slots:
    virtual void initTestCase() = 0;
    
};

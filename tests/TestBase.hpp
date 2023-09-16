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

    void create_test_contacts();
    void create_test_chats();

    void add_contact(QString contact_name);
    Contact get_contact(QString contact_name);

    GeneralModel *get_general_model();
    void set_general_model(GeneralModel *model);

public:
    TestBase(/* args */);
    ~TestBase();
};


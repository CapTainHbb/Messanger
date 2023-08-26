#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

class TestGui : public QObject
{
    Q_OBJECT;

    inline void create_send_message_row(QString chat_name, QString messages_text);

    void select_chat_by_chat_name(QString chat_name);

private slots:
    void initTestCase();

    void empty_active_chat();

    void create_new_chat_data();
    void create_new_chat();

    void select_chat_data();
    void select_chat();

    void check_send_message_data();
    void check_send_message();

    void check_chat_messages_uniqueness_data();
    void check_chat_messages_uniqueness();

private:
    MainWindow main_window;
    QStringList chat_names;
};

void TestGui::initTestCase()
{
    main_window.init_widgets();

    chat_names.append("1");
    chat_names.append("2");
}


void TestGui::empty_active_chat()
{
    QVERIFY(main_window.active_chat_widget->send_message_textbox->isHidden());
    QVERIFY(main_window.active_chat_widget->send_message_pushbutton->isHidden());
}

void TestGui::create_new_chat_data()
{
    QTest::addColumn<QTestEventList>("click_add_new_chat_button");
    QTest::addColumn<int>("number_of_all_chats");
    QTest::addColumn<int>("number_of_messages_in_active_chat");
    QTest::addColumn<QString>("active_chat_name");

    QTestEventList click_new_chat;
    click_new_chat.addMouseClick(Qt::MouseButton::LeftButton);
    QTest::newRow("first new chat") << click_new_chat << 1 << 0 << "1";
    QTest::newRow("second new chat") << click_new_chat << 2 << 0 << "2";
}

void TestGui::create_new_chat()
{
    QFETCH(QTestEventList, click_add_new_chat_button);
    QFETCH(int, number_of_all_chats);
    QFETCH(int, number_of_messages_in_active_chat);
    QFETCH(QString, active_chat_name);

    click_add_new_chat_button.simulate(main_window.left_drawer_widget->new_chat_button);

    QCOMPARE(main_window.left_drawer_widget->get_number_of_all_chats(), number_of_all_chats);
    QCOMPARE(main_window.active_chat_widget->get_number_of_messages_in_active_chat() , number_of_messages_in_active_chat);
    QCOMPARE(main_window.active_chat_widget->get_active_chat_name(), active_chat_name);

    QVERIFY(main_window.active_chat_widget->send_message_textbox->isHidden() != true);
    QVERIFY(main_window.active_chat_widget->send_message_pushbutton->isHidden() != true);
}


void TestGui::select_chat_data()
{
    QTest::addColumn<QString>("selected_chat_name");

    QTest::newRow("select_first_chat") << "1";
    QTest::newRow("select_second_chat") << "2";
}

void TestGui::select_chat()
{
    QFETCH(QString, selected_chat_name);

    select_chat_by_chat_name(selected_chat_name);

    QCOMPARE(main_window.active_chat_widget->get_active_chat_name(), selected_chat_name);
}


void TestGui::select_chat_by_chat_name(QString chat_name)
{
    auto chat_item{ main_window.left_drawer_widget->find_chat_item(chat_name) };
    auto rect{ main_window.left_drawer_widget->get_chat_item_rect(chat_item) };

    QTest::mouseClick(main_window.left_drawer_widget->list_of_chats->viewport(), Qt::LeftButton, 0, rect.center());
}


void TestGui::check_send_message_data()
{
    QTest::addColumn<QString>("chat_name");
    QTest::addColumn<QTestEventList>("type_message");
    QTest::addColumn<QTestEventList>("click_on_send_message");
    QTest::addColumn<QString>("message_text");
    QTest::addColumn<int>("number_of_message_in_active_chat");
    
    create_send_message_row(chat_names.at(0), "hi bob!");
    create_send_message_row(chat_names.at(0), "im alice!");

    create_send_message_row(chat_names.at(1), "hi alice!");
    create_send_message_row(chat_names.at(1), "im bob!");
}

inline void TestGui::create_send_message_row(QString chat_name, QString message_text)
{
    static QString previous_chat_name{ chat_name };
    static int number_of_messages_in_chat{ 0 };
    
    QTestEventList type_message;
    type_message.addKeyClicks(message_text);

    QTestEventList click_on_send_message;
    click_on_send_message.addMouseClick(Qt::MouseButton::LeftButton);

    if(chat_name == previous_chat_name)
    {
        number_of_messages_in_chat++;
    }
    else
    {
        previous_chat_name = chat_name;
        number_of_messages_in_chat = 1;
    }
    
    QString row_name{ chat_name + "_" + message_text };
    QTest::newRow(row_name.toStdString().c_str()) << chat_name << type_message << click_on_send_message << message_text  << number_of_messages_in_chat;
}

void TestGui::check_send_message()
{
    QFETCH(QString, chat_name);
    QFETCH(QTestEventList, type_message);
    QFETCH(QTestEventList, click_on_send_message);
    QFETCH(QString, message_text);
    QFETCH(int, number_of_message_in_active_chat);

    select_chat_by_chat_name(chat_name);
    type_message.simulate(main_window.active_chat_widget->send_message_textbox);
    click_on_send_message.simulate(main_window.active_chat_widget->send_message_pushbutton);

    QCOMPARE(main_window.active_chat_widget->get_number_of_messages_in_active_chat(), number_of_message_in_active_chat);
    QCOMPARE(main_window.active_chat_widget->get_last_message_on_active_chat(), message_text);
}


void TestGui::check_chat_messages_uniqueness_data()
{
    QTest::addColumn<QString>("first_chat_name");
    QTest::addColumn<QString>("second_chat_name");
    QTest::addColumn<int>("number_of_messages_to_compare");

    QTest::newRow("first_row") << chat_names.at(0) << chat_names.at(1) << 2;
}

void TestGui::check_chat_messages_uniqueness()
{
    QFETCH(QString, first_chat_name);
    QFETCH(QString, second_chat_name);
    QFETCH(int, number_of_messages_to_compare);

    select_chat_by_chat_name(first_chat_name);
    auto first_chat_messages_text = main_window.active_chat_widget->get_active_chat_messages_text();

    select_chat_by_chat_name(second_chat_name);
    auto second_chat_messages_text = main_window.active_chat_widget->get_active_chat_messages_text();

    for(size_t i = 0; i < number_of_messages_to_compare; i++)
    {
        QVERIFY(first_chat_messages_text.at(i) != second_chat_messages_text.at(i));
    }

}


QTEST_MAIN(TestGui)
#include "testgui.moc"

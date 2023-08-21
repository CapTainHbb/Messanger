#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

class TestGui : public QObject
{
    Q_OBJECT;

    void send_message();
    void create_send_message_data();

private slots:
    void initTestCase();

    void create_new_chat_data();
    void create_new_chat();

    void select_chat_data();
    void select_chat();

    void check_send_message_data();
    void check_send_message();

private:
    MainWindow main_window;
};

void TestGui::initTestCase()
{
    main_window.init_widgets();
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
}


void TestGui::select_chat_data()
{
    QTest::addColumn<QString>("selected_chat_name");

    QTest::newRow("select_first_chat") << "1";
}

void TestGui::select_chat()
{
    QFETCH(QString, selected_chat_name);

    auto found_items{ main_window.left_drawer_widget->list_of_chats->findItems(selected_chat_name, Qt::MatchExactly) };
    QVERIFY(found_items.count() != 0);

    auto found_item{ found_items.at(0) };
    auto rect{ main_window.left_drawer_widget->list_of_chats->visualItemRect(found_item) };

    QTest::mouseClick(main_window.left_drawer_widget->list_of_chats->viewport(), Qt::LeftButton, 0, rect.center());

//    QCOMPARE(main_window.get_active_chat_name(), selected_chat_name);
//    select_chat.simulate();
//    auto selected_items = main_window.list_of_chats->selectedItems();

}


void TestGui::check_send_message_data()
{
    create_send_message_data();
}

void TestGui::check_send_message()
{
    send_message();
}


void TestGui::create_send_message_data()
{
    QTest::addColumn<QTestEventList>("keyboard_events");
    QTest::addColumn<QTestEventList>("mouse_events");
    QTest::addColumn<QString>("results");

    QTestEventList first_message_keyboard;
    first_message_keyboard.addKeyClicks("hello world");

    QTestEventList first_message_mouse_events;
    first_message_mouse_events.addMouseClick(Qt::MouseButton::LeftButton);

    QTest::newRow("first message") << first_message_keyboard << first_message_mouse_events << "hello world";

    QTestEventList second_message_keyboard;
    second_message_keyboard.addKeyClicks("im hossein");

    QTestEventList second_message_mouse_events;
    second_message_mouse_events.addMouseClick(Qt::MouseButton::LeftButton);

    QTest::newRow("second message") << second_message_keyboard << second_message_mouse_events << "im hossein";
}

void TestGui::send_message()
{
    QFETCH(QTestEventList, keyboard_events);
    QFETCH(QTestEventList, mouse_events);
    QFETCH(QString, results);

    keyboard_events.simulate(main_window.active_chat_widget->send_message_textbox);
    mouse_events.simulate(main_window.active_chat_widget->send_message_pushbutton);
    QCOMPARE(main_window.active_chat_widget->get_last_message_on_active_chat()->text(), results);
}

QTEST_MAIN(TestGui)
#include "testgui.moc"

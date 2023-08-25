#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

class TestGui : public QObject
{
    Q_OBJECT;

    void send_message();

    void select_chat_by_chat_name(QString chat_name);

private slots:
    void initTestCase();

    void create_new_chat_data();
    void create_new_chat();

    void select_chat_data();
    void select_chat();

    void check_send_message_data();
    void check_send_message();

    void check_chat_messages_uniqueness();

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
    QTest::addColumn<QString>("results");

    QString chat_name_1{ "1" };
    QTestEventList first_message_keyboard;
    first_message_keyboard.addKeyClicks("hello world");
    QTestEventList first_message_mouse_events;
    first_message_mouse_events.addMouseClick(Qt::MouseButton::LeftButton);
    QTest::newRow("first message") << chat_name_1 << first_message_keyboard << first_message_mouse_events << "hello world";

    QString chat_name_2{ "2" };
    QTestEventList second_message_keyboard;
    second_message_keyboard.addKeyClicks("im hossein");
    QTestEventList second_message_mouse_events;
    second_message_mouse_events.addMouseClick(Qt::MouseButton::LeftButton);
    QTest::newRow("second message") << chat_name_2 << second_message_keyboard << second_message_mouse_events << "im hossein";
}

void TestGui::check_send_message()
{
    QFETCH(QString, chat_name);
    QFETCH(QTestEventList, type_message);
    QFETCH(QTestEventList, click_on_send_message);
    QFETCH(QString, results);

    select_chat_by_chat_name(chat_name);
    type_message.simulate(main_window.active_chat_widget->send_message_textbox);
    click_on_send_message.simulate(main_window.active_chat_widget->send_message_pushbutton);

    QCOMPARE(main_window.active_chat_widget->get_number_of_messages_in_active_chat(), 1);
    QCOMPARE(main_window.active_chat_widget->get_last_message_on_active_chat()->text(), results);
}

void TestGui::check_chat_messages_uniqueness()
{
    QString first_chat_message{ };
    select_chat_by_chat_name("1");
    first_chat_message = main_window.active_chat_widget->get_last_message_on_active_chat()->text();
    QCOMPARE(first_chat_message, "hello world");

    QString second_chat_message{ };
    select_chat_by_chat_name("2");
    second_chat_message = main_window.active_chat_widget->get_last_message_on_active_chat()->text();
    QCOMPARE(second_chat_message, "im hossein");
}

QTEST_MAIN(TestGui)
#include "testgui.moc"

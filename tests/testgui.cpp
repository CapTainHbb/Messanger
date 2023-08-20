#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

class TestGui : public QObject
{
    Q_OBJECT;

private slots:
    void initTestCase();

    void check_send_message_data();
    void check_send_message();

    void send_message_to_different_chat_data();
    void send_message_to_different_chat();

private:
    MainWindow main_window;
};

void TestGui::initTestCase()
{
    main_window.init_widgets();
}

void TestGui::check_send_message_data()
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

void TestGui::check_send_message()
{
    QFETCH(QTestEventList, keyboard_events);
    QFETCH(QTestEventList, mouse_events);
    QFETCH(QString, results);

    keyboard_events.simulate(main_window.send_message_textbox);
    mouse_events.simulate(main_window.send_message_pushbutton);
    QCOMPARE(main_window.get_last_message_on_active_chat()->text(), results);
}

void TestGui::send_message_to_different_chat_data()
{
    QTest::addColumn<QTestEventList>("type_message");
    QTest::addColumn<QTestEventList>("click_send_message");
//    QTest::addColumn<QString
}

void TestGui::send_message_to_different_chat()
{

}

QTEST_MAIN(TestGui)
#include "testgui.moc"

#include <TestGuiBase.hpp>

class StartNewChatForExistingContact : public TestGuiBase
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void start_new_chat_data();
    void start_new_chat();
};

void StartNewChatForExistingContact::initTestCase()
{
    connect_to_server_from_gui(XMPP_TEST_CLIENT_USERNAME,
                               XMPP_TEST_CLIENT_PASSWORD,
                               XMPP_SERVER_ADDRESS);
    create_test_contacts_from_gui();
}

void StartNewChatForExistingContact::start_new_chat_data()
{
    QTest::addColumn<Contact>("contact");
    QTest::addColumn<QString>("message_text");
    QTest::addColumn<int>("number_of_message_in_active_chat");

    QTRY_VERIFY(get_general_model()->get_contact_count() > 0);

    for(const auto& contact : get_general_model()->get_contacts())
    {
        QTestEventList click_on_contact_list{ };
        click_on_contact_list.addMouseClick(Qt::MouseButton::LeftButton);
                        
        QString message_text{ "hi " + contact.get_name() };
        QTestEventList type_message;
        type_message.addKeyClicks(message_text);

        QTestEventList click_on_send_message;
        click_on_send_message.addMouseClick(Qt::MouseButton::LeftButton);

        QTest::newRow(contact.get_name().toLocal8Bit()) 
                << contact
                << message_text
                << 1;
    }
    
}

void StartNewChatForExistingContact::start_new_chat()
{
    QFETCH(Contact, contact);
    QFETCH(QString, message_text);
    QFETCH(int, number_of_message_in_active_chat);

    if(get_general_model()->contact_has_chat(contact))
    {
        QFAIL("chat " + contact.get_name().toLocal8Bit() + " already exists!");
    }

    left_click_on_widget(get_left_drawer_widget()->contact_list_button);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == true);
    QCOMPARE(get_middle_stack_widget()->currentIndex(), CONTACT_LIST_INDEX);

    double_click_on_contact(contact);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == true);
    QCOMPARE(get_active_chat_widget()->isHidden(), false);
    QCOMPARE(get_middle_stack_widget()->currentIndex(), CHAT_LIST_INDEX);
    QCOMPARE(get_active_chat_widget()->get_chat_name(), contact.get_name());

    fill_text_input(message_text, get_active_chat_widget()->send_message_textbox);
    left_click_on_widget(get_active_chat_widget()->send_message_pushbutton);

    QCOMPARE(get_active_chat_widget()->get_number_of_messages(), number_of_message_in_active_chat);
    QCOMPARE(get_active_chat_widget()->get_last_message(), message_text);

    QVERIFY(get_chat_list_widget()->chat_exists(contact));
}

QTEST_MAIN(StartNewChatForExistingContact)
#include "StartNewChatForExistingContact.moc"
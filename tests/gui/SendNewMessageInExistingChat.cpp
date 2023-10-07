#include <TestGuiBase.hpp>

class SendNewMessageInExistingChat : public TestGuiBase
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void send_new_message_in_existing_chat_data();
    void send_new_message_in_existing_chat();

    void check_chat_uniquness();
};

void SendNewMessageInExistingChat::initTestCase()
{
    connect_to_server_from_gui(XMPP_TEST_CLIENT_USERNAME,
                               XMPP_TEST_CLIENT_PASSWORD,
                               XMPP_SERVER_ADDRESS);
    create_test_contacts_from_gui();
    create_test_chats_from_gui();
}

void SendNewMessageInExistingChat::send_new_message_in_existing_chat_data()
{
    QTest::addColumn<Contact>("contact");
    QTest::addColumn<QString>("message_text");
    QTest::addColumn<int>("number_of_message_in_active_chat");

    QString pre_text_message{ "how is every thing" };
    create_test_chats_from_gui(pre_text_message);
    for(const auto& contact : main_window.contact_proxy_model->source_model->get_contacts())
    {
        QTest::newRow(contact.get_name().toLocal8Bit()) 
                << contact 
                << pre_text_message + contact.get_name()
                << contact.chat_count();
    }
}

void SendNewMessageInExistingChat::send_new_message_in_existing_chat()
{
    QFETCH(Contact, contact);
    QFETCH(QString, message_text);
    QFETCH(int, number_of_message_in_active_chat);

    QCOMPARE(get_middle_stack_widget()->currentIndex(), CHAT_LIST_INDEX);

    select_chat(contact);

    QVERIFY(get_active_chat_widget()->isHidden() == false);
    QVERIFY(get_active_chat_widget()->chat_messages_frame->isHidden() == false);
    QVERIFY(get_active_chat_widget()->send_message_pushbutton->isHidden() == false);
    QVERIFY(get_active_chat_widget()->send_message_textbox->isHidden() == false);

    QCOMPARE(get_active_chat_widget()->get_chat_name(), contact.get_name());

    QCOMPARE(get_active_chat_widget()->get_number_of_messages(), number_of_message_in_active_chat);
    QCOMPARE(get_active_chat_widget()->get_last_message(), message_text);
}

void SendNewMessageInExistingChat::check_chat_uniquness()
{
    QStringList contacts_messages_in_active_chat_widget;
    for (auto &&contact : get_general_model()->get_contacts())
    {
        select_chat(contact);
        auto contact_chat_message_in_active_chat_widget{ get_active_chat_widget()->get_last_message() };
        contacts_messages_in_active_chat_widget.push_back(contact_chat_message_in_active_chat_widget);
    }

    QSet<QString> stringSet(contacts_messages_in_active_chat_widget.begin(), contacts_messages_in_active_chat_widget.end());
    QVERIFY(stringSet.count() == contacts_messages_in_active_chat_widget.count());
}

QTEST_MAIN(SendNewMessageInExistingChat)
#include "SendNewMessageInExistingChat.moc"

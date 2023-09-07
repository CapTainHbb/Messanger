#include <TestGuiBase.hpp>

class SendNewMessageInExistingChat : public TestGuiBase
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void send_new_message_in_existing_chat_data();
    void send_new_message_in_existing_chat();

    void check_chat_uniquness_data();
    void check_chat_uniquness();
};

void SendNewMessageInExistingChat::initTestCase()
{
    create_test_contacts(); 
    create_test_chats();   
}

void SendNewMessageInExistingChat::send_new_message_in_existing_chat_data()
{
    QTest::addColumn<Contact>("contact");
    QTest::addColumn<QTestEventList>("type_message");
    QTest::addColumn<QTestEventList>("click_on_send_message");
    QTest::addColumn<QString>("message_text");
    QTest::addColumn<int>("number_of_message_in_active_chat");
    
    for(const auto& contact : main_window.contact_proxy_model->source_model->get_contacts())
    {
        QTestEventList click_on_contact_list{ };
        click_on_contact_list.addMouseClick(Qt::MouseButton::LeftButton);
                        
        QString message_text{ "how is every thing " + contact.get_name() };
        QTestEventList type_message;
        type_message.addKeyClicks(message_text);
        
        QTestEventList click_on_send_message;
        click_on_send_message.addMouseClick(Qt::MouseButton::LeftButton);

        QTest::newRow(contact.get_name().toLocal8Bit()) 
                << contact 
                << type_message
                << click_on_send_message
                << message_text
                << contact.chat_count() + 1;
    }
}

void SendNewMessageInExistingChat::send_new_message_in_existing_chat()
{
    QFETCH(Contact, contact);
    QFETCH(QTestEventList, type_message);
    QFETCH(QTestEventList, click_on_send_message);
    QFETCH(QString, message_text);
    QFETCH(int, number_of_message_in_active_chat);

    QCOMPARE(get_middle_stack_widget()->currentIndex(), CHAT_LIST_INDEX);

    select_chat(contact);

    QVERIFY(get_active_chat_widget()->isHidden() == false);
    QVERIFY(get_active_chat_widget()->chat_messages_frame->isHidden() == false);
    QVERIFY(get_active_chat_widget()->send_message_pushbutton->isHidden() == false);
    QVERIFY(get_active_chat_widget()->send_message_textbox->isHidden() == false);

    QCOMPARE(get_active_chat_widget()->get_chat_name(), contact.get_name());

    type_message.simulate(get_active_chat_widget()->send_message_textbox);
    click_on_send_message.simulate(get_active_chat_widget()->send_message_pushbutton);

    QCOMPARE(get_active_chat_widget()->get_number_of_messages(), number_of_message_in_active_chat);
    QCOMPARE(get_active_chat_widget()->get_last_message(), message_text);
}

void SendNewMessageInExistingChat::check_chat_uniquness_data()
{

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

    QSet<QString> stringSet = QSet<QString>::fromList(contacts_messages_in_active_chat_widget);
    QVERIFY(stringSet.count() == contacts_messages_in_active_chat_widget.count());
}

QTEST_MAIN(SendNewMessageInExistingChat)
#include "SendNewMessageInExistingChat.moc"

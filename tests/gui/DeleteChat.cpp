#include <TestGuiBase.hpp>

class DeleteChat : public TestGuiBase
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void delete_selected_chat_data();
    void delete_selected_chat();

    void delete_unselected_chat();
};

void DeleteChat::initTestCase()
{
    create_test_contacts();
    create_test_chats();
}

void DeleteChat::delete_selected_chat_data()
{
    QTest::addColumn<Contact>("contact");
    
    for (const auto contact : get_general_model()->get_contacts())
    {
        QTest::newRow(contact.get_name().toLocal8Bit()) << contact;
    }    
}

void DeleteChat::delete_selected_chat()
{
    QFETCH(Contact, contact);

    select_chat(contact);
    right_click_on_chat(contact);
    left_click_on_delete_chat();

    QCOMPARE(get_chat_list_widget()->chat_exists(contact), false);
    QCOMPARE(get_active_chat_widget()->get_chat_status(), ActiveChat::Status::EMPTY_CHAT);
    
    QCOMPARE(get_active_chat_widget()->messages.count(), 0);
}

void DeleteChat::delete_unselected_chat()
{
    create_test_chats();

    auto contacts_in_model{ get_general_model()->get_contacts() };

    QVERIFY(contacts_in_model.count() > 1);

    select_chat(contacts_in_model.at(0));
    right_click_on_chat(contacts_in_model.at(1));
    left_click_on_delete_chat();

    QCOMPARE(get_chat_list_widget()->chat_exists(contacts_in_model.at(1)), false);
    QCOMPARE(get_active_chat_widget()->get_chat_status(), ActiveChat::Status::CHAT_WITH_MESSAGES);
    
    QVERIFY(get_active_chat_widget()->messages.count() != 0);
}


QTEST_MAIN(DeleteChat)
#include "DeleteChat.moc"
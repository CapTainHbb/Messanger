#include <TestGuiBase.hpp>


class SelectExistingChat : public TestGuiBase
{
    Q_OBJECT

private:
    /* data */
public:
    SelectExistingChat();
    ~SelectExistingChat();

private slots:
    void initTestCase() override;

    void select_existing_chat_data();
    void select_existing_chat();
};

SelectExistingChat::SelectExistingChat()
{
}

SelectExistingChat::~SelectExistingChat()
{
}

void SelectExistingChat::initTestCase()
{
    create_test_contacts();
    create_test_chats();
}

void SelectExistingChat::select_existing_chat_data()
{
    QTest::addColumn<Contact>("contact_in_chat_list");
    QTest::addColumn<Contact>("contact_in_active_chat");

    for(auto contact : get_general_model()->get_contacts())
    {
        QTest::newRow(contact.get_name().toLocal8Bit()) << contact << contact;
    }
}

void SelectExistingChat::select_existing_chat()
{
    QFETCH(Contact, contact_in_chat_list);
    QFETCH(Contact, contact_in_active_chat);

    select_chat(contact_in_chat_list);

    QVERIFY(contact_in_chat_list == get_active_chat_widget()->active_contact);
    QVERIFY(contact_in_chat_list.get_last_chat() == get_active_chat_widget()->active_contact.get_last_chat());
}   

QTEST_MAIN(SelectExistingChat)
#include "SelectExistingChat.moc"

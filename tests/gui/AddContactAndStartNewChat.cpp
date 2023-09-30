#include <TestGuiBase.hpp>

class AddContactAndStartNewChat : public  TestGuiBase
{
Q_OBJECT

private slots:
    void initTestCase() override;

    void add_contact_and_start_new_chat_data();
    void add_contact_and_start_new_chat();
};

void AddContactAndStartNewChat::initTestCase()
{

}

void AddContactAndStartNewChat::add_contact_and_start_new_chat_data()
{

}

void AddContactAndStartNewChat::add_contact_and_start_new_chat()
{

}


QTEST_MAIN(AddContactAndStartNewChat)
#include "AddContactAndStartNewChat.moc"

#include <QTest>
#include <QWidget>
#include <mainwindow.h>
#include <iostream>

#include <TestModelBase.hpp>


class TestChatListProxyModel : public TestModelBase
{
    Q_OBJECT

private:
    ChatListProxyModel *chat_list_model{ nullptr };

public:
    TestChatListProxyModel(/* args */) = default;
    ~TestChatListProxyModel() = default;

private slots:
    void initTestCase() override;
    
    void create_contact_data();
    void create_contact();

    void add_chat_to_contact_data();
    void add_chat_to_contact();
};

void TestChatListProxyModel::initTestCase()
{
    set_general_model(main_window.general_model);
    chat_list_model = main_window.chat_list_proxy_model;
    create_test_contacts();
}

void TestChatListProxyModel::create_contact_data()
{
    QTest::addColumn<Contact>("contact");

    for (auto& contact : test_contacts)
    {
        QTest::newRow(contact.get_name().toLocal8Bit()) << contact;
    }
    
}

void TestChatListProxyModel::create_contact()
{
    QFETCH(Contact, contact);

    add_contact_to_model(contact);

    auto contact_in_model{ get_contact_from_model(contact) };

    QVERIFY(contact_in_model == contact);
}


void TestChatListProxyModel::add_chat_to_contact_data()
{
    QTest::addColumn<Contact>("contact");
    QTest::addColumn<QString>("chat_message");
    QTest::addColumn<int>("chat_list_model_index_row");

    for(int i{ 0 }; i < test_contacts.count(); i++)
    {
        QTest::newRow(test_contacts.at(i).get_name().toLocal8Bit()) 
        << test_contacts.at(i) 
        << (QString("hi ") + test_contacts.at(i).get_name())
        << i;
    }
}

void TestChatListProxyModel::add_chat_to_contact()
{
    QFETCH(Contact, contact);
    QFETCH(QString, chat_message);
    QFETCH(int, chat_list_model_index_row);

    QVERIFY(get_general_model()->contact_has_chat(contact) == false);
    get_general_model()->add_chat_to_contact(contact, chat_message);
    QVERIFY(get_general_model()->contact_has_chat(contact)== true);

    auto contact_in_chat_list_model{ chat_list_model->get_contact_in_chat_list(chat_list_model_index_row) };

    QCOMPARE(contact.get_name() , contact_in_chat_list_model.get_name());
}


QTEST_MAIN(TestChatListProxyModel)
#include "TestChatListProxyModel.moc"
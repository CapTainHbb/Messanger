#include <TestGuiBase.hpp>

class AddContact : public TestGuiBase
{
Q_OBJECT

private slots:
    void initTestCase() override;
    void add_contact_data();
    void add_contact();
};

void AddContact::initTestCase()
{
    connect_to_server_from_gui(XMPP_TEST_CLIENT_USERNAME,
                               XMPP_TEST_CLIENT_PASSWORD,
                               XMPP_SERVER_ADDRESS);
    left_click_on_widget(get_left_drawer_widget()->add_contact_button);
}

void AddContact::add_contact_data()
{
    QTest::addColumn<Contact>("contact");
    QTest::addColumn<int>("contacts_count");

    create_test_contacts();

    int contacts_count{ 0 };
    for(const auto& contact : test_contacts)
    {
        QTest::newRow(contact.get_name().toLocal8Bit())
                << contact
                << ++contacts_count;
    }
}

void AddContact::add_contact()
{
    QFETCH(Contact, contact);
    QFETCH(int, contacts_count);

    add_contact_from_gui(contact);

    QTRY_VERIFY(get_general_model()->get_last_added_contact() == contact);
    QTRY_COMPARE(get_general_model()->get_contacts().count(), contacts_count);
}


QTEST_MAIN(AddContact)
#include "AddContact.moc"
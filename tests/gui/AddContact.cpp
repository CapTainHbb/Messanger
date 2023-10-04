#include <TestGuiBase.hpp>

class AddContact : public TestGuiBase
{
Q_OBJECT

private:
    QList<QString> contacts_to_add;

private slots:
    void initTestCase() override;

    void add_contact_data();
    void add_contact();
    void check_all_added_contact_in_model();
};

void AddContact::initTestCase()
{
    start_xmpp_test_server();
    connect_to_server(XMPP_TEST_CLIENT_USERNAME,
                      XMPP_TEST_CLIENT_PASSWORD,
                      XMPP_SERVER_ADDRESS);
    left_click_on_widget(get_left_drawer_widget()->add_contact_button);

    contacts_to_add.append("ahmad");
    contacts_to_add.append("amir_hossein");
    contacts_to_add.append("javad");
    contacts_to_add.append("navid");
}

void AddContact::add_contact_data()
{
    QTest::addColumn<QString>("contact_username");
    QTest::addColumn<QString>("contact_domain");

    for(const auto& contact_string : contacts_to_add)
    {
        QTest::newRow(contact_string.toLocal8Bit())
                << contact_string
                << XMPP_SERVER_ADDRESS;
    }
}

void AddContact::add_contact()
{
    QFETCH(QString, contact_username);
    QFETCH(QString, contact_domain);

    QString jid{ contact_username + "@" + contact_domain };
    add_contact_from_gui(jid);

    Contact expected_contact{ jid };

    QTRY_VERIFY(get_general_model()->get_last_added_contact() == expected_contact);
}

void AddContact::check_all_added_contact_in_model()
{
    QCOMPARE(get_general_model()->get_contacts().count(), contacts_to_add.count());
}


QTEST_MAIN(AddContact)
#include "AddContact.moc"
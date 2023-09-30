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
    connect_to_server(XMPP_TEST_CLIENT_USERNAME,
                      XMPP_TEST_CLIENT_PASSWORD,
                      XMPP_SERVER_ADDRESS);
    left_click_on_widget(get_left_drawer_widget()->add_contact_button);
}

void AddContact::add_contact_data()
{
    QTest::addColumn<QString>("contact_username");
    QTest::addColumn<QString>("contact_domain");

    QTest::newRow("first_contact")
            << "ahmad"
            << XMPP_SERVER_ADDRESS;
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

QTEST_MAIN(AddContact)
#include "AddContact.moc"
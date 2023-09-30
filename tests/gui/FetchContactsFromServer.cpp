#include <TestGuiBase.hpp>

class FetchContactsFromServer : public TestGuiBase
{
Q_OBJECT

private:



private slots:
    void initTestCase() override;

    void add_contact_with_test_client_data();
    void add_contact_with_test_client();

    void fetch_contacts_from_server_data();
    void fetch_contacts_from_server();
};

void FetchContactsFromServer::initTestCase()
{
    start_xmpp_test_server();
    connect_xmpp_test_client_to_server();
}

void FetchContactsFromServer::add_contact_with_test_client_data()
{
    QTest::addColumn<QString>("contact_jid");

    QTest::newRow("ahmad") <<
                    "ahmad@127.0.0.1";
    QTest::newRow("hossein") <<
                   "hossein@127.0.0.1";

}

void FetchContactsFromServer::add_contact_with_test_client()
{
    QFETCH(QString, contact_jid);

    QSignalSpy spy(xmpp_test_client.roster_manager,
                   SIGNAL(itemAdded(const QString&)));
    xmpp_test_client.on_request_add_contact(contact_jid);

    QTRY_COMPARE(spy.count(), 1);
}

void FetchContactsFromServer::fetch_contacts_from_server_data()
{
    add_contact_with_test_client_data();
}


void FetchContactsFromServer::fetch_contacts_from_server()
{
    QFETCH(QString, contact_jid);

    connect_to_server(XMPP_TEST_CLIENT_USERNAME,
                      XMPP_TEST_CLIENT_PASSWORD,
                      XMPP_SERVER_ADDRESS);

    try
    {
        get_general_model()->get_contact(contact_jid);
    }
    catch (std::invalid_argument& ex)
    {
        QFAIL(ex.what());
    }
}


QTEST_MAIN(FetchContactsFromServer)
#include "FetchContactsFromServer.moc"

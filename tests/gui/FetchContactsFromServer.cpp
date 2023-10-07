#include <TestGuiBase.hpp>

class FetchContactsFromServer : public TestGuiBase
{
Q_OBJECT

private slots:
    void initTestCase() override;

    void fetch_contacts_from_server();
};

void FetchContactsFromServer::initTestCase()
{
    connect_to_server_from_gui(XMPP_TEST_CLIENT_USERNAME,
                               XMPP_TEST_CLIENT_PASSWORD,
                               XMPP_SERVER_ADDRESS);

    create_test_contacts_from_gui();
}

void FetchContactsFromServer::fetch_contacts_from_server()
{
    get_xmpp_client()->disconnectFromServer();

    get_general_model()->delete_all_contacts();
    QTRY_COMPARE(get_general_model()->get_contact_count(), 0);

    connect_to_server_from_gui(XMPP_TEST_CLIENT_USERNAME,
                               XMPP_TEST_CLIENT_PASSWORD,
                               XMPP_SERVER_ADDRESS);
    try
    {
        for(const auto& contact : test_contacts)
        {
            QTRY_VERIFY(get_general_model()->contact_exists(contact));
        }
    }
    catch (std::invalid_argument& ex)
    {
        QFAIL(ex.what());
    }
}


QTEST_MAIN(FetchContactsFromServer)
#include "FetchContactsFromServer.moc"

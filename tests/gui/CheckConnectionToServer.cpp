#include <TestGuiBase.hpp>

class CheckConnectionToServer : public TestGuiBase
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void check_connection_to_server_data();
    void check_connection_to_server();
};

void CheckConnectionToServer::initTestCase()
{
    left_click_on_widget(get_left_drawer_widget()->settings_button);
}

void CheckConnectionToServer::check_connection_to_server_data()
{
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("domain_name");

    QTest::newRow("authentication_data")
                            << XMPP_TEST_CLIENT_USERNAME
                            << XMPP_TEST_CLIENT_PASSWORD
                            << XMPP_SERVER_ADDRESS;
}

void CheckConnectionToServer::check_connection_to_server()
{
    QFETCH(QString, username);
    QFETCH(QString, password);
    QFETCH(QString, domain_name);

    connect_to_server_from_gui(username,
                               password,
                               domain_name);
}


QTEST_MAIN(CheckConnectionToServer)
#include "CheckConnectionToServer.moc"

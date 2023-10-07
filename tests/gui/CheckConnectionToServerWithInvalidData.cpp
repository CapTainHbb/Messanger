#include <TestGuiBase.hpp>

class CheckConnectionToServerWithInvalidData : public TestGuiBase
{
    Q_OBJECT

private slots:
    void initTestCase() override;

    void check_connection_to_server_data();
    void check_connection_to_server();
};

void CheckConnectionToServerWithInvalidData::initTestCase()
{
    QTestEventList events;
    events.addMouseClick(Qt::MouseButton::LeftButton);
    events.simulate(get_left_drawer_widget()->settings_button);
}

void CheckConnectionToServerWithInvalidData::check_connection_to_server_data()
{
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("domain_name");

    QTest::newRow("invalid_authentication_data")
            << XMPP_TEST_CLIENT_USERNAME
            << "12345"
            << XMPP_SERVER_ADDRESS;

}

void CheckConnectionToServerWithInvalidData::check_connection_to_server()
{
    QFETCH(QString, username);
    QFETCH(QString, password);
    QFETCH(QString, domain_name);

    {
        // does not work and I don't know why!!
//        left_click_on_widget(get_settings_widget()->connect_to_server_button);
    }

    connect_to_server_from_gui(username, password, domain_name, QXmppClient::State::DisconnectedState);
}


QTEST_MAIN(CheckConnectionToServerWithInvalidData)
#include "CheckConnectionToServerWithInvalidData.moc"

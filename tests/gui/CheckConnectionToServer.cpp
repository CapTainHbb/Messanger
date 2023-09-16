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
    QTestEventList events;
    events.addMouseClick(Qt::MouseButton::LeftButton);
    events.simulate(get_left_drawer_widget()->settings_button);
}

void CheckConnectionToServer::check_connection_to_server_data()
{
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("domain_name");

    QTest::newRow("authentication_data")
                            << "captainhb"
                            << "capitanhb12345"
                            << "127.0.0.1";
}

void CheckConnectionToServer::check_connection_to_server()
{
    QFETCH(QString, username);
    QFETCH(QString, password);
    QFETCH(QString, domain_name);

    fill_text_input(username, get_settings_widget()->username_text_input);
    fill_text_input(password, get_settings_widget()->password_text_input);
    fill_text_input(domain_name, get_settings_widget()->domain_name_text_input);

    {
        // does not work and I dont know why!!
        //    QTestEventList click_on_connect_to_server;
        //    click_on_connect_to_server.addMouseClick(Qt::MouseButton::LeftButton);
        //    click_on_connect_to_server.simulate(get_settings_widget()->connect_to_server_button);
    }

    get_settings_widget()->on_click_connect_to_server_button();
    QTRY_COMPARE(get_settings_widget()->get_last_connection_result(), QXmppClient::State::ConnectedState);
}


QTEST_MAIN(CheckConnectionToServer)
#include "CheckConnectionToServer.moc"

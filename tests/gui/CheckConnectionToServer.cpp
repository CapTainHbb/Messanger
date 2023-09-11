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
    QTest::addColumn<QString>("first_octed");
    QTest::addColumn<QString>("second_octed");
    QTest::addColumn<QString>("third_octed");
    QTest::addColumn<QString>("fourth_octed");

    QTest::newRow("google_dns_ip_address") << "8" << "8" << "8" << "8";
}

void CheckConnectionToServer::check_connection_to_server()
{
    QFETCH(QString, first_octed);
    QFETCH(QString, second_octed);
    QFETCH(QString, third_octed);
    QFETCH(QString, fourth_octed);

    QTestEventList type_ip_address;
    QString ip_address_text{ first_octed + "." + second_octed + "." + third_octed + "." + fourth_octed };
    type_ip_address.addKeyClicks(ip_address_text);
    type_ip_address.simulate(get_settings_widget()->ip_address_text_input);

    // does not work and I dont know why!!
    // QTestEventList click_on_connect_to_server;
    // click_on_connect_to_server.addMouseClick(Qt::MouseButton::LeftButton);
    // click_on_connect_to_server.simulate(get_settings_widget()->connect_to_server_button);
    get_settings_widget()->on_click_connect_to_server_button();
    
    QString connection_result{ ip_address_text + " is reachable" };
    QCOMPARE(get_settings_widget()->connection_result_label->text(), connection_result);
}

QTEST_MAIN(CheckConnectionToServer)
#include "CheckConnectionToServer.moc"

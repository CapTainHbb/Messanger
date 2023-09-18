#include <TestGuiBase.hpp>

class FetchContactsFromServer : public TestGuiBase
{
Q_OBJECT


private slots:
    void initTestCase() override;

    void fetch_contacts_from_server_data();
    void fetch_contacts_from_server();
};

void FetchContactsFromServer::initTestCase()
{

}

void FetchContactsFromServer::fetch_contacts_from_server_data()
{
    QTest::addColumn<QString>("username");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("domain_name");
    QTest::addColumn<QStringList>("contacts_name");

    QStringList contacts_name;
    contacts_name.append("alice");
    contacts_name.append("bob");

    QTest::newRow("authentication_data")
            << "captainhb"
            << "capitanhb12345"
            << "127.0.0.1"
            << contacts_name;
}

void FetchContactsFromServer::fetch_contacts_from_server()
{
    QFETCH(QString, username);
    QFETCH(QString, password);
    QFETCH(QString, domain_name);
    QFETCH(QStringList, contacts_name);

    connect_to_server(username, password, domain_name);

    const auto contacts_in_model{ get_general_model()->get_contacts() };
    QTRY_VERIFY(contacts_name.at(0) == contacts_in_model.at(0).get_name());
}


QTEST_MAIN(FetchContactsFromServer)
#include "FetchContactsFromServer.moc"

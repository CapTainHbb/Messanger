#include <TestBase.hpp>
#include <XmppServer.hpp>

class HandleTwoRostersContacts : public TestBase
{
    Q_OBJECT
private:
    XmppServer server{ "127.0.0.1" };
    XmppClient client{ };

private slots:
    void initTestCase();
};

void HandleTwoRostersContacts::initTestCase()
{
    client.connectToServer(XMPP_TEST_CLIENT_JID, XMPP_TEST_CLIENT_PASSWORD);
    QTRY_VERIFY2_WITH_TIMEOUT(client.isConnected(), "timeout", 10000);
}

QTEST_MAIN(HandleTwoRostersContacts)
#include "HandleTwoRostersContacts.moc"
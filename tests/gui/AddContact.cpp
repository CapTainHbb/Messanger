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
    QTestEventList click_on_add_contact;
    click_on_add_contact.addMouseClick(Qt::LeftButton);
    click_on_add_contact.simulate(get_left_drawer_widget()->add_contact_button);
}

void AddContact::add_contact_data()
{
    QTest::addColumn<QString>("contact_username");
    QTest::addColumn<QString>("contact_domain");

    QTest::newRow("first_contact")
            << "captainhb"
            << "127.0.0.1";
}

void AddContact::add_contact()
{
    QFETCH(QString, contact_username);
    QFETCH(QString, contact_domain);

    QString jid{ contact_username + "@" + contact_domain };
    fill_text_input(jid, get_add_contact_widget()->contact_jid_text_input);

    QTestEventList click_on_add_contact;
    click_on_add_contact.addMouseClick(Qt::MouseButton::LeftButton);

    click_on_add_contact.simulate(get_add_contact_widget()->add_contact_button);

    auto found_contact { get_general_model()->get_contact(contact_username) };
}

QTEST_MAIN(AddContact)
#include "AddContact.moc"
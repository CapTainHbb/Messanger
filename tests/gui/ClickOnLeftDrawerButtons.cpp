#include <TestGuiBase.hpp>


class ClickOnLeftDrawerButtons : public TestGuiBase
{
    Q_OBJECT
private slots:
    void initTestCase() override;
    
    void click_on_contact_list();
    void click_on_chat_list();
    void click_on_setttings();
};

void ClickOnLeftDrawerButtons::initTestCase()
{

}

void ClickOnLeftDrawerButtons::click_on_contact_list()
{
    QTestEventList events;
    events.addMouseClick(Qt::MouseButton::LeftButton);
    events.simulate(get_left_drawer_widget()->contact_list_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() ==  CONTACT_LIST_INDEX);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == false);
}

void ClickOnLeftDrawerButtons::click_on_chat_list()
{
    QTestEventList events;
    events.addMouseClick(Qt::MouseButton::LeftButton);
    events.simulate(get_left_drawer_widget()->chat_list_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() == CHAT_LIST_INDEX);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == false);

}

void ClickOnLeftDrawerButtons::click_on_setttings()
{
    QTestEventList events;
    events.addMouseClick(Qt::MouseButton::LeftButton);
    events.simulate(get_left_drawer_widget()->settings_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() == SETTINGS_INDEX);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
}

QTEST_MAIN(ClickOnLeftDrawerButtons)
#include "ClickOnLeftDrawerButtons.moc"
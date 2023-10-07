#include <TestGuiBase.hpp>

class ClickOnLeftDrawerButtons : public TestGuiBase
{
    Q_OBJECT
private slots:
    void initTestCase() override;
    
    void click_on_contact_list();
    void click_on_chat_list();
    void click_on_settings();
    void click_on_add_contact();
};

void ClickOnLeftDrawerButtons::initTestCase()
{

}

void ClickOnLeftDrawerButtons::click_on_contact_list()
{
    left_click_on_widget(get_left_drawer_widget()->contact_list_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() ==  CONTACT_LIST_INDEX);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->add_contact_button->isChecked() == false);
}

void ClickOnLeftDrawerButtons::click_on_chat_list()
{
    left_click_on_widget(get_left_drawer_widget()->chat_list_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() == CHAT_LIST_INDEX);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->add_contact_button->isChecked() == false);
}

void ClickOnLeftDrawerButtons::click_on_settings()
{
    left_click_on_widget(get_left_drawer_widget()->settings_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() == SETTINGS_INDEX);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->add_contact_button->isChecked() == false);
}

void ClickOnLeftDrawerButtons::click_on_add_contact()
{
    left_click_on_widget(get_left_drawer_widget()->add_contact_button);
    QVERIFY(get_middle_stack_widget()->currentIndex() == ADD_CONTACT_INDEX);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->add_contact_button->isChecked() == true);
}


QTEST_MAIN(ClickOnLeftDrawerButtons)
#include "ClickOnLeftDrawerButtons.moc"
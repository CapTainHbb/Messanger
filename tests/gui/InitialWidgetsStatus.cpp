#include <TestGuiBase.hpp>

class InitialWidgetsStatus : public TestGuiBase
{
    Q_OBJECT

private slots:

    void initTestCase() override;

    void widgets_visibility();

    void widgets_checkablity();
};

void InitialWidgetsStatus::initTestCase()
{
}

void InitialWidgetsStatus::widgets_visibility()
{
    QVERIFY(get_left_drawer_widget()->isHidden() == false);

    QVERIFY(get_middle_stack_widget()->isHidden() == false);
    QVERIFY(get_chat_list_widget()->isHidden() == false);
    QVERIFY(get_contact_list_wiget()->isHidden() == true);

    QVERIFY(get_active_chat_widget()->isHidden() == false);
    QVERIFY(get_active_chat_widget()->chat_messages_frame->isHidden() == false);
    QVERIFY(get_active_chat_widget()->send_message_pushbutton->isHidden() == true);
    QVERIFY(get_active_chat_widget()->send_message_textbox->isHidden() == true);
}

void InitialWidgetsStatus::widgets_checkablity()
{
    QVERIFY(get_left_drawer_widget()->chat_list_button->isChecked() == true);
    QVERIFY(get_left_drawer_widget()->contact_list_button->isChecked() == false);
    QVERIFY(get_left_drawer_widget()->settings_button->isChecked() == false);
}

QTEST_MAIN(InitialWidgetsStatus)
#include "InitialWidgetsStatus.moc"
#include <TestGuiBase.hpp>

class InitialWidgetsVisibility : public TestGuiBase
{
    Q_OBJECT

private slots:

    void initTestCase() override;

    void widgets_visibility();
};

void InitialWidgetsVisibility::initTestCase()
{
}

void InitialWidgetsVisibility::widgets_visibility()
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

QTEST_MAIN(InitialWidgetsVisibility)
#include "InitialWidgetsVisibility.moc"
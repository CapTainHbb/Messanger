#include <TestGuiBase.hpp>

void TestGuiBase::double_click_on_contact(const Contact& contact)
{
    auto contact_model_index{ get_general_model()->get_contact_model_index(contact) };
    emit get_contact_list_wiget()->on_item_double_clicked(contact_model_index);
    // auto rect{ get_contact_list_wiget()->get_item_rect(contact) };
    // QTest::mouseClick(get_contact_list_wiget()->contact_list->viewport(), Qt::LeftButton, 0, rect.center());
    // QTest::mouseDClick(get_contact_list_wiget()->contact_list->viewport(), Qt::LeftButton, 0, rect.center());
}

void TestGuiBase::select_chat(const Contact& contact)
{
    auto rect{ get_chat_list_widget()->get_item_rect(contact) };

    QTest::mouseClick(get_chat_list_widget()->chat_list->viewport(),
                      Qt::LeftButton, Qt::KeyboardModifier::NoModifier, rect.center());
}


void TestGuiBase::right_click_on_chat(const Contact& contact)
{
    auto rect{ get_chat_list_widget()->get_item_rect(contact) };
    QTest::mouseClick(get_chat_list_widget()->chat_list->viewport(),
        Qt::RightButton, Qt::KeyboardModifier::NoModifier, rect.center());
}

void TestGuiBase::left_click_on_delete_chat()
{
    get_chat_list_widget()->delete_chat->trigger();
}

ContactListWidget *TestGuiBase::get_contact_list_wiget() const
{
    return main_window.middle_stack_widget->contact_list_widget;
}

ChatListWidget *TestGuiBase::get_chat_list_widget() const
{
    return main_window.middle_stack_widget->chat_list_widget;
}

LeftDrawer *TestGuiBase::get_left_drawer_widget() const
{
    return main_window.left_drawer_widget;
}

ActiveChat *TestGuiBase::get_active_chat_widget() const
{
    return main_window.active_chat_widget;
}

MiddleStack *TestGuiBase::get_middle_stack_widget() const
{
    return main_window.middle_stack_widget;
}

SettingsWidget *TestGuiBase::get_settings_widget() const
{
    return main_window.middle_stack_widget->settings_widget;
}

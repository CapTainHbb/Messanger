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

void TestGuiBase::fill_text_input(const QString& text, QWidget* widget)
{
    QTestEventList type_password;
    type_password.addKeyClicks(text);
    type_password.simulate(widget);
}

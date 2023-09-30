#include <TestGuiBase.hpp>

void TestGuiBase::double_click_on_contact(const Contact& contact)
{
    auto contact_model_index{ get_general_model()->get_contact_model_index(contact) };
    emit get_contact_list_wiget()->on_item_double_clicked(contact_model_index);
//     auto rect{ get_contact_list_wiget()->get_item_rect(contact) };
//     QTest::mouseClick(get_contact_list_wiget()->contact_list->viewport(),
//                       Qt::LeftButton,
//                       Qt::KeyboardModifier::NoModifier,
//                       rect.center());
//
//     QTest::mouseDClick(get_contact_list_wiget()->contact_list->viewport(),
//                        Qt::LeftButton,
//                        Qt::KeyboardModifier::NoModifier,
//                        rect.center());
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

void TestGuiBase::add_contact_from_gui(const QString& jid)
{
    fill_text_input(jid, get_add_contact_widget()->contact_jid_text_input);

    QTestEventList click_on_add_contact;
    click_on_add_contact.addMouseClick(Qt::MouseButton::LeftButton);

    click_on_add_contact.simulate(get_add_contact_widget()->add_contact_button);
}

void TestGuiBase::fill_text_input(const QString& text, QWidget* widget)
{
    QTestEventList type_in_text_edit;
    type_in_text_edit.addKeyClicks(text);
    type_in_text_edit.simulate(widget);
}

void TestGuiBase::left_click_on_widget(QWidget* widget)
{
    QTestEventList left_click_event;
    left_click_event.addMouseClick(Qt::LeftButton);
    left_click_event.simulate(widget);
}

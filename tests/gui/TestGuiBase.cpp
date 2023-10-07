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

void TestGuiBase::add_contact_from_gui(const Contact& contact)
{
    fill_text_input(contact.get_name(), get_add_contact_widget()->contact_name_text_input);
    fill_text_input(contact.get_domain(), get_add_contact_widget()->contact_domain_text_input);

    QTestEventList click_on_add_contact;
    click_on_add_contact.addMouseClick(Qt::MouseButton::LeftButton);

    click_on_add_contact.simulate(get_add_contact_widget()->add_contact_button);
    get_add_contact_widget()->contact_name_text_input->clear();
    get_add_contact_widget()->contact_domain_text_input->clear();

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

void TestGuiBase::connect_to_server_from_gui(const QString& username,
                                          const QString& password,
                                          const QString& domain_name,
                                          QXmppClient::State desired_state)
{
    get_settings_widget()->username_text_input->setText(username);
    get_settings_widget()->password_text_input->setText(password);
    get_settings_widget()->domain_name_text_input->setText(domain_name);

    get_settings_widget()->on_click_connect_to_server_button();
    QTRY_COMPARE_EQ_WITH_TIMEOUT(get_settings_widget()->get_last_connection_result(),
                                 desired_state,
                                 10000);
}

void TestGuiBase::create_test_contacts_from_gui()
{
    test_contacts.append(Contact("bob"));
    test_contacts.append(Contact("alice"));
    test_contacts.append(Contact("sam"));
    test_contacts.append(Contact("harry"));

    for(const auto& contact_jid : test_contacts)
    {
        add_contact_from_gui(contact_jid);
    }

    QTRY_VERIFY(get_general_model()->get_contact_count() == test_contacts.count());
}

void TestGuiBase::create_test_chats_from_gui(const QString& pre_text)
{
    for(const auto& contact : test_contacts)
    {
        left_click_on_widget(get_left_drawer_widget()->contact_list_button);
        double_click_on_contact(contact);

        QString message_text{ pre_text + contact.get_name() };
        fill_text_input(message_text, get_active_chat_widget()->send_message_textbox);
        left_click_on_widget(get_active_chat_widget()->send_message_pushbutton);

        QCOMPARE(get_active_chat_widget()->get_last_message(), message_text);
        QVERIFY(get_chat_list_widget()->chat_exists(contact));
    }

}

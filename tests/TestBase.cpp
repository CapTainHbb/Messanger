#include <TestBase.hpp>

TestBase::TestBase(/* args */)
{
    set_general_model(main_window.general_model);
}

TestBase::~TestBase()
{
}

ContactListWidget *TestBase::get_contact_list_wiget() const
{
    return main_window.middle_stack_widget->contact_list_widget;
}

AddContactWidget *TestBase::get_add_contact_widget() const
{
    return main_window.middle_stack_widget->add_contact_widget;
}


ChatListWidget *TestBase::get_chat_list_widget() const
{
    return main_window.middle_stack_widget->chat_list_widget;
}

LeftDrawer *TestBase::get_left_drawer_widget() const
{
    return main_window.left_drawer_widget;
}

ActiveChat *TestBase::get_active_chat_widget() const
{
    return main_window.active_chat_widget;
}

MiddleStack *TestBase::get_middle_stack_widget() const
{
    return main_window.middle_stack_widget;
}

SettingsWidget *TestBase::get_settings_widget() const
{
    return main_window.middle_stack_widget->settings_widget;
}


void TestBase::create_test_contacts()
{
    add_contact("alice");
    add_contact("bob");
    add_contact("harry");
    add_contact("sam");
}

void TestBase::create_test_chats()
{
    auto contacts_in_model{ get_general_model()->get_contacts() };
    for (int i = contacts_in_model.count() - 1; i >= 0; i--)
    {
        get_general_model()->add_chat_to_contact(contacts_in_model.at(i), "hi " + contacts_in_model.at(i).get_name());
    }
}

void TestBase::add_contact(QString contact_name)
{
    main_window.contact_proxy_model->source_model->add_contact(contact_name);
}

Contact TestBase::get_contact(QString contact_name)
{
    return main_window.contact_proxy_model->source_model->get_contact(contact_name);
}

GeneralModel *TestBase::get_general_model()
{
    return general_model;
}

void TestBase::set_general_model(GeneralModel *model)
{
    general_model = model;
}

void TestBase::connect_to_server(const QString& username,
                       const QString& password,
                       const QString& domain_name)
{
    get_settings_widget()->username_text_input->setText(username);
    get_settings_widget()->password_text_input->setText(password);
    get_settings_widget()->domain_name_text_input->setText(domain_name);

    get_settings_widget()->on_click_connect_to_server_button();
    QTRY_COMPARE(get_settings_widget()->get_last_connection_result(), QXmppClient::State::ConnectedState);
}


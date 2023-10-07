#include <TestBase.hpp>
#include <utility>

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

XmppClient *TestBase::get_xmpp_client()
{
    return &main_window.xmpp_client;
}

void TestBase::add_contact_to_model(const Contact& contact) const
{
    main_window.contact_proxy_model->source_model->add_contact(contact);
}


Contact TestBase::get_contact_from_model(const Contact& contact) const
{
    return main_window.contact_proxy_model->source_model->get_contact(contact);
}

GeneralModel *TestBase::get_general_model()
{
    return general_model;
}

void TestBase::set_general_model(GeneralModel *model)
{
    general_model = model;
}

void TestBase::create_test_contacts()
{
    test_contacts.append(Contact("alice"));
    test_contacts.append(Contact("harry"));
    test_contacts.append(Contact("bob"));
    test_contacts.append(Contact("sam"));
}


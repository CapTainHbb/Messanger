#include <TestBase.hpp>

TestBase::TestBase(/* args */)
{
    set_general_model(main_window.general_model);
}

TestBase::~TestBase()
{
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


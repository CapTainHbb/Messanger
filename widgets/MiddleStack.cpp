#include "MiddleStack.hpp"

MiddleStack::MiddleStack(ContactProxyModel *_contact_proxy_model,
                     ChatListProxyModel *_chat_list_proxy_model,
                     QWidget *parent)
: QStackedWidget(parent),
contact_proxy_model{ _contact_proxy_model }, 
chat_list_proxy_model{ _chat_list_proxy_model }
{
    // @note
    // order of initialization is important!
    init_chat_list_widget();
    init_contact_list_widget();
    init_add_contact_widget();
    init_settings_widget();
    init_signal_slots();
    setCurrentIndex(CHAT_LIST_INDEX);
}

MiddleStack::~MiddleStack()
{
}

void MiddleStack::init_chat_list_widget()
{
    chat_list_widget = new ChatListWidget(chat_list_proxy_model, this);
    this->addWidget(chat_list_widget);
}

void MiddleStack::init_contact_list_widget()
{
    contact_list_widget = new ContactListWidget(contact_proxy_model, this);
    this->addWidget(contact_list_widget);
}

void MiddleStack::init_add_contact_widget()
{
    add_contact_widget = new AddContactWidget(this);
    add_contact_widget->setObjectName("add_contact_widget");
    this->addWidget(add_contact_widget);

}

void MiddleStack::init_settings_widget()
{
    settings_widget = new SettingsWidget(this);
    this->addWidget(settings_widget);
}

void MiddleStack::init_signal_slots()
{
    connect(contact_list_widget, &ContactListWidget::selected_contact_item,
            chat_list_widget, &ChatListWidget::on_contact_item_selected);

    connect(contact_list_widget, &ContactListWidget::selected_contact_item,
            this, &MiddleStack::on_contact_item_selected);
}

void MiddleStack::on_contact_item_selected(const Contact& contact)
{
    setCurrentIndex(CHAT_LIST_INDEX);
}

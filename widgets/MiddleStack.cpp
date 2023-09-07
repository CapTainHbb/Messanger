#include "MiddleStack.hpp"

MiddleStack::MiddleStack(ContactProxyModel *_contact_proxy_model, ChatListProxyModel *_chat_list_proxy_model, QWidget *parent)
: QStackedWidget(parent),
contact_proxy_model{ _contact_proxy_model }, 
chat_list_proxy_model{ _chat_list_proxy_model }
{
    init_chat_list_widget();
    init_contact_list_widget();
    init_signal_slots();
    setCurrentIndex(0);
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
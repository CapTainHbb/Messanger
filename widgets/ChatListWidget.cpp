#include "ChatListWidget.hpp"

ChatListWidget::ChatListWidget(ChatListProxyModel *_model, QWidget *parent)
    : model(_model), QWidget(parent)
{
    init_layout();
    init_chat_list();
}

ChatListWidget::~ChatListWidget()
{
}

void ChatListWidget::init_layout()
{
    vbox = new QVBoxLayout(this);
}

void ChatListWidget::on_contact_item_selected(const Contact& contact)
{
    set_selected_contact_item(contact);
    return;
}

void ChatListWidget::set_selected_contact_item(const Contact& contact)
{
    selected_contact_item = contact;
}

void ChatListWidget::init_chat_list()
{
    chat_list = new QListView(this);
    chat_list->setObjectName("chat_list");
    chat_list->setContextMenuPolicy(Qt::ActionsContextMenu);
    chat_list->setModel(model);
    chat_list->setStyleSheet("color: blue; background-color: cyan");
    
    connect(chat_list, &QListView::clicked,
            this, &ChatListWidget::on_item_clicked);

    delete_chat = new QAction("delete chat", this);
    connect(delete_chat, &QAction::triggered, this, &ChatListWidget::on_delete_item_clicked);
    chat_list->addAction(delete_chat);

    vbox->addWidget(chat_list);
}

void ChatListWidget::on_delete_item_clicked(bool checked)
{
    auto model_index{ chat_list->currentIndex() };
    auto source_model_index{ model->get_source_model_index(model_index) };
    delete_item(source_model_index);
    emit chat_item_deleted(source_model_index);
}

void ChatListWidget::delete_item(const QModelIndex& model_index)
{
    model->source_model->delete_contact_chats(model_index);
}

void ChatListWidget::on_item_clicked(const QModelIndex& model_index)
{
    auto source_model_index{ model->get_source_model_index(model_index) };
    emit chat_item_clicked(source_model_index);
}

size_t ChatListWidget::get_number_of_all_chats() const
{
    return chat_list->children().count();
}

bool ChatListWidget::chat_exists(const Contact& contact)
{
    return model->source_model->contact_has_chat(contact);
}

QRect ChatListWidget::get_item_rect(const Contact& contact)
{
    auto proxy_model_index{ model->get_proxy_model_index(contact) };

    return chat_list->visualRect(proxy_model_index);
} 
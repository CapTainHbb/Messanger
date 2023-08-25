#include "ActiveChat.hpp"

ActiveChat::ActiveChat(QWidget *parent)
{
    setParent(parent);
    setObjectName("active_chat_widget");

    active_chat_vbox = new QVBoxLayout(this);
    active_chat_vbox->setObjectName("active_chat_vbox");

    init_active_chat_messages();
    init_send_message_textbox();
    init_send_message_button();
}

ActiveChat::~ActiveChat()
{
}


void ActiveChat::init_active_chat_messages()
{
    active_chat_messages = new QTextBrowser(this);
    active_chat_messages->setObjectName("active_chat_messages");

    active_chat_messages_vbox = new QVBoxLayout(active_chat_messages);
    active_chat_messages_vbox->setObjectName("active_chat_messages_vbox");

    active_chat_vbox->addWidget(active_chat_messages);
}

void ActiveChat::init_send_message_textbox()
{
    send_message_textbox = new QTextEdit(this);
    send_message_textbox->setObjectName("send_message_textbox");

    active_chat_vbox->addWidget(send_message_textbox);
}

void ActiveChat::init_send_message_button()
{
    send_message_pushbutton = new QPushButton(this);
    send_message_pushbutton->setObjectName("send_message_pushbutton");
    send_message_pushbutton->setText("send message");
    active_chat_vbox->addWidget(send_message_pushbutton);

    connect(send_message_pushbutton, &QPushButton::clicked, this, &ActiveChat::on_send_message_clicked);
}

void ActiveChat::on_send_message_clicked()
{
    QLabel *new_message{ nullptr };
    new_message = new QLabel();
    new_message->setText(send_message_textbox->toPlainText());

    active_chat_messages_vbox->addWidget(new_message);

    auto current_messages{ active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QLabel*>>() };
    current_messages.append(new_message);

    QVariant new_chat_messages;
    new_chat_messages.setValue(current_messages);
    
    active_chat->setData(Qt::ItemDataRole::UserRole, new_chat_messages);

    send_message_textbox->clear();
}


QLabel *ActiveChat::get_last_message_on_active_chat() const 
{
    if(nullptr == active_chat)
    {
        throw std::invalid_argument("active chat is nullptr");
    }

    auto messages{  active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QLabel*>>() };
    return messages.last();
}

size_t ActiveChat::get_number_of_messages_in_active_chat() const
{
    auto chat_messages{ active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QLabel*>>() };

    return chat_messages.count();
}

QString ActiveChat::get_active_chat_name() const
{
    return active_chat->text();
}

void ActiveChat::set_active_chat(QListWidgetItem *_active_chat)
{
    active_chat = _active_chat;
    clear_active_chat_messages();
}

void ActiveChat::clear_active_chat_messages()
{
    if(0 == active_chat_messages_vbox->count())
    {
        return;
    }

    while (QLayoutItem* item = active_chat_messages_vbox->takeAt(0))
    {
        active_chat_messages_vbox->removeWidget(item->widget());
        active_chat_messages_vbox->removeItem(item);
    }
}


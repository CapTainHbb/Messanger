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
    active_chat_messages_frame = new QFrame(this);
    active_chat_messages_frame->setObjectName("active_chat_messages_frame");
    active_chat_messages_frame->setFrameStyle(QFrame::Box | QFrame::Plain);

    active_chat_messages_vbox = new QVBoxLayout(active_chat_messages_frame);
    active_chat_messages_vbox->setObjectName("active_chat_messages_vbox");

    active_chat_vbox->addWidget(active_chat_messages_frame);
}

void ActiveChat::init_send_message_textbox()
{
    send_message_textbox = new QTextEdit(this);
    send_message_textbox->setObjectName("send_message_textbox");
    send_message_textbox->setHidden(true);

    active_chat_vbox->addWidget(send_message_textbox);
}

void ActiveChat::init_send_message_button()
{
    send_message_pushbutton = new QPushButton(this);
    send_message_pushbutton->setObjectName("send_message_pushbutton");
    send_message_pushbutton->setText("send message");
    send_message_pushbutton->setHidden(true);
    active_chat_vbox->addWidget(send_message_pushbutton);

    connect(send_message_pushbutton, &QPushButton::clicked, this, &ActiveChat::on_send_message_clicked);
}

void ActiveChat::on_send_message_clicked()
{
    QString message_text{ send_message_textbox->toPlainText() };
    
    create_chat_message_widget(message_text);
    add_message_to_active_chat_model(message_text);

    send_message_textbox->clear();
}

void ActiveChat::add_message_to_active_chat_model(QString message_text)
{
    QString new_message_text{ message_text };
    auto current_messages{ active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QString>>() };
    current_messages.append(new_message_text);

    QVariant new_chat_messages;
    new_chat_messages.setValue(current_messages);
    
    active_chat->setData(Qt::ItemDataRole::UserRole, new_chat_messages);
}

void ActiveChat::create_chat_message_widget(QString message_text)
{
    QLabel *message_qlabel{ nullptr };
    message_qlabel = new QLabel(active_chat_messages_frame);
    message_qlabel->setText(message_text);
    active_chat_messages_vbox->addWidget(message_qlabel);
}

QString ActiveChat::get_last_message_on_active_chat() const 
{
    if(nullptr == active_chat)
    {
        throw std::invalid_argument("active chat is nullptr");
    }

    auto messages{  active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QString>>() };
    return messages.last();
}


size_t ActiveChat::get_number_of_messages_in_active_chat() const
{
    return get_active_chat_messages_text().count();
}

QString ActiveChat::get_active_chat_name() const
{
    return active_chat->text();
}

QList<QString>  ActiveChat::get_active_chat_messages_text() const
{
    return active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QString>>();
}


QListWidgetItem *ActiveChat::get_active_chat() const
{
    return active_chat;
}

void ActiveChat::set_active_chat(QListWidgetItem *_active_chat)
{
    active_chat = _active_chat;
    clear_active_chat_messages_layout();
    reconstruct_active_chat_messages_layout();
    send_message_textbox->setHidden(false);
    send_message_pushbutton->setHidden(false);
}


void ActiveChat::clear_active_chat_messages_layout()
{
    clearLayout(active_chat_messages_vbox);
}

void ActiveChat::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }        
        if (item->widget())
        {
            delete item->widget();
        }
    }
}

void ActiveChat::reconstruct_active_chat_messages_layout()
{
    auto active_chat_messages_text{ active_chat->data(Qt::ItemDataRole::UserRole).value<QList<QString>>() };
    for(auto& chat_message_text : active_chat_messages_text)
    {
        create_chat_message_widget(chat_message_text);
    }
}

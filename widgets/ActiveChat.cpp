#include "ActiveChat.hpp"

ActiveChat::ActiveChat(GeneralModel *_model, QWidget *parent)
 :model{ _model }
{
    setParent(parent);
    setObjectName("active_chat_widget");

    vbox = new QVBoxLayout(this);
    vbox->setObjectName("vbox");

    init_chat_messages();
    init_send_message_textbox();
    init_send_message_button();
}

ActiveChat::~ActiveChat()
{
}


void ActiveChat::on_contact_item_selected(const Contact &contact)
{
    reinit(contact);
}

void ActiveChat::on_chat_item_clicked(const QModelIndex& model_index)
{
    reinit(model->get_contact(model_index));
}

void ActiveChat::on_chat_item_deleted(const QModelIndex& model_index)
{
    auto updated_contact{ model->get_contact(model_index) };
    if(updated_contact != active_contact)
    {
        return;
    }
    set_chat_status(Status::EMPTY_CHAT);
}

void ActiveChat::init_chat_messages()
{
    chat_messages_frame = new QFrame(this);
    chat_messages_frame->setObjectName("chat_messages_frame");
    chat_messages_frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    chat_messages_frame->setHidden(false);

    chat_messages_vbox = new QVBoxLayout(chat_messages_frame);
    chat_messages_vbox->setObjectName("chat_messages_vbox");

    vbox->addWidget(chat_messages_frame);
}

void ActiveChat::init_send_message_textbox()
{
    send_message_textbox = new QTextEdit(this);
    send_message_textbox->setObjectName("send_message_textbox");
    send_message_textbox->setHidden(true);

    vbox->addWidget(send_message_textbox);
}

void ActiveChat::init_send_message_button()
{
    send_message_pushbutton = new QPushButton(this);
    send_message_pushbutton->setObjectName("send_message_pushbutton");
    send_message_pushbutton->setText("send message");
    send_message_pushbutton->setHidden(true);
    vbox->addWidget(send_message_pushbutton);

    connect(send_message_pushbutton, &QPushButton::clicked,
            this, &ActiveChat::on_send_message_clicked);
}

void ActiveChat::on_send_message_clicked()
{
    QString message_text{ send_message_textbox->toPlainText() };
    
    create_chat_message_widget(message_text);

    active_contact.add_chat(message_text);
    model->update_contact(active_contact);

    send_message_textbox->clear();
}

void ActiveChat::create_chat_message_widget(QString message_text)
{
    QLabel *message_qlabel{ nullptr };
    message_qlabel = new QLabel(chat_messages_frame);
    message_qlabel->setText(message_text);
    messages.append(message_qlabel);
    chat_messages_vbox->addWidget(message_qlabel);
}


QString ActiveChat::get_chat_name() const
{
    return active_contact.get_name();
}

QList<QString> ActiveChat::get_chat_messages_text() const
{
    QList<QString> chat_messages_text;
    for (const auto message_widget : messages)
    {
        chat_messages_text.append(message_widget->text());
    }
    return chat_messages_text;
}

QString ActiveChat::get_last_message() const
{
    auto number_of_messages_in_active_chat{ get_number_of_messages() };
    if(0 == number_of_messages_in_active_chat)
    {
        return "";
    }

    return messages.last()->text();
}

size_t ActiveChat::get_number_of_messages() const
{
    return messages.count();
}


void ActiveChat::reinit(const Contact &contact)
{
    set_active_contact(contact);
    clear_chat_messages_layout();
    fill_chat_messages_layout();
    set_chat_status(Status::CHAT_WITH_MESSAGES);
}

void ActiveChat::set_active_contact(const Contact &contact)
{
    active_contact = contact;
}

void ActiveChat::clear_chat_messages_layout()
{
    clear_layout(chat_messages_vbox);
    messages.clear();
}

void ActiveChat::clear_layout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clear_layout(item->layout());
            delete item->layout();
        }        
        if (item->widget())
        {
            delete item->widget();
        }
    }
}

void ActiveChat::fill_chat_messages_layout()
{
    for(auto& chat : active_contact.get_chats())
    {
        create_chat_message_widget(chat.get_chat_text());
    }
}



void ActiveChat::set_chat_status(Status new_status)
{   
    status = new_status;

    switch (status)
    {
    case Status::START_NEW_CHAT:
    case Status::CHAT_WITH_MESSAGES:
    {
        chat_messages_frame->setHidden(false);
        send_message_pushbutton->setHidden(false);
        send_message_textbox->setHidden(false);
        break;
    }
    case Status::EMPTY_CHAT:
    {
        set_active_contact(Contact());
        clear_chat_messages_layout();
        chat_messages_frame->setHidden(false);
        send_message_pushbutton->setHidden(true);
        send_message_textbox->setHidden(true);
        break;
    }
    default:
        break;
    }
    
}

ActiveChat::Status ActiveChat::get_chat_status() const
{
    return status;
}
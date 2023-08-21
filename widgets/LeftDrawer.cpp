#include "LeftDrawer.hpp"


LeftDrawer::LeftDrawer(ActiveChat *widget, QWidget *parent)
{
    setParent(parent);
    setObjectName("left_drawer_widget");

    set_active_chat_widget(widget);

    left_drawer_vbox = new QVBoxLayout(this);
    left_drawer_vbox->setObjectName("left_drawer_vbox");

    init_list_of_chats();
    init_new_chat_button();
}

void LeftDrawer::set_active_chat_widget(ActiveChat *widget)
{
    active_chat_widget = widget;
}

void LeftDrawer::init_list_of_chats()
{
    list_of_chats = new QListWidget(this);
    list_of_chats->setObjectName("list_of_chats");
    left_drawer_vbox->addWidget(list_of_chats);
    connect(list_of_chats, &QListWidget::itemClicked,
            this, &LeftDrawer::on_chat_item_clicked);
}

void LeftDrawer::on_chat_item_clicked(QListWidgetItem* item)
{

}

void LeftDrawer::init_new_chat_button()
{
    new_chat_button = new QPushButton(this);
    new_chat_button->setObjectName("new_chat_button");
    new_chat_button->setText("new chat");
    connect(new_chat_button, &QPushButton::clicked, this, &LeftDrawer::on_new_chat_clicked);
    left_drawer_vbox->addWidget(new_chat_button);
}

void LeftDrawer::on_new_chat_clicked()
{
    static auto chat_count{ 0 };
    chat_count++;

    QString chat_name{ QString::number(chat_count) };

    QListWidgetItem *new_chat_item{ new QListWidgetItem(chat_name, list_of_chats) };
    QVariant chat_messages(QList<QLabel*>());
    new_chat_item->setData(Qt::ItemDataRole::UserRole, chat_messages);
    
    list_of_chats->addItem(new_chat_item);

    active_chat_widget->set_active_chat(new_chat_item);
}

size_t LeftDrawer::get_number_of_all_chats() const
{
    return list_of_chats->count();
}

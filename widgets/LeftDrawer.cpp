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
    list_of_chats->setContextMenuPolicy(Qt::ActionsContextMenu);

    delete_chat = new QAction("delete chat", this);
    connect(delete_chat, &QAction::triggered, this, &LeftDrawer::on_delete_chat_clicked);
    list_of_chats->addAction(delete_chat);

    left_drawer_vbox->addWidget(list_of_chats);
    connect(list_of_chats, &QListWidget::itemClicked,
            this, &LeftDrawer::on_chat_item_clicked);
}

void LeftDrawer::on_delete_chat_clicked(bool checked)
{
    delete_chat_item(list_of_chats->currentItem());

    if(0 == list_of_chats->count())
    {
        active_chat_widget->set_active_chat(nullptr);
        return;
    }

    get_first_chat_item()->setSelected(true);
    active_chat_widget->set_active_chat(get_first_chat_item());
}

void LeftDrawer::delete_chat_item(QListWidgetItem *item)
{
    list_of_chats->takeItem(list_of_chats->row(item));
}

void LeftDrawer::on_chat_item_clicked(QListWidgetItem *item)
{
    active_chat_widget->set_active_chat(item);
}

QListWidgetItem *LeftDrawer::get_first_chat_item()
{
    return list_of_chats->itemAt(0, 0);
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
    QVariant chat_messages(QList<QString>());
    new_chat_item->setData(Qt::ItemDataRole::UserRole, chat_messages);

    active_chat_widget->set_active_chat(new_chat_item);

    new_chat_item->setSelected(true);
}

size_t LeftDrawer::get_number_of_all_chats() const
{
    return list_of_chats->count();
}


QRect LeftDrawer::get_chat_item_rect_by_name(QString chat_name)
{
    auto chat_item{ find_chat_item_by_name(chat_name) };
    auto rect{ get_chat_item_rect(chat_item) };
    return rect;
} 

QListWidgetItem* LeftDrawer::find_chat_item_by_name(QString chat_name)
{
    auto found_chats{ list_of_chats->findItems(chat_name, Qt::MatchExactly) };

    if(0 == found_chats.count())
    {
        throw std::invalid_argument("chat nout found-> " + chat_name.toStdString() );
    }

    return found_chats.at(0);
}

QRect LeftDrawer::get_chat_item_rect(QListWidgetItem *item)
{
    return list_of_chats->visualItemRect(item);
}

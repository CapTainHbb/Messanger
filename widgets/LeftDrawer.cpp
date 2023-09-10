#include "LeftDrawer.hpp"


LeftDrawer::LeftDrawer(ActiveChat *widget, QWidget *parent)
{
    setParent(parent);
    setObjectName("left_drawer_widget");

    set_active_chat_widget(widget);

    init_layout();

    init_contact_list_button();
    init_chat_list_button();
    init_settings_button();
    set_all_buttons_initial_checkablity();
}

void LeftDrawer::set_active_chat_widget(ActiveChat *widget)
{
    active_chat_widget = widget;
}

void LeftDrawer::init_layout()
{
    left_drawer_vbox = new QVBoxLayout(this);
    left_drawer_vbox->setObjectName("left_drawer_vbox");
}

void LeftDrawer::init_contact_list_button()
{
    contact_list_button = new QPushButton(this);
    contact_list_button->setObjectName("contact_list_button");
    contact_list_button->setText("contact list");
    contact_list_button->setCheckable(true);

    connect(contact_list_button, &QPushButton::clicked, this, &LeftDrawer::on_contact_list_button_clicked);

    left_drawer_vbox->addWidget(contact_list_button);
}

void LeftDrawer::on_contact_list_button_clicked()
{
    emit set_middle_stack_widget_index(CONTACT_LIST_INDEX);
    contact_list_button->setChecked(true);
    chat_list_button->setChecked(false);
    settings_button->setChecked(false);
}

void LeftDrawer::on_contact_item_selected(const Contact &contact)
{
    contact_list_button->setChecked(false);
    chat_list_button->setChecked(true);
}

void LeftDrawer::init_chat_list_button()
{
    chat_list_button = new QPushButton(this);
    chat_list_button->setObjectName("chat_list_button");
    chat_list_button->setText("chat list");
    chat_list_button->setCheckable(true);

    connect(chat_list_button, &QPushButton::clicked, this, &LeftDrawer::on_chat_list_button_clicked);

    left_drawer_vbox->addWidget(chat_list_button);
}

void LeftDrawer::on_chat_list_button_clicked()
{
    emit set_middle_stack_widget_index(CHAT_LIST_INDEX);
    chat_list_button->setChecked(true);
    contact_list_button->setChecked(false);
    settings_button->setChecked(false);
}

void LeftDrawer::init_settings_button()
{
    settings_button = new QPushButton(this);
    settings_button->setObjectName("settings_button");
    settings_button->setText("settings");
    settings_button->setCheckable(true);

    connect(settings_button, &QPushButton::clicked, this, &LeftDrawer::on_settings_button_clicked);

    left_drawer_vbox->addWidget(settings_button);
}

void LeftDrawer::on_settings_button_clicked()
{
    emit set_middle_stack_widget_index(SETTINGS_INDEX);
    settings_button->setChecked(true);
    contact_list_button->setChecked(false);
    chat_list_button->setChecked(false);
}

void LeftDrawer::set_all_buttons_initial_checkablity()
{
    chat_list_button->setChecked(true);
    contact_list_button->setChecked(false);
    settings_button->setChecked(false);
}
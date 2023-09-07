#include "LeftDrawer.hpp"


LeftDrawer::LeftDrawer(ActiveChat *widget, QWidget *parent)
{
    setParent(parent);
    setObjectName("left_drawer_widget");

    set_active_chat_widget(widget);

    left_drawer_vbox = new QVBoxLayout(this);
    left_drawer_vbox->setObjectName("left_drawer_vbox");

    init_contact_list_button();

}

void LeftDrawer::set_active_chat_widget(ActiveChat *widget)
{
    active_chat_widget = widget;
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
}

void LeftDrawer::on_contact_item_selected(const Contact &contact)
{
    contact_list_button->setChecked(false);
}



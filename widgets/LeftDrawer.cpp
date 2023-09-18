#include "LeftDrawer.hpp"


LeftDrawer::LeftDrawer(ActiveChat *active_chat_wiget, QWidget *parent)
{
    setParent(parent);
    setObjectName("left_drawer_widget");

    set_active_chat_widget(active_chat_wiget);

    init_layout();

    init_contact_list_button();
    init_add_contact_button();
    init_chat_list_button();
    init_settings_button();
    set_all_buttons_initial_checkability();
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
    uncheck_all_other_buttons(CONTACT_LIST_INDEX);
}

void LeftDrawer::on_contact_item_selected(const Contact &contact)
{
    uncheck_all_other_buttons(CHAT_LIST_INDEX);
}

void LeftDrawer::init_add_contact_button()
{
    add_contact_button = new QPushButton(this);
    add_contact_button->setObjectName("add_contact_button_in_left_drawer");
    add_contact_button->setText("add contact");
    add_contact_button->setCheckable(true);

    connect(add_contact_button, &QPushButton::clicked,
            this, &LeftDrawer::on_add_contact_clicked);

    left_drawer_vbox->addWidget(add_contact_button);
}

void LeftDrawer::on_add_contact_clicked()
{
    emit set_middle_stack_widget_index(ADD_CONTACT_INDEX);
    uncheck_all_other_buttons(ADD_CONTACT_INDEX);
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
    uncheck_all_other_buttons(CHAT_LIST_INDEX);
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
    uncheck_all_other_buttons(SETTINGS_INDEX);
}

void LeftDrawer::set_all_buttons_initial_checkability()
{
    uncheck_all_other_buttons(CHAT_LIST_INDEX);
}

void LeftDrawer::uncheck_all_other_buttons(int current_middle_stack_index)
{
    switch (current_middle_stack_index)
    {
        case CHAT_LIST_INDEX:
        {
            chat_list_button->setChecked(true);
            contact_list_button->setChecked(false);
            add_contact_button->setChecked(false);
            settings_button->setChecked(false);
            break;
        }
        case CONTACT_LIST_INDEX:
        {
            chat_list_button->setChecked(false);
            contact_list_button->setChecked(true);
            add_contact_button->setChecked(false);
            settings_button->setChecked(false);
            break;
        }
        case ADD_CONTACT_INDEX:
        {
            chat_list_button->setChecked(false);
            contact_list_button->setChecked(false);
            add_contact_button->setChecked(true);
            settings_button->setChecked(false);
            break;
        }
        case SETTINGS_INDEX:
        {
            chat_list_button->setChecked(false);
            contact_list_button->setChecked(false);
            add_contact_button->setChecked(false);
            settings_button->setChecked(true);
            break;
        }

        default:
        {
            chat_list_button->setChecked(false);
            contact_list_button->setChecked(false);
            add_contact_button->setChecked(false);
            settings_button->setChecked(false);
            break;
        }

    }
}
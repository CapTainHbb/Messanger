#include <SettingsWidget.hpp>

SettingsWidget::SettingsWidget(QWidget *parent)
: QWidget(parent)
{
    init_layout();
    init_username_widget();
    init_password_widget();
    init_domain_name_widget();
    init_connect_to_server_widget();
//    init_connection_result_widget();
    connect_signals_to_slots();
}

void SettingsWidget::init_layout()
{
    layout = new QFormLayout(this);
    layout->setObjectName("settings_widget_layout");
}

void SettingsWidget::init_username_widget()
{
    username_text_input = new QLineEdit();
    username_text_input->setObjectName("username_text_input");
    layout->addRow("Username", username_text_input);
}

void SettingsWidget::init_password_widget()
{
    password_text_input = new QLineEdit();
    password_text_input->setObjectName("password_text_input");
    layout->addRow("Password", password_text_input);
}

void SettingsWidget::init_domain_name_widget()
{
    domain_name_text_input = new QLineEdit();
    domain_name_text_input->setObjectName("domain_name_text_input");
    layout->addRow("Domain name", domain_name_text_input);
}

void SettingsWidget::init_connect_to_server_widget()
{
    connect_to_server_button = new QPushButton(this);
    connect_to_server_button->setObjectName("connect_to_server_button");
    connect_to_server_button->setText("connect to server");
    layout->addRow(connect_to_server_button);

    connect(connect_to_server_button, &QPushButton::clicked,
            this, &SettingsWidget::on_click_connect_to_server_button);
}

void SettingsWidget::on_click_connect_to_server_button()
{
    emit request_to_connect_server(username_text_input->text(),
                                   password_text_input->text(),
                                   domain_name_text_input->text());
}

void SettingsWidget::init_connection_result_widget()
{
    connection_result_label = new QLabel(this);
    connection_result_label->setObjectName("connection_result_label");
    connection_result_label->setText("No connection at the moment!");
    layout->addRow(connection_result_label);
}

void SettingsWidget::connect_signals_to_slots()
{

}

void SettingsWidget::on_connection_result_received(QXmppClient::State status)
{
    last_connection_result = status;
}

QXmppClient::State SettingsWidget::get_last_connection_result() const
{
    return last_connection_result;
}



#include <SettingsWidget.hpp>

SettingsWidget::SettingsWidget(QWidget *parent)
: QWidget(parent)
{
    init_layout();
    init_server_ip_adderss_widget();
    init_connect_to_server_widget();
    init_connection_result_widget();
}

SettingsWidget::~SettingsWidget()
{
}

void SettingsWidget::init_layout()
{
    vbox = new QVBoxLayout(this);
    vbox->setObjectName("settings_widget_vbox");
}

void SettingsWidget::init_server_ip_adderss_widget()
{
    ip_address_text_input = new QLineEdit();
    ip_address_text_input->setObjectName("ip_address_text_input");
    ip_address_text_input->setInputMask("000.000.000.000;_");
    vbox->addWidget(ip_address_text_input);
}

void SettingsWidget::init_connect_to_server_widget()
{
    connect_to_server_button = new QPushButton(this);
    connect_to_server_button->setObjectName("connect_to_server_button");
    connect_to_server_button->setText("connect to server");
    vbox->addWidget(connect_to_server_button);

    connect(connect_to_server_button, &QPushButton::clicked,
            this, &SettingsWidget::on_click_connect_to_server_button);
}

void SettingsWidget::on_click_connect_to_server_button()
{
    connection_result_label->setText(ip_address_text_input->text() + " is reachable");
}

void SettingsWidget::init_connection_result_widget()
{
    connection_result_label = new QLabel(this);
    connection_result_label->setObjectName("connection_result_label");
    connection_result_label->setText("No connection at the moment!");
    vbox->addWidget(connection_result_label);
}

#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

class SettingsWidget : public QWidget
{
public:
    SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();
    
    QVBoxLayout *vbox{ nullptr };
    void init_layout();

    QLabel *server_address_label{ nullptr };
    QLineEdit *ip_address_text_input{ nullptr };
    void init_server_ip_adderss_widget();

    QPushButton *connect_to_server_button{ nullptr };
    void init_connect_to_server_widget();

    QLabel *connection_result_label{ nullptr };
    void init_connection_result_widget();

public slots:
    void on_click_connect_to_server_button();
    
};


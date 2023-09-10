#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMenu>
#include <stdexcept>
#include <iostream>

#include "ActiveChat.hpp"
#include "MiddleStack.hpp"

class LeftDrawer : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *left_drawer_vbox{ nullptr };
    void init_layout();

public:
    LeftDrawer(ActiveChat* wiget, QWidget *parent = nullptr);
    ~LeftDrawer() = default;

    QPushButton *contact_list_button{ nullptr };
    void init_contact_list_button();
    void on_contact_list_button_clicked();

    QPushButton *chat_list_button{ nullptr };
    void init_chat_list_button();
    void on_chat_list_button_clicked();

    QPushButton *settings_button{ nullptr };
    void init_settings_button();
    void on_settings_button_clicked();

    ActiveChat *active_chat_widget{ nullptr };
    void set_active_chat_widget(ActiveChat *widget);

    void set_all_buttons_initial_checkablity();

signals:
    void set_middle_stack_widget_index(int middle_index_widget_index);

public slots:
    void on_contact_item_selected(const Contact &index);
};

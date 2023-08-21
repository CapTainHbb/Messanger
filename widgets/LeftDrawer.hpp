#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include "ActiveChat.hpp"

class LeftDrawer : public QWidget
{
private:
    QVBoxLayout *left_drawer_vbox{ nullptr };

public:
    LeftDrawer(ActiveChat* wiget, QWidget *parent = nullptr);
    ~LeftDrawer() = default;

    ActiveChat *active_chat_widget{ nullptr };
    void set_active_chat_widget(ActiveChat *widget);

    QListWidget *list_of_chats{ nullptr };
    void init_list_of_chats();

    QPushButton *new_chat_button{ nullptr };
    void init_new_chat_button();
    
    size_t get_number_of_all_chats() const;


public slots:
    void on_chat_item_clicked(QListWidgetItem* item);   
    void on_new_chat_clicked();
};

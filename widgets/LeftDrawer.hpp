#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMenu>
#include <stdexcept>
#include <iostream>

#include "ActiveChat.hpp"

class LeftDrawer : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *left_drawer_vbox{ nullptr };

public:
    LeftDrawer(ActiveChat* wiget, QWidget *parent = nullptr);
    ~LeftDrawer() = default;

    ActiveChat *active_chat_widget{ nullptr };
    void set_active_chat_widget(ActiveChat *widget);

    QListWidget *list_of_chats{ nullptr };
    void init_list_of_chats();

    void on_delete_chat_clicked(bool checked);
    void delete_chat_item(QListWidgetItem *item);

    QPushButton *new_chat_button{ nullptr };
    void init_new_chat_button();
    
    size_t get_number_of_all_chats() const;
    QListWidgetItem *get_first_chat_item();

    QRect get_chat_item_rect_by_name(QString chat_name);   
    QListWidgetItem* find_chat_item_by_name(QString chat_name); 
    QRect get_chat_item_rect(QListWidgetItem *item);

    QAction *delete_chat{ nullptr };


public slots:
    void on_chat_item_clicked(QListWidgetItem* item);   
    void on_new_chat_clicked();
};

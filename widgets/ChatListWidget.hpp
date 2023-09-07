#pragma once

#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVariant>

#include <Contact.hpp>
#include <ChatListProxyModel.hpp>
#include <QListView>

class ChatListWidget : public QWidget
{
    Q_OBJECT
private:
    ChatListProxyModel *model{ nullptr };

public:
    ChatListWidget(ChatListProxyModel *model, QWidget *parent = nullptr);
    ~ChatListWidget();

    QVBoxLayout *vbox{ nullptr };
    void init_layout();

    Contact selected_contact_item{ };
    void set_selected_contact_item(const Contact& contact);

    QListView *chat_list{ nullptr };
    void init_chat_list();

    QAction *delete_chat{ nullptr };
    void on_delete_item_clicked(bool checked);
    void delete_item(const QModelIndex& model_index);

    size_t get_number_of_all_chats() const;

    bool chat_exists(const Contact& contact);
    QRect get_item_rect(const Contact& contact);   

signals:
    void chat_item_clicked(const QModelIndex model_index);
    void chat_item_deleted(const QModelIndex& model_index);

public slots:
    void on_item_clicked(const QModelIndex& model_index);   
    void on_contact_item_selected(const Contact& contact);
};
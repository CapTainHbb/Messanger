#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>

#include <ContactProxyModel.hpp>
#include <ChatListProxyModel.hpp>

#include <ContactListWidget.hpp>
#include <AddContactWidget.hpp>
#include <ChatListWidget.hpp>
#include <SettingsWidget.hpp>
#include <XmppClient.hpp>

struct MiddleStackIndex
{
    #define CHAT_LIST_INDEX       0
    #define CONTACT_LIST_INDEX    1
    #define ADD_CONTACT_INDEX     2
    #define SETTINGS_INDEX        3
};

class MiddleStack : public QStackedWidget
{
    Q_OBJECT
private:
    ContactProxyModel *contact_proxy_model{ nullptr };
    ChatListProxyModel *chat_list_proxy_model{ nullptr };

public:
    MiddleStack(ContactProxyModel *contact_proxy_model,
                ChatListProxyModel *chat_list_proxy_model,
                QWidget *parent = nullptr);
    ~MiddleStack();

    ContactListWidget *contact_list_widget{ nullptr };
    void init_contact_list_widget();

    AddContactWidget *add_contact_widget{ nullptr };
    void init_add_contact_widget();

    ChatListWidget *chat_list_widget{ nullptr };
    void init_chat_list_widget();

    SettingsWidget *settings_widget{ nullptr };
    void init_settings_widget();

    void init_signal_slots();

public slots:
    void on_contact_item_selected(const Contact &contact);
};


#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QListWidgetItem>
#include <QVariant>
#include <QFrame>

#include <GeneralModel.hpp>
#include <Contact.hpp>

class ActiveChat : public  QWidget
{
private:
    GeneralModel *model{ nullptr };
    

public:
    ActiveChat(GeneralModel* model, QWidget *parent = nullptr);
    ~ActiveChat();

    enum Status
    {
        START_NEW_CHAT,
        CHAT_WITH_MESSAGES,
        EMPTY_CHAT
    } status;

    void set_chat_status(Status new_status);
    Status get_chat_status() const;


    QVBoxLayout *vbox{ nullptr };

    QFrame *chat_messages_frame{ nullptr };
    QVBoxLayout *chat_messages_vbox{ nullptr };
    void init_chat_messages();

    QList<QLabel*> messages;
    QString get_last_message() const;
    size_t get_number_of_messages() const;

    Contact active_contact{ };
    void set_active_contact(const Contact &contact);

    QTextEdit *send_message_textbox{ nullptr };
    void init_send_message_textbox();

    void create_chat_message_widget(QString message_text);
    void add_message_to_active_chat_model(QString message_text);
    void set_chat_list_to_selected_contact_item(QList<QString> chat_list);

    QPushButton *send_message_pushbutton{ nullptr };
    void init_send_message_button();

    QString get_chat_name() const;    
    QList<QString> get_chat_messages_text() const;

    void reinit(const Contact &contact);
    void clear_chat_messages_layout();
    void clear_layout(QLayout *layout);
    void fill_chat_messages_layout();


public slots:
    void on_send_message_clicked();
    void on_contact_item_selected(const Contact &contact);
    void on_chat_item_clicked(const QModelIndex& model_index);
    void on_chat_item_deleted(const QModelIndex& model_index);
};



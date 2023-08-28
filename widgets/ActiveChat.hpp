#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QListWidgetItem>
#include <QVariant>
#include <QFrame>

class ActiveChat : public  QWidget
{
private:
    /* data */
    

public:
    ActiveChat(QWidget *parent = nullptr);
    ~ActiveChat();

    QVBoxLayout *active_chat_vbox{ nullptr };

    QFrame *active_chat_messages_frame{ nullptr };
    QVBoxLayout *active_chat_messages_vbox{ nullptr };
    void init_active_chat_messages();
    
    void clear_active_chat_messages_layout();
    QString get_last_message_on_active_chat() const;
    size_t get_number_of_messages_in_active_chat() const;

    void reconstruct_active_chat_messages_layout();

    QTextEdit *send_message_textbox{ nullptr };
    void init_send_message_textbox();

    void create_chat_message_widget(QString message_text);
    void add_message_to_active_chat_model(QString message_text);

    QPushButton *send_message_pushbutton{ nullptr };
    void init_send_message_button();

    QListWidgetItem *active_chat{ nullptr };
    QListWidgetItem *get_active_chat() const;
    void set_active_chat(QListWidgetItem *active_chat);

    QString get_active_chat_name() const;    
    QList<QString> get_active_chat_messages_text() const;

    void clear_layout(QLayout *layout);

public slots:
    void on_send_message_clicked();
};



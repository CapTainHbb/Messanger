#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QListWidgetItem>
#include <QVariant>

class ActiveChat : public  QWidget
{
private:
    /* data */
    

public:
    ActiveChat(QWidget *parent = nullptr);
    ~ActiveChat();

    QVBoxLayout *active_chat_vbox{ nullptr };

    QTextBrowser *active_chat_messages{ nullptr };
    QVBoxLayout *active_chat_messages_vbox{ nullptr };
    void init_active_chat_messages();
    void clear_active_chat_messages();
    QLabel *get_last_message_on_active_chat() const;
    // QList<QLabel *> get_all_messages_on_active_chat() const;
    size_t get_number_of_messages_in_active_chat() const;

    QTextEdit *send_message_textbox{ nullptr };
    void init_send_message_textbox();

    QPushButton *send_message_pushbutton{ nullptr };
    void init_send_message_button();

    QListWidgetItem *active_chat{ nullptr };
    void set_active_chat(QListWidgetItem *active_chat);

    QString get_active_chat_name() const;    

public slots:
    void on_send_message_clicked();
};



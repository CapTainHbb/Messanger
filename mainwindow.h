#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>

#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_widgets();

    QWidget *top_most_widget{ nullptr };
    QHBoxLayout *top_most_hbox{ nullptr };
    void init_top_most_widget();

    QWidget *left_drawer_widget{ nullptr };
    QVBoxLayout *left_drawer_vbox{ nullptr };
    QListWidget *list_of_chats{ nullptr };
    QPushButton *new_chat{ nullptr };
    void init_left_drawer_widget();

    QWidget *active_chat{ nullptr };
    QVBoxLayout *active_chat_vbox{ nullptr };
    QTextBrowser *active_chat_messages{ nullptr };
    QVBoxLayout *active_chat_messages_vbox{ nullptr };
    void init_active_chat_widget();
    void init_active_chat_messages();
    void clear_active_chat_messages();

    size_t get_number_of_messages_in_active_chat() const;

    QString active_chat_name{ };
    void set_active_chat_name(QString chat_name);
    QString get_active_chat_name() const;

    QMap<QString, QList<QLabel*>*> all_chats_messages;

    QTextEdit *send_message_textbox{ nullptr };
    QPushButton *send_message_pushbutton{ nullptr };
    void init_send_message_textbox();
    void init_send_message_button();

    QLabel *get_last_message_on_active_chat();

    size_t get_number_of_all_chats() const;

public slots:
    void on_send_message_clicked();
    void on_chat_item_clicked(QListWidgetItem* item);
    void on_new_chat_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

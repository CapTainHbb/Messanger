#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
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
    void init_top_most_widget();
    void init_left_drawer_widget();

    void init_active_chat_widget();
    void init_current_chat_messages();
    void init_send_message_textbox();
    void init_send_message_button();

    QWidget *top_most_widget{ nullptr };
    QHBoxLayout *top_most_hbox{ nullptr };

    QWidget *active_chat{ nullptr };
    QVBoxLayout *active_chat_vbox{ nullptr };

    QTextBrowser *current_messages{ nullptr };
    QVBoxLayout *current_messages_vbox{ nullptr };

    QTextEdit *send_message_textbox{ nullptr };
    QPushButton *send_message_pushbutton{ nullptr };

    QLabel *get_last_message_on_active_chat();

public slots:
    void on_send_message_clicked();

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H

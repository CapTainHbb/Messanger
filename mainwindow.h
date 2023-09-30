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

#include <GeneralModel.hpp>
#include <ContactProxyModel.hpp>
#include <ActiveChatProxyModel.hpp>
#include <ChatListProxyModel.hpp>
#include <LeftDrawer.hpp>
#include <MiddleStack.hpp>
#include <ActiveChat.hpp>
#include <XmppClient.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    XmppClient xmpp_client{ };

    GeneralModel *general_model{ nullptr };
    ContactProxyModel *contact_proxy_model{ nullptr };
    ChatListProxyModel *chat_list_proxy_model{ nullptr };
    void init_models();

    void init_widgets();

    QWidget *top_most_widget{ nullptr };
    QHBoxLayout *top_most_hbox{ nullptr };
    void init_top_most_widget();

    LeftDrawer *left_drawer_widget{ nullptr };
    void init_left_drawer_widget();

    MiddleStack *middle_stack_widget{ nullptr };
    void init_middle_stack_widget();

    ActiveChat *active_chat_widget{ nullptr };
    void init_active_chat_widget();

    void connect_signals_to_slots();

    void align_layout(); 

    void set_all_widgets_initial_visibility();   

public slots:
    void on_contact_item_selected(const Contact &contact);

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H

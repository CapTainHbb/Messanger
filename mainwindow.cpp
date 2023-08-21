#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init_widgets()
{
    init_top_most_widget();
    init_left_drawer_widget();
    init_active_chat_widget();
}


void MainWindow::init_top_most_widget()
{
    top_most_widget = new QWidget(this);
    top_most_widget->setObjectName("top_most_widget");
    setCentralWidget(top_most_widget);

    top_most_hbox = new QHBoxLayout(top_most_widget);
    top_most_hbox->setObjectName("top_most_hbox");
}

void MainWindow::init_left_drawer_widget()
{
    left_drawer_widget = new QWidget(top_most_widget);
    left_drawer_widget->setObjectName("left_drawer_widget");
    top_most_hbox->addWidget(left_drawer_widget);

    left_drawer_vbox = new QVBoxLayout(left_drawer_widget);
    left_drawer_vbox->setObjectName("left_drawer_vbox");

    list_of_chats = new QListWidget(left_drawer_widget);
    list_of_chats->setObjectName("list_of_chats");
    left_drawer_vbox->addWidget(list_of_chats);
    connect(list_of_chats, &QListWidget::itemClicked,
            this, &MainWindow::on_chat_item_clicked);

    new_chat = new QPushButton(top_most_widget);
    new_chat->setObjectName("new_chat");
    new_chat->setText("new chat");
    connect(new_chat, &QPushButton::clicked, this, &MainWindow::on_new_chat_clicked);
    left_drawer_vbox->addWidget(new_chat);
}

void MainWindow::on_chat_item_clicked(QListWidgetItem* item)
{

}

void MainWindow::on_new_chat_clicked()
{
    static auto chat_count{ 0 };
    chat_count++;

    QString chat_name{ QString::number(chat_count) };
    set_active_chat_name(chat_name);

    QListWidgetItem *new_chat_item{ new QListWidgetItem(chat_name, list_of_chats) };
    list_of_chats->addItem(new_chat_item);

    QList<QLabel*> *chat_messages = new QList<QLabel*>();
    all_chats_messages.insert(chat_name, chat_messages);

    clear_active_chat_messages();
}

void MainWindow::clear_active_chat_messages()
{
    if(0 == active_chat_messages_vbox->count())
    {
        return;
    }

    while (QLayoutItem* item = active_chat_messages_vbox->takeAt(0))
    {
        active_chat_messages_vbox->removeItem(item);
    }
}

size_t MainWindow::get_number_of_messages_in_active_chat() const
{
    active_chat_messages_vbox->children().count();
}

size_t MainWindow::get_number_of_all_chats() const
{
    return list_of_chats->count();
}


void MainWindow::set_active_chat_name(QString chat_name)
{
    active_chat_name = chat_name;
}

QString MainWindow::get_active_chat_name() const
{
    return active_chat_name;
}


void MainWindow::init_active_chat_widget()
{
    active_chat = new QWidget(top_most_widget);
    active_chat->setObjectName("active_chat");
    top_most_hbox->addWidget(active_chat);

    active_chat_vbox = new QVBoxLayout(active_chat);
    active_chat_vbox->setObjectName("active_chat_vbox");

    init_active_chat_messages();
    init_send_message_textbox();
    init_send_message_button();
}

void MainWindow::init_active_chat_messages()
{
    active_chat_messages = new QTextBrowser(active_chat);
    active_chat_messages->setObjectName("active_chat_messages");

    active_chat_messages_vbox = new QVBoxLayout(active_chat_messages);
    active_chat_messages_vbox->setObjectName("active_chat_messages_vbox");

    active_chat_vbox->addWidget(active_chat_messages);
}

void MainWindow::init_send_message_textbox()
{
    send_message_textbox = new QTextEdit(active_chat);
    send_message_textbox->setObjectName("send_message_textbox");

    active_chat_vbox->addWidget(send_message_textbox);
}

void MainWindow::init_send_message_button()
{
    send_message_pushbutton = new QPushButton(active_chat);
    send_message_pushbutton->setObjectName("send_message_pushbutton");
    send_message_pushbutton->setText("send message");
    active_chat_vbox->addWidget(send_message_pushbutton);

    connect(send_message_pushbutton, &QPushButton::clicked, this, &MainWindow::on_send_message_clicked);
}

void MainWindow::on_send_message_clicked()
{
    QLabel *new_message{ nullptr };
    new_message = new QLabel(active_chat_messages);
    new_message->setText(send_message_textbox->toPlainText());

    active_chat_messages_vbox->addWidget(new_message);

    send_message_textbox->clear();
}

QLabel *MainWindow::get_last_message_on_active_chat()
{
    auto number_of_messages = active_chat_messages->children().length();
    if(0 == number_of_messages)
    {
        throw std::invalid_argument("empty messages");
    }

    auto obj = reinterpret_cast<QLabel*>(active_chat_messages->children().at(number_of_messages - 1));
    return obj;
}


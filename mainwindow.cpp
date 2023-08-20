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

}

void MainWindow::init_active_chat_widget()
{
    active_chat = new QWidget(top_most_widget);
    active_chat->setObjectName("active_chat");
    top_most_hbox->addWidget(active_chat);

    active_chat_vbox = new QVBoxLayout(active_chat);
    active_chat_vbox->setObjectName("active_chat_vbox");

    init_current_chat_messages();
    init_send_message_textbox();
    init_send_message_button();
}

void MainWindow::init_current_chat_messages()
{
    current_messages = new QTextBrowser(active_chat);
    current_messages->setObjectName("current_messages");

    current_messages_vbox = new QVBoxLayout(current_messages);
    current_messages_vbox->setObjectName("current_messages_vbox");

    active_chat_vbox->addWidget(current_messages);
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
    QLabel *new_send_message{ nullptr };
    new_send_message = new QLabel(current_messages);
    new_send_message->setText(send_message_textbox->toPlainText());

    current_messages_vbox->addWidget(new_send_message);

    send_message_textbox->clear();
}

QLabel *MainWindow::get_last_message_on_active_chat()
{
    auto number_of_messages = current_messages->children().length();
    if(0 == number_of_messages)
    {
        throw std::invalid_argument("empty messages");
    }

    auto obj = reinterpret_cast<QLabel*>(current_messages->children().at(number_of_messages - 1));
    return obj;
}



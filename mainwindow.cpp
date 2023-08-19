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

void MainWindow::init_layouts()
{
    vbox = new QVBoxLayout(ui->centralwidget);
}

void MainWindow::init_widgets()
{
    active_chat = new QTextBrowser();
    active_chat_vbox =  new QVBoxLayout(active_chat);

    vbox->addWidget(active_chat);

    send_message_textbox = new QTextEdit();
    vbox->addWidget(send_message_textbox);

    send_message_pushbutton = new QPushButton();
    send_message_pushbutton->setText("send message");
    vbox->addWidget(send_message_pushbutton);

    connect(send_message_pushbutton, &QPushButton::clicked, this, &MainWindow::on_send_message_clicked);
}

QLabel *MainWindow::get_last_message_on_active_chat()
{
    auto number_of_messages = active_chat->children().length();
    if(0 == number_of_messages)
    {
        throw std::invalid_argument("empty messages");
    }

    auto obj = reinterpret_cast<QLabel*>(active_chat->children().at(number_of_messages - 1));
    return obj;
}

void MainWindow::on_send_message_clicked()
{
    QLabel *new_send_message{ nullptr };
    new_send_message = new QLabel();

    new_send_message->setText(send_message_textbox->toPlainText());

    active_chat_vbox->addWidget(new_send_message);

    send_message_textbox->clear();
}

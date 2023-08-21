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
    init_active_chat_widget();
    init_left_drawer_widget();
    align_layout();
}

void MainWindow::init_top_most_widget()
{
    top_most_widget = new QWidget(this);
    top_most_widget->setObjectName("top_most_widget");
    setCentralWidget(top_most_widget);

    top_most_hbox = new QHBoxLayout(top_most_widget);
    top_most_hbox->setObjectName("top_most_hbox");
}

void MainWindow::init_active_chat_widget()
{
    active_chat_widget = new ActiveChat(this);
}

void MainWindow::init_left_drawer_widget()
{
    left_drawer_widget = new LeftDrawer(active_chat_widget, this);
}

void MainWindow::align_layout()
{
    top_most_hbox->addWidget(left_drawer_widget);
    top_most_hbox->addWidget(active_chat_widget);
}

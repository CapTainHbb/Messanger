#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  

    init_models();
    init_widgets();  
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_models()
{
    general_model = new GeneralModel();

    contact_proxy_model = new ContactProxyModel(general_model);
    
    chat_list_proxy_model = new ChatListProxyModel(general_model);

}

void MainWindow::init_widgets()
{
    init_top_most_widget();
    init_left_drawer_widget();
    init_active_chat_widget();
    init_middle_stack_widget();
    connect_signals_to_slots();
    align_layout();
    set_all_widgets_initial_visibility();
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
    left_drawer_widget = new LeftDrawer(active_chat_widget, this);
}

void MainWindow::init_middle_stack_widget()
{
    middle_stack_widget = new MiddleStack(contact_proxy_model, chat_list_proxy_model, this);
}

void MainWindow::init_active_chat_widget()
{
    active_chat_widget = new ActiveChat(general_model, this);
}

void MainWindow::connect_signals_to_slots()
{
    connect(left_drawer_widget, &LeftDrawer::set_middle_stack_widget_index,
            middle_stack_widget, &QStackedWidget::setCurrentIndex);
    
    connect(middle_stack_widget->contact_list_widget, &ContactListWidget::selected_contact_item,
            active_chat_widget, &ActiveChat::on_contact_item_selected);
    
    connect(middle_stack_widget->contact_list_widget, &ContactListWidget::selected_contact_item,
            this, &MainWindow::on_contact_item_selected);
    
    connect(middle_stack_widget->contact_list_widget, &ContactListWidget::selected_contact_item,
            left_drawer_widget, &LeftDrawer::on_contact_item_selected);

    connect(middle_stack_widget->chat_list_widget, &ChatListWidget::chat_item_clicked, 
            active_chat_widget, &ActiveChat::on_chat_item_clicked);

    connect(middle_stack_widget->chat_list_widget, &ChatListWidget::chat_item_deleted, 
            active_chat_widget, &ActiveChat::on_chat_item_deleted);
}

void MainWindow::on_contact_item_selected(const Contact &index)
{
    active_chat_widget->setHidden(false);
}

void MainWindow::align_layout()
{
    top_most_hbox->addWidget(left_drawer_widget);
    top_most_hbox->addWidget(middle_stack_widget);
    top_most_hbox->addWidget(active_chat_widget);
}

void MainWindow::set_all_widgets_initial_visibility()
{
    left_drawer_widget->setHidden(false);

    middle_stack_widget->setHidden(false);
    middle_stack_widget->contact_list_widget->setHidden(true);
    middle_stack_widget->chat_list_widget->setHidden(false);

    active_chat_widget->setHidden(false);
}

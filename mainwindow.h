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

#include <LeftDrawer.hpp>
#include <ActiveChat.hpp>

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

    LeftDrawer *left_drawer_widget{ nullptr };
    ActiveChat *active_chat_widget{ nullptr };

    void init_active_chat_widget();
    void init_left_drawer_widget();
    void align_layout();    

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

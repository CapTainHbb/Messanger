#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_layouts();
    void init_widgets();

    QVBoxLayout *vbox{ nullptr };
    QVBoxLayout *active_chat_vbox{ nullptr };

    QTextBrowser *active_chat{ nullptr };
    QTextEdit *send_message_textbox{ nullptr };
    QPushButton *send_message_pushbutton{ nullptr };

    QLabel *get_last_message_on_active_chat();

public slots:
    void on_send_message_clicked();

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H

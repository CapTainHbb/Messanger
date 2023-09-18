#pragma  once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

#include <XmppClient.hpp>

class AddContactWidget : public  QWidget
{
    Q_OBJECT

public:
    AddContactWidget(QWidget *parent = nullptr);
    ~AddContactWidget() = default;

    QFormLayout *layout{ nullptr };
    void init_layout();

    QLineEdit *contact_jid_text_input{ nullptr };
    QPushButton *add_contact_button{ nullptr };
    void init_add_contact_form();
    void on_add_contact_button_clicked();

signals:
    void request_add_contact(const QString& contact_jid);
};


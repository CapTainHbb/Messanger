#include <AddContactWidget.hpp>

AddContactWidget::AddContactWidget(QWidget *parent)
{
    setParent(parent);

    init_layout();
    init_add_contact_form();
}

void AddContactWidget::init_layout()
{
    layout = new QFormLayout(this);
    layout->setObjectName("add_contact_layout");
}

void AddContactWidget::init_add_contact_form()
{
    contact_jid_text_input = new QLineEdit(this);
    contact_jid_text_input->setObjectName("contact_jid_text_input");
    layout->addRow("contact jid", contact_jid_text_input);

    add_contact_button = new QPushButton(this);
    add_contact_button->setObjectName("add_contact_button");
    add_contact_button->setText("add contact");
    connect(add_contact_button, &QPushButton::clicked,
            this, &AddContactWidget::on_add_contact_button_clicked);

    layout->addRow(add_contact_button);
}

void AddContactWidget::on_add_contact_button_clicked()
{
    auto contact_jid{ contact_jid_text_input->text() };
    emit request_add_contact(contact_jid);
}
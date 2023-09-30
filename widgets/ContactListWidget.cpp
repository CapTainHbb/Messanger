#include "ContactListWidget.hpp"

ContactListWidget::ContactListWidget(ContactProxyModel *_model, QWidget *parent)
    : model{ _model }, QWidget(parent)
{
    init_layout();
    init_contact_list();
}

ContactListWidget::~ContactListWidget()
{
}

void ContactListWidget::init_layout()
{
    vbox = new QVBoxLayout(this);
}


void ContactListWidget::init_contact_list()
{
    contact_list = new QListView(this);
    contact_list->setObjectName("contact_list_widget");

    // moc data
//    model->source_model->add_contact("alice");
//    model->source_model->add_contact("bob");
    //

    contact_list->setModel(model->source_model);
    contact_list->setStyleSheet("background-color: grey");
    
    connect(contact_list, &QListView::doubleClicked,
            this, &ContactListWidget::on_item_double_clicked);

    vbox->addWidget(contact_list);
}

void ContactListWidget::on_item_double_clicked(const QModelIndex &index)
{
    auto contact = model->source_model->get_contact(index);
    emit selected_contact_item(contact);
}

QRect ContactListWidget::get_item_rect(const Contact& contact) const
{
    auto model_index{ model->source_model->get_contact_model_index(contact) };
    return contact_list->visualRect(model_index);
}

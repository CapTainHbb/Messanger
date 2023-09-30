#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QMenu>
#include <stdexcept>
#include <iostream>
#include <ContactProxyModel.hpp>

class ContactListWidget : public QWidget
{
    Q_OBJECT    

public:
    ContactListWidget(ContactProxyModel *model, QWidget *parent = nullptr);
    ~ContactListWidget();

    QVBoxLayout *vbox{ nullptr };
    void init_layout();

    QListView *contact_list{ nullptr };
    void init_contact_list();
    void on_item_double_clicked(const QModelIndex &index);

    QRect get_item_rect(const Contact& contact) const;

    ContactProxyModel *model{ nullptr };

signals:
    void selected_contact_item(const Contact &index);

};



#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QListView>

#include <iostream>
#include <algorithm>

#include <Contact.hpp>

class GeneralModel : public QAbstractListModel
{
    Q_OBJECT

public:

    GeneralModel(QObject *parent = nullptr)
        : QAbstractListModel(parent) {}

    GeneralModel(const QList<Contact> &_contacts, QObject *parent = nullptr)
        : QAbstractListModel(parent), contacts(_contacts) {}

    virtual ~GeneralModel(){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    bool contact_has_chat(const QModelIndex& model_index) const;
    bool contact_has_chat(const Contact& contact) const;

    void add_contact(QString contact_name);
    void update_contact(const Contact& contact);

    Contact get_contact(QString contact_name) const;
    Contact get_contact(const QModelIndex& index) const;

    QModelIndex get_contact_model_index(const Contact& contact);

    QList<Contact> get_contacts() const;

    void add_chat_to_contact(const Contact& contact, const QString& chat_message);
    void add_chat_to_contact(const QModelIndex& model_index, const QString& chat_message);

    void delete_contact_chats(const QModelIndex& model_index);

private:
    QList<Contact> contacts;
};


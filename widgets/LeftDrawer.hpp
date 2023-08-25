#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <stdexcept>

#include "ActiveChat.hpp"

class LeftDrawer : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *left_drawer_vbox{ nullptr };

public:
    LeftDrawer(ActiveChat* wiget, QWidget *parent = nullptr);
    ~LeftDrawer() = default;

    ActiveChat *active_chat_widget{ nullptr };
    void set_active_chat_widget(ActiveChat *widget);

    QListWidget *list_of_chats{ nullptr };
    void init_list_of_chats();

    QPushButton *new_chat_button{ nullptr };
    void init_new_chat_button();
    
    size_t get_number_of_all_chats() const;

    QListWidgetItem* find_chat_item(QString chat_name);
    
    QRect get_chat_item_rect(QListWidgetItem *item);

public slots:
    void on_chat_item_clicked(QListWidgetItem* item);   
    void on_new_chat_clicked();
};


// class StringListModel : public QAbstractListModel
// {
//     Q_OBJECT

// public:
//     StringListModel(const QStringList &strings, QObject *parent = nullptr)
//         : QAbstractListModel(parent), stringList(strings) {}

//     int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//     QVariant data(const QModelIndex &index, int role) const override;
//     QVariant headerData(int section, Qt::Orientation orientation,
//                         int role = Qt::DisplayRole) const override;

//     Qt::ItemFlags flags(const QModelIndex &index) const override;
//     bool setData(const QModelIndex &index, const QVariant &value,
//                     int role = Qt::EditRole) override;

//     bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//     bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

// private:
//     QStringList stringList;
// };

// int StringListModel::rowCount(const QModelIndex &parent) const
// {
//     return stringList.count();
// }

// QVariant StringListModel::data(const QModelIndex &index, int role) const
// {
//     if (!index.isValid())
//         return QVariant();

//     if (index.row() >= stringList.size())
//         return QVariant();

//     if (role == Qt::DisplayRole || role == Qt::EditRole)
//         return stringList.at(index.row());
//     else
//         return QVariant();
// }

// QVariant StringListModel::headerData(int section, Qt::Orientation orientation,
//                                      int role) const
// {
//     if (role != Qt::DisplayRole)
//         return QVariant();

//     if (orientation == Qt::Horizontal)
//         return QStringLiteral("Column %1").arg(section);
//     else
//         return QStringLiteral("Row %1").arg(section);
// }

// Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
// {
//     if (!index.isValid())
//         return Qt::ItemIsEnabled;

//     return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
// }

// bool StringListModel::setData(const QModelIndex &index,
//                               const QVariant &value, int role)
// {
//     if (index.isValid() && role == Qt::EditRole) {

//         stringList.replace(index.row(), value.toString());
//         emit dataChanged(index, index, {role});
//         return true;
//     }
//     return false;
// }

// bool StringListModel::insertRows(int position, int rows, const QModelIndex &parent)
// {
//     beginInsertRows(QModelIndex(), position, position+rows-1);

//     for (int row = 0; row < rows; ++row) {
//         stringList.insert(position, "");
//     }

//     endInsertRows();
//     return true;
// }
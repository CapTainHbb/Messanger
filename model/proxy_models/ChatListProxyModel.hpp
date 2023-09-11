#pragma once

#include <GeneralProxyModel.hpp>

#include <vector>

class ChatListProxyModel : public GeneralProxyModel
{
    Q_OBJECT    
    
public:
    ChatListProxyModel(GeneralModel *source_model, QObject *parent = nullptr);
    ~ChatListProxyModel() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = 0) const override;

    void delete_index_mapping(const QModelIndex& source_model_index);
    void add_index_mapping(const QModelIndex& source_index) override;
    void reorder_index_mapping();

    QModelIndex get_source_model_index(const Contact& contact) const;
    QModelIndex get_source_model_index(const QModelIndex& proxy_model_index) const;

    QModelIndex get_proxy_model_index(const Contact& contact) const;
    QModelIndex get_proxy_model_index(const QModelIndex& source_model_index);

    Contact get_contact_in_chat_list(int proxy_model_index_row) const;

private:
    int map_proxy_row_to_source_row(int row) const;
    int map_source_row_to_proxy_row(int row) const;
    QModelIndex map_source_index_to_proxy_index(const QModelIndex& source_model_index) const;
    QModelIndex map_proxy_index_to_source_index(const QModelIndex& proxy_model_index) const;

public slots:
    void source_data_changed(const QModelIndex &topLeft, 
                        const QModelIndex &bottomRight, 
                        const QVector<int> &roles = QVector<int>()) override;
};

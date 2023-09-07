#pragma once

#include <GeneralProxyModel.hpp>

class ActiveChatProxyModel : public GeneralProxyModel
{
    Q_OBJECT    

public:
    ActiveChatProxyModel(GeneralModel *source_model, QObject *parent = nullptr);
    ~ActiveChatProxyModel() = default;

    void add_index_mapping(const QModelIndex& source_index) override;
};

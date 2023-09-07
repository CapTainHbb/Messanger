#include <ActiveChatProxyModel.hpp>

ActiveChatProxyModel::ActiveChatProxyModel(GeneralModel *_source_model, QObject *parent)
: GeneralProxyModel(_source_model, parent)
{

}


void ActiveChatProxyModel::add_index_mapping(const QModelIndex& source_index)
{

}

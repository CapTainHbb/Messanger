#include <ChatListProxyModel.hpp>

ChatListProxyModel::ChatListProxyModel(GeneralModel *_source_model, QObject *parent)
: GeneralProxyModel(_source_model, parent)
{
    connect(source_model, GeneralModel::dataChanged, this, ChatListProxyModel::source_data_changed);
}

int ChatListProxyModel::rowCount(const QModelIndex &parent) const
{
    return index_mapping.size();
}

QVariant ChatListProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= index_mapping.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        QVariant contact_qvar;
        auto source_model_index{ get_source_model_index(index) };
        auto contact{ source_model->get_contact(source_model_index) };
        contact_qvar.setValue(contact.get_name());
        return contact_qvar;
    }
    else if(Qt::UserRole == role)
    {
        QVariant contact_qvar;
        auto source_model_index{ get_source_model_index(index) };
        auto contact{ source_model->get_contact(source_model_index) };
        contact_qvar.setValue(contact);
        return contact_qvar;
    }
    else
    {
        return QVariant();
    }
}


QModelIndex ChatListProxyModel::get_proxy_model_index(const Contact& contact) const
{
    auto source_model_index{ get_source_model_index(contact) };
    return map_source_index_to_proxy_index(source_model_index);
}

QModelIndex ChatListProxyModel::get_proxy_model_index(const QModelIndex& source_model_index)
{
    return map_source_index_to_proxy_index(source_model_index); 
}

QModelIndex ChatListProxyModel::map_source_index_to_proxy_index(const QModelIndex& source_model_index) const
{
    auto proxy_row{ map_source_row_to_proxy_row(source_model_index.row()) };
    auto proxy_model_index{ index(proxy_row) };
    return proxy_model_index;
}

int ChatListProxyModel::map_source_row_to_proxy_row(int row) const
{
    for (auto &&mapping : index_mapping)
    {
        if(mapping.source_index.get_row() == row)
        {
            return mapping.proxy_index.get_row();
        }
    }
    
    throw std::invalid_argument("invalid source row index");
}


QModelIndex ChatListProxyModel::get_source_model_index(const Contact& contact) const
{
    return source_model->get_contact_model_index(contact);
}

QModelIndex ChatListProxyModel::get_source_model_index(const QModelIndex& proxy_model_index) const
{
    return map_proxy_index_to_source_index(proxy_model_index);
}

QModelIndex ChatListProxyModel::map_proxy_index_to_source_index(const QModelIndex& proxy_model_index) const
{
    auto source_row{ map_proxy_row_to_source_row(proxy_model_index.row()) };
    auto source_model_index{ source_model->index(source_row) };
    return source_model_index;
}

int ChatListProxyModel::map_proxy_row_to_source_row(int row) const
{
    return index_mapping.at(row).source_index.get_row();
}



void ChatListProxyModel::source_data_changed(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    for(const auto& item : index_mapping)
    {
        if(item.source_index.get_row() == topLeft.row())
        {
            if(!source_model->contact_has_chat(topLeft))
            {
                delete_index_mapping(topLeft);
            }
            return;
        }
    }
    
    add_index_mapping(topLeft);
    emit dataChanged(index(0, 0), index(index_mapping.size() - 1));
}

void ChatListProxyModel::delete_index_mapping(const QModelIndex& source_model_index)
{
    bool source_model_index_found{ false };
    int i{ 0 };
    for (; i < index_mapping.size(); i++)
    {
        if(index_mapping.at(i).source_index.get_row() == source_model_index.row())
        {
            source_model_index_found = true;
            break;
        }
    }

    if(!source_model_index_found)
    {
        throw std::invalid_argument("invalid source_model_index!");
    }
    
    index_mapping.erase(index_mapping.begin() + i);

    reorder_index_mapping();    
}

void ChatListProxyModel::reorder_index_mapping()
{
    for (int i = 0; i < index_mapping.size(); i++)
    {
        index_mapping.at(i).proxy_index.row = i;
    }
}

void ChatListProxyModel::add_index_mapping(const QModelIndex& source_model_index)
{
    LocalModelIndex source_index{ };
    source_index.row = source_model_index.row();
    source_index.column = 0;

    LocalModelIndex proxy_index{ };
    proxy_index.row = index_mapping.size();
    proxy_index.column = 0;

    IndexMap new_map{ };
    new_map.proxy_index = proxy_index;
    new_map.source_index = source_index;

    index_mapping.push_back(new_map);
}

Contact ChatListProxyModel::get_contact_in_chat_list(int proxy_model_index_row) const
{
    auto model_index = index(proxy_model_index_row, 0);
    auto qvar = data(model_index, Qt::UserRole);
    auto contact_in_chat_list_proxy_model = qvar.value<Contact>();
    return contact_in_chat_list_proxy_model;
}


#include <GeneralProxyModel.hpp>

int GeneralProxyModel::rowCount(const QModelIndex &parent) const
{
    return source_model->rowCount();
}

QVariant GeneralProxyModel::data(const QModelIndex &index, int role) const
{
    auto data_value { source_model->data(index, role) };

    if (Qt::DisplayRole == role)
    {
        auto contact{ data_value.value<Contact>() };
        QVariant contact_name;
        contact_name.setValue(contact.get_name());
        return contact_name;
    }

    return data_value;
}

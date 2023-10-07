#include <GeneralModel.hpp>


int GeneralModel::rowCount(const QModelIndex &parent) const
{
    return contacts.count();
}

QVariant GeneralModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    
    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}

Qt::ItemFlags GeneralModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index);
}

bool GeneralModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        contacts.replace(index.row(), value.value<Contact>());
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

bool GeneralModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        contacts.insert(row, Contact());
    }

    endInsertRows();
    return true;
}

bool GeneralModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
         contacts.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QVariant GeneralModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= contacts.size())
    {
        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {
        QVariant contact_name;
        contact_name.setValue(contacts.at(index.row()).get_name());
        return contact_name;
    }
    else if (role == Qt::EditRole || role == Qt::UserRole)
    {
        QVariant contact;
        contact.setValue(contacts.at(index.row()));
        return contact;
    }
    else
    {
        return QVariant();
    }
}

void GeneralModel::sort(int column, Qt::SortOrder order)
{
    std::sort(contacts.begin(), contacts.end());
}

bool GeneralModel::contact_has_chat(const QModelIndex& model_index) const
{
    return get_contact(model_index).chat_count() > 0;
}

bool GeneralModel::contact_has_chat(const Contact& contact) const
{
    auto contact_in_model{ get_contact(contact) };
    if(contact_in_model.chat_count() > 0)
    {
        return true;
    }

    return false;
}

Contact GeneralModel::get_contact(const Contact& _contact) const
{
    for(const auto& contact : contacts)
    {
        if (_contact == contact)
        {
            return contact;
        }
    }
    throw std::invalid_argument(_contact.get_jid().toStdString() + " not found!");
}

Contact GeneralModel::get_contact(const QModelIndex& index) const
{
    auto contact_qvariant{ data(index, Qt::UserRole) };

    auto contact = contact_qvariant.value<Contact>();
    return contact;
}

int GeneralModel::get_contact_count() const
{
    return contacts.count();
}

void GeneralModel::delete_all_contacts()
{
    removeRows(0, rowCount());
}



void GeneralModel::add_contact(const Contact& contact)
{
    insertRows(0, 1);

    auto model_index = index(0, Qt::DisplayRole);
    QVariant contact_qvariant;
    contact_qvariant.setValue(contact);

    setData(model_index, contact_qvariant);
}

void GeneralModel::update_contact(const Contact& contact)
{
    auto model_index{ get_contact_model_index(contact) };

    QVariant contact_qvariant;
    contact_qvariant.setValue(contact);

    setData(model_index, contact_qvariant);
}

QModelIndex GeneralModel::get_contact_model_index(const Contact& contact)
{
    for (int i{ 0 }; i < rowCount(); i++)
    {
        auto model_index{ index(i, Qt::DisplayRole) };
        auto contact_in_model = get_contact(model_index);
        if (contact_in_model == contact)
        {
            return  model_index;
        }
    }

    throw std::invalid_argument("contact not found");
}

bool GeneralModel::contact_exists(const QString& contact_name)
{
    return contact_exists(Contact(contact_name));
}

bool GeneralModel::contact_exists(const Contact& contact)
{
    auto contact_iter { std::find(contacts.begin(), contacts.end(),contact) };
    if(contact_iter == contacts.end())
    {
        return false;
    }

    return true;
}

QList<Contact> GeneralModel::get_contacts() const
{
    QList<Contact> all_contacts;

    for (int r = 0; r < rowCount(); ++r) {
        auto model_index = index(r, 0);
        auto model_data = data(model_index, Qt::UserRole);
        auto contact = model_data.value<Contact>();
        all_contacts.append(contact);
    }

    return all_contacts;
}

Contact GeneralModel::get_last_added_contact()
{
    if(rowCount() == 0)
    {
        return Contact{};
    }

    auto model_index{ index(0) };
    return get_contact(model_index);
}


void GeneralModel::add_chat_to_contact(const Contact& contact, const QString& chat_message)
{
    auto model_index{ get_contact_model_index(contact) };
    add_chat_to_contact(model_index, chat_message);
}

void GeneralModel::add_chat_to_contact(const QModelIndex& model_index, const QString& chat_message)
{
    auto contact{ get_contact(model_index) };
    contact.add_chat(chat_message);
    update_contact(contact);
}

void GeneralModel::delete_contact_chats(const QModelIndex& model_index)
{
    auto contact{ get_contact(model_index) };
    contact.delete_chats();
    update_contact(contact);
}
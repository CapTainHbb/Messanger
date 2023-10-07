#include "Contact.hpp"

#include <utility>

void Contact::from_jid(const QString& _jid)
{
    auto splitted_jid{ _jid.split('@') };
    if(splitted_jid.count() != 2)
    {
        throw std::invalid_argument("invalid jid " + _jid.toStdString());
    }

    set_name(splitted_jid.at(0));
    set_domain(splitted_jid.at(1));
    create_jid();
}


bool Contact::operator==(const Contact& other) const
{
    if(get_jid() == other.get_jid())
    {
        return true;
    }
    return false;
}

bool Contact::operator!=(const Contact& other) const
{
    if( (*this) == other)
    {
        return false;
    }

    return true;
}

bool Contact::operator<(const Contact& other)
{
    if (name < other.name)
    {
        return true;
    }

    return false;
}



void Contact::set_name(QString name)
{
    this->name = std::move(name);
}

QString Contact::get_name() const
{
    return name;
}

void Contact::set_domain(const QString& domain)
{
    this->domain = domain;
}

QString Contact::get_domain() const
{
    return this->domain;
}

void Contact::create_jid()
{
    jid = name + "@" + domain;
}

QString Contact::get_jid() const
{
    return this->jid;
}

void Contact::add_chat(const QString& chat_text)
{
    Chat new_chat;
    new_chat.set_chat_text(chat_text);
    chats.append(new_chat);
}
    
Chat Contact::get_chat(int index) const
{
    return chats.at(index);
}

Chat Contact::get_last_chat() const
{
    return get_chats().last();
}


QList<Chat> Contact::get_chats() const
{
    return chats;
}

int Contact::chat_count() const
{
    return chats.count();
}

void Contact::delete_chats()
{
    chats.clear();
}



#include "Contact.hpp"


bool Contact::operator==(const Contact& other)
{
    if(name == other.name)
    {
        return true;
    }
    return false;
}

bool Contact::operator!=(const Contact& other)
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
    this->name = name;
}

QString Contact::get_name() const
{
    return name;
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



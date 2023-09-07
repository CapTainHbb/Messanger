#pragma once

#include <QObject>
#include <iostream>
#include <Chat.hpp>

class Contact
{
public:

    Contact(QString contact_name = "")
        :name{ contact_name }
    {

    }

    bool operator==(const Contact& other);

    bool operator!=(const Contact& other);

    bool operator<(const Contact& other);

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {
        os << contact.get_name().toStdString();
        return os;
    }

    void set_name(QString name);
    QString get_name() const;

    void add_chat(const QString& chat_text);
    Chat get_chat(int index) const;
    Chat get_last_chat() const;
    QList<Chat> get_chats() const;

    int chat_count() const;

    void delete_chats();

private:
    QString name;
    static int id;
    QList<Chat> chats;

};
Q_DECLARE_METATYPE(Contact);

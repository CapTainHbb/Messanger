#pragma once

#include <QObject>
#include <iostream>
#include <Chat.hpp>
#include <utility>

class Contact
{
public:

    explicit Contact(QString contact_name = "", const QString& contact_domain = "127.0.0.1")
    {
        set_name(contact_name);
        set_domain(contact_domain);
        if(!contact_name.isEmpty())
        {
            create_jid();
        }
    }
    void from_jid(const QString& jid);

    bool operator==(const Contact& other) const;

    bool operator!=(const Contact& other) const;

    bool operator<(const Contact& other);

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {
        os << contact.get_name().toStdString();
        return os;
    }

    void set_name(QString name);
    QString get_name() const;

    void set_domain(const QString& domain);
    QString get_domain() const;

    void create_jid();
    QString get_jid() const;

    void add_chat(const QString& chat_text);
    Chat get_chat(int index) const;
    Chat get_last_chat() const;
    QList<Chat> get_chats() const;

    int chat_count() const;

    void delete_chats();

private:
    QString name;
    QString jid;
    QString domain;
    QList<Chat> chats;

};
Q_DECLARE_METATYPE(Contact);

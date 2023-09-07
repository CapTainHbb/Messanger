#pragma once

#include <QString>

class Chat
{
private:
    QString chat_text{ };

public:
    Chat();
    ~Chat();

    bool operator==(const Chat& other)
    {
        return other.get_chat_text() == get_chat_text();
    }

    void set_chat_text(const QString& text);
    QString get_chat_text() const;
};



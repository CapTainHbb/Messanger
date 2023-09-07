#include <Chat.hpp>

Chat::Chat()
{
}

Chat::~Chat()
{
}


void Chat::set_chat_text(const QString& text)
{
    chat_text = text;
}

QString Chat::get_chat_text() const
{
    return chat_text;
}
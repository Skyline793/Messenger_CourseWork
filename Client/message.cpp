#include "message.h"

Message::Message(const QString& sender, const QString& text, const QString& date)
{
    this->sender = sender;
    this->text = text;
    this->date = date;
}

QString Message::GetSender()
{
    return sender;
}

QString Message::GetText()
{
    return text;
}

QString Message::GetDate()
{
    return date;
}

QString Message::ToString()
{
    return QString("[%1] %2: %3").arg(date, sender, text);
}

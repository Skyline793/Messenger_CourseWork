#include "chat.h"

Chat::Chat(const int chatID, const QString& nazv, const QStringList& members)
{
    this->chatID = chatID;
    this->nazv = nazv;
    this->membersNicks = members;
}

int Chat::GetID()
{
    return chatID;
}

QString Chat::GetNazv()
{
    return nazv;
}

QStringList Chat::GetMembers()
{
    return membersNicks;
}

QList<Message*> Chat::GetMessages()
{
    return messages;
}
void Chat::AddMessage(Message* m)
{
    messages.append(m);
}

QString Chat::GetLastMessageDateTime()
{
    if(messages.isEmpty())
        return QString("01.01.1970 00:00:00");
    else
        return messages.last()->GetDate();
}

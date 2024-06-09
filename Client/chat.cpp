#include "chat.h"

Chat::Chat(int chatID, QString nazv)
{
    this->chatID = chatID;
    this->nazv = nazv;
}

Chat::Chat(int chatID, QString nazv, QStringList members)
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

void Chat::AddMember(QString nick)
{
    membersNicks.append(nick);
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
    return messages.last()->GetDate();
}

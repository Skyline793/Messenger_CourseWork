#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include "message.h"

class Chat
{
public:
    Chat(int chatID, QString nazv);
    Chat(int chatID, QString nazv, QStringList members);
    int GetID();
    QString GetNazv();
    QStringList GetMembers();
    void AddMember(QString nick);
    QList<Message*> GetMessages();
    void AddMessage(Message* m);
    QString GetLastMessageDateTime();

private:
    int chatID;
    QString nazv;
    QStringList membersNicks;
    QList<Message*> messages;
};

#endif // CHAT_H

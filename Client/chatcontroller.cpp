#include "chatcontroller.h"

ChatController::ChatController(User* user, QObject *parent)
    : QObject{parent}
{
    this->user = user;
    this->activeChatID = -1;
    connect(user, &User::NewCommand, this, &ChatController::HandleNewCommand);
    connect(user, &User::ClientDisconnected, this, &ChatController::HandleClientDisconnected);
}

void ChatController::HandleNewCommand(QDataStream& in) {
    Commands cmd;
    in >> cmd;
    //Вызываем обработчик в зависимости от поступившей команды
    switch(cmd)
    {
    case Commands::LogInSuccess:
        ProcessLoginSuccess(in);
        break;
    case Commands::LogInFail:
        ProcessLoginFail(in);
        break;
    case Commands::SignUpSuccess:
        ProcessSignUpSuccess(in);
        break;
    case Commands::SignUpFail:
        ProcessSignUpFail(in);
        break;
    case Commands::IncomingMessage:
        ProcessIncomingMessage(in);
        break;
    case Commands::Userlist:
        ProcessReceivedUserlist(in);
        break;
    case Commands::ChatHistory:
        LoadChatHistory(in);
        break;
    case Commands::NewChat:
        AddNewChat(in);
        break;
    case Commands::NewChatFail:
        ProcessNewChatFail(in);
        break;
    }
}

void ChatController::HandleClientDisconnected()
{
    emit Disconnection();
}

void ChatController::SortChats()
{
    std::sort(chats.begin(), chats.end(),[](Chat *chat1, Chat *chat2) {
        QDateTime dateTime1 = QDateTime::fromString(chat1->GetLastMessageDateTime(), "dd.MM.yyyy HH:mm:ss");
        QDateTime dateTime2 = QDateTime::fromString(chat2->GetLastMessageDateTime(), "dd.MM.yyyy HH:mm:ss");
        return dateTime1 > dateTime2;
    });
}

void ChatController::ProcessIncomingMessage(QDataStream &in)
{
    int chatID;
    QString senderNick;
    QString date;
    QString text;
    in >> chatID >> senderNick >> date >> text;
    Message* m = new Message(senderNick, text, date);
    foreach(Chat* chat, chats)
    {
        int id = chat->GetID();
        if(id != chatID) continue;
        chat->AddMessage(m);
        SortChats();
        emit ChatsListUpdated(GetChatsList());
        emit NewMessage(chatID);
        break;
    }
}

void ChatController::LoadChatHistory(QDataStream& in)
{
    QString chatInfo;
    QStringList messages;
    in >> chatInfo >> messages;
    QStringList chatInfoParts = chatInfo.split("$");
    int id = chatInfoParts[0].toInt();
    QString nazv = chatInfoParts[1];
    QStringList members = chatInfoParts[2].split(",");
    if(nazv.isEmpty() && members.size() == 2)
    {
        if(members[0] != user->GetNickname())
            nazv = members[0];
        else
            nazv = members[1];
    }

    Chat* newChat = new Chat(id, nazv, members);
    foreach(QString m, messages)
    {
        QStringList messageParts = m.split("$");
        QString sender = messageParts[0];
        QString text = messageParts[1];
        QString date = messageParts[2];
        Message* message = new Message(sender, text, date);
        newChat->AddMessage(message);

    }
    this->chats.append(newChat);
    emit ChatsListUpdated(GetChatsList());
}

void ChatController::AddNewChat(QDataStream &in)
{
    int chatID;
    QString nazv;
    QStringList members;
    Chat* newChat;
    in >> chatID >> nazv >> members;
    if(nazv.isEmpty() && members.size() == 2)
    {
        if(members[0] != user->GetNickname())
            nazv = members[0];
        else
            nazv = members[1];
        newChat = new Chat(chatID, nazv, members);
    }
    else
        newChat = new Chat(chatID, nazv, members);

    chats.append(newChat);
    emit ChatsListUpdated(GetChatsList());
}

void ChatController::ProcessLoginSuccess(QDataStream &in)
{
    int id;
    QString nickname;
    QString sex;
    in >> id >> nickname >> sex;
    user->SetID(id);
    user->SetNickname(nickname);
    user->SetSex(sex);
    emit SuccessfulLogin();
}

void ChatController::ProcessLoginFail(QDataStream &in)
{
    emit FailedLogin();
}

void ChatController::ProcessSignUpSuccess(QDataStream& in)
{
    emit SuccessfulSignUp();
}

void ChatController::ProcessSignUpFail(QDataStream &in)
{
    emit FailedSignUp();
}

void ChatController::ProcessReceivedUserlist(QDataStream &in)
{
    QStringList users;
    in >> users;
    emit UserlistReceived(users);
}

void ChatController::ProcessNewChatFail(QDataStream &in)
{
    emit FailedNewChat();
}

void ChatController::SendMessage(const QString& text)
{
    int chatID = activeChatID;
    int senderID = user->GetID();
    QString senderNick = user->GetNickname();
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::OutcomingMessage << chatID << senderID << senderNick << date << text;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);

    foreach(Chat* chat, chats)
    {
        int id = chat->GetID();
        if(id != chatID) continue;
        Message* m = new Message(senderNick, text, date);
        chat->AddMessage(m);
        emit ChatsListUpdated(GetChatsList());
        emit NewMessage(chatID);
        break;
    }
}

void ChatController::CreateGroupChat(const QString& nazv, QStringList members)
{
    members.append(user->GetNickname());
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::NewChatRequest << nazv << members;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);
}

void ChatController::CreatePersonalChat(const QString& member)
{
    QStringList members;
    members.append(user->GetNickname());
    members.append(member);
    QString nazv = "";
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::NewChatRequest << nazv << members;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);
}

bool ChatController::ConnectToServer(const QString &addr, int port)
{
    return user->Connect(addr, port);
}

void ChatController::Login(const QString &nickname, const QString &password)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::LogInRequest << nickname << password;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);
}

void ChatController::SignUp(const QString &nickname, const QString &name, const QString &sex, const QString &password)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::SignUpRequest << nickname << name << sex << password;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);
}

void ChatController::RequestChatHistory()
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::ChatHistoryRequest;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);
}

void ChatController::RequestUserlist()
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::UserlistRequest;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    user->SendData(data);
}

QStringList ChatController::GetActiveChatMessages()
{
    QStringList messages;
    foreach(Chat* chat, chats)
    {
        if(chat->GetID() != this->activeChatID)
            continue;
        QList<Message*> list = chat->GetMessages();
        foreach(Message* m, list)
            messages.append(m->ToString());
        break;
    }
    return messages;
}

QList<QPair<int, QString>> ChatController::GetChatsList()
{
    SortChats();
    QList<QPair<int, QString>> list;
    foreach(Chat* chat, chats)
    {
        list.append(QPair<int, QString>(chat->GetID(), chat->GetNazv()));
    }
    return list;
}

void ChatController::SetActiveChat(int chatID)
{
    this->activeChatID = chatID;
}

int ChatController::GetActiveChatID()
{
    return activeChatID;
}

QString ChatController::GetChatNazv(int chatID)
{
    QString nazv;
    foreach(Chat* chat, chats)
    {
        if(chat->GetID() == chatID)
        {
            nazv = chat->GetNazv();
            break;
        }
    }
    return nazv;
}

QStringList ChatController::GetChatMembers(int chatID)
{
    QStringList members;
    foreach(Chat* chat, chats)
    {
        if(chat->GetID() == chatID)
        {
            members = chat->GetMembers();
            break;
        }
    }
    return members;
}

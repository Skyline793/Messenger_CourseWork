#include "server.h"
#include <QDataStream>
#include <QTextStream>
#include <QDebug>
#include "Commands.h"

Server::~Server()
{
    myServer->close();
    delete myServer;
    delete db;
}

Server::Server(Database* db, QObject *parent)
    : QObject(parent) {
    myServer = new QTcpServer(this);
    this->db = db;
    connect(myServer, &QTcpServer::newConnection, this, &Server::NewConnection);
}

void Server::StartServer(int nPort)
{
    if (!myServer->listen(QHostAddress::Any, nPort)) {
        qCritical() << "Не удалось запустить сервер:" << myServer->errorString();
        exit(1);
    }
    foreach(ILogger* logger, loggers)
        logger->LogStart(QString::number(myServer->serverPort()));
}

void Server::AddLogger(ILogger *logger)
{
    this->loggers.append(logger);
}

void Server::NewConnection() {
    QTcpSocket *socket = myServer->nextPendingConnection();
    ClientHandler *handler = new ClientHandler(socket, this);
    connect(handler, &ClientHandler::NewMessage, this, &Server::HandleNewCommand);
    connect(handler, &ClientHandler::ClientDisconnected, this, &Server::HandleClientDisconnected);
}

void Server::HandleNewCommand(ClientHandler* client, QDataStream& in) {
    Commands cmd;
    in >> cmd;
    switch(cmd)
    {
    case Commands::LogInRequest:
        LogInClient(client, in);
        break;
    case Commands::SignUpRequest:
        SignUpClient(client, in);
        break;
    case Commands::OutcomingMessage:
        ForwardMessage(in);
        break;
    case Commands::UserlistRequest:
        SendUserlist(client);
        break;
    case Commands::ChatHistoryRequest:
        SendChatsHistory(client);
        break;
    case Commands::NewChatRequest:
        AddNewChat(client, in);
    }
}

void Server::HandleClientDisconnected(ClientHandler* client)
{
    if (clients.contains(client))
    {
    clients.removeOne(client);
    foreach(ILogger* logger, loggers)
        logger->LogDisconnection(client->GetNickname());
    }
    delete client;
}

void Server::LogInClient(ClientHandler* client, QDataStream& in)
{
    QString nickname;
    QString password;
    in >> nickname >> password;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    if (db->IsUserExists(nickname, password)) {
        client->SetNickname(nickname);
        client->SetID(db->GetUserID(nickname));
        out << quint32(0) << Commands::LogInSuccess << client->GetID() << client->GetNickname() << db->GetUserSex(client->GetID());
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
        clients.append(client);
        foreach(ILogger* logger, loggers)
            logger->LogConnection(client->GetNickname());
    }
    else {
        out << quint32(0) << Commands::LogInFail;
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
    }
}

void Server::SignUpClient(ClientHandler* client, QDataStream& in)
{
    QString nickname;
    QString name;
    QString sex;
    QString password;
    in >> nickname >> name >> sex >> password;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    if (db->AddUser(nickname, name, sex, password)) {
        out << quint32(0) << Commands::SignUpSuccess;
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
    }
    else {
        out << quint32(0) << Commands::SignUpFail;
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
    }
}

void Server::ForwardMessage(QDataStream& in)
{
    int chatID;
    int senderID;
    QString senderNick;
    QString date;
    QString text;
    in >> chatID >> senderID >> senderNick >> date >> text;
    if(!db->AddMessage(chatID, senderID, date, text))
        return;
   QVector<int> receivers = db->GetChatMembers(chatID);
    if(receivers.isEmpty()) return;
    foreach(ClientHandler* client, clients)
    {
        if(receivers.contains(client->GetID()) && client->GetID() != senderID)
        {
            qDebug() << client->GetNickname();
            data.clear();
            QDataStream out(&data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_2);
            out << quint32(0) << Commands::IncomingMessage << chatID << senderNick << date << text;
            out.device()->seek(0);
            out << quint32(data.size() - sizeof(quint32));
            client->SendData(data);
        }
    }
}

void Server::SendUserlist(ClientHandler* client)
{

    QStringList users = db->GetUserNicknames();
    users.removeOne(client->GetNickname());
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint32(0) << Commands::Userlist << users;
    out.device()->seek(0);
    out << quint32(data.size() - sizeof(quint32));
    client->SendData(data);
}

void Server::SendChatsHistory(ClientHandler* client)
{
    QStringList chats = db->GetUserChats(client->GetID());
    foreach(QString chat, chats)
    {
        data.clear();
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_2);
        out << quint32(0) << Commands::ChatHistory << chat << db->GetChatMessages(chat.section("$", 0, 0).toInt());
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
    }
}

void Server::AddNewChat(ClientHandler* client, QDataStream &in)
{
    int chatID = 0;
    QString nazv;
    QStringList membersNicknames;
    QStringList membersID;
    in >> nazv >> membersNicknames;
    foreach(QString nick, membersNicknames)
        membersID.append(QString::number(db->GetUserID(nick)));
    membersID.sort();
    if(db->IsChatExists(nazv, membersID.join(",")))
    {
        data.clear();
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_2);
        out << quint32(0) << Commands::NewChatFail;
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
        return;
    }

    if(nazv.isEmpty() && membersID.size() == 2)
    {
        chatID = db->AddPersonalChat(membersID.join(","));
    }
    else
    {
        chatID = db->AddGroupChat(nazv, membersID.join(","));
    }

    foreach(ClientHandler* client, clients)
    {
        if(!membersNicknames.contains(client->GetNickname()))
            continue;
        data.clear();
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_2);
        out << quint32(0) << Commands::NewChat << chatID << nazv << membersNicknames;
        out.device()->seek(0);
        out << quint32(data.size() - sizeof(quint32));
        client->SendData(data);
    }
}


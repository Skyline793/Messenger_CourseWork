#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include "clienthandler.h"
#include "ilogger.h"
#include "database.h"

class Server : public QObject {
    Q_OBJECT

public:
    ~Server();
    Server(Database* db, QObject *parent = nullptr);
    void StartServer(int nPort);
    void AddLogger(ILogger* logger);

private slots:
    void NewConnection();
    void HandleNewCommand(ClientHandler* client, QDataStream& in);
    void HandleClientDisconnected(ClientHandler* client);

private:
    QTcpServer *myServer;
    Database* db;
    QList<ClientHandler*> clients;
    QList<ILogger*> loggers;
    QByteArray data;

    void LogInClient(ClientHandler* client, QDataStream& in);
    void SignUpClient(ClientHandler* client, QDataStream& in);
    void ForwardMessage(QDataStream& in);
    void SendUserlist(ClientHandler* client);
    void SendChatsHistory(ClientHandler* client);
    void AddNewChat(ClientHandler* client, QDataStream& in);

};

#endif // SERVER_H

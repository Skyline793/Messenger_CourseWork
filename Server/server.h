#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

#include "clienthandler.h"
#include "ilogger.h"
#include "database.h"
#include "Commands.h"

///
/// \brief Класс сервера
///
class Server : public QObject {
    Q_OBJECT
    //Публичные методы
public:
    ~Server();
    Server(Database* db, QObject *parent = nullptr);
    ///
    /// \brief Запустить прослушивание сервера
    /// \param nPort - номер порта сервера
    ///
    void StartServer(int nPort);
    ///
    /// \brief Добавить логгера в список
    /// \param logger - объект типа ILogger
    ///
    void AddLogger(ILogger* logger);
    ///
    /// \brief Удалить логгера из списка
    /// \param logger - объект типа ILogger
    ///
    void RemoveLogger(ILogger* logger);

    //приватные слоты
private slots:
    ///
    /// \brief Обработчик нового подключения к серверу
    ///
    void HandleNewConnection();
    ///
    /// \brief Обрабочик входящей команды от клиента
    /// \param client - указатель на клиента
    /// \param in - поток данных
    ///
    void HandleNewCommand(ClientHandler* client, QDataStream& in);
    ///
    /// \brief Обработчик отключения клиента от сервера
    /// \param client - указатель на клиента
    ///
    void HandleClientDisconnected(ClientHandler* client);

    //приватные методы
private:
    ///
    /// \brief Осуществить авторизацию клиента
    /// \param client - указатель на клиента
    /// \param in - поток данных с логином и паролем клиента
    ///
    void ProcessLogInRequest(ClientHandler* client, QDataStream& in);
    ///
    /// \brief SignUpClient - осуществить регистрацию клиента в базе
    /// \param client - указатель на клиента
    /// \param in - поток данных с информацией о клиенте
    ///
    void ProcessSignUpRequest(ClientHandler* client, QDataStream& in);
    ///
    /// \brief Маршрутизировать сообщение от отправителя получателям
    /// \param in - поток данных с сообщением
    ///
    void ProcessOutcomingMessage(QDataStream& in);
    ///
    /// \brief Отправить клиенту список пользователей из базы данных
    /// \param client - указатель на клиента-получателя
    ///
    void ProcessUserlistRequest(ClientHandler* client);
    ///
    /// \brief Отправить клиенту историю его чатов и сообщений
    /// \param client - указатель на клиента-получателя
    ///
    void ProcessChatHistoryRequest(ClientHandler* client);
    ///
    /// \brief Добавить в базу новый чат и разослать его участникам
    /// \param client - указатель на клиента, запросившего создание чата
    /// \param in - поток данных с названием и участниками чата
    ///
    void ProcessNewChatRequest(ClientHandler* client, QDataStream& in);

    //приватные поля
private:
    ///
    /// \brief tcp сервер
    ///
    QTcpServer *myServer;
    ///
    /// \brief база данных
    ///
    Database* db;
    ///
    /// \brief список подключенных клиентов
    ///
    QList<ClientHandler*> clients;
    ///
    /// \brief список логгеров
    ///
    QList<ILogger*> loggers;
    ///
    /// \brief массив данных, используемый для отправки сообщений клиентам
    ///
    QByteArray data;
};

#endif // SERVER_H

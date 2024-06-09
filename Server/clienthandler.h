#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QTcpSocket>
#include <QObject>
#include <QString>

///
/// \brief Класс обработчика Клиента
///
class ClientHandler : public QObject {
    Q_OBJECT

public:
    ClientHandler(QTcpSocket* socket, QObject *parent = nullptr);
    ///
    /// \brief Сеттер никнейма клиента
    /// \param nickname - никнейм
    ///
    void SetNickname(const QString &nickname);
    ///
    /// \brief Геттер никнейма клиента
    /// \return никнейм
    ///
    QString GetNickname();
    ///
    /// \brief Сеттер id клиента
    /// \param id клиента
    ///
    void SetID(int id);
    ///
    /// \brief геттер id клиента
    /// \return id клиента
    ///
    int GetID();
    ///
    /// \brief Сеттер пола клиента
    /// \param пол клиента
    ///
    void SendData(QByteArray& data);

signals:
    ///
    /// \brief Сигнал о новом сообщении от сервера
    /// \param client - указатель на клиента
    /// \param in - ссылка на поток данных
    ///
    void NewMessage(ClientHandler* client, QDataStream& in);
    ///
    /// \brief Сигнал об отключении клиента от хоста
    /// \param указатель на клиента
    ///
    void ClientDisconnected(ClientHandler* client);

private slots:
    ///
    /// \brief Обрабочик сигнала readyRead
    ///
    void HandleReadyRead();
    ///
    /// \brief Обработчик сигнала disconnected
    ///
    void HandleDisconnected();

private:
    ///
    /// \brief id клиента
    ///
    int id;
    ///
    /// \brief никнейм клиента
    ///
    QString nickname;
    ///
    /// \brief tcp сокет
    ///
    QTcpSocket *clientSocket;
    ///
    /// \brief размер получаемого блока
    ///
    quint32 blockSize;
};

#endif // CLIENTHANDLER_H

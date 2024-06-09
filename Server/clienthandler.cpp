#include "clienthandler.h"
#include "Commands.h"

ClientHandler::ClientHandler(QTcpSocket* socket, QObject *parent)
    : QObject(parent), clientSocket(socket) {
    connect(socket, &QTcpSocket::readyRead, this, &ClientHandler::HandleReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientHandler::HandleDisconnected);
    blockSize = 0;
}

void ClientHandler::SetNickname(const QString &nickname) {
    if(!nickname.isEmpty())
        this->nickname = nickname;
}

QString ClientHandler::GetNickname() {
    return nickname;
}

void ClientHandler::SetID(int id)
{
    if(id > 0)
        this->id = id;
}
int ClientHandler::GetID()
{
    return id;
}

void ClientHandler::SendData(QByteArray& data)
{
    clientSocket->write(data);
}

void ClientHandler::HandleReadyRead()
{
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() != QDataStream::Ok)
        return;
    while(true)
    {
        if(blockSize != 0 || clientSocket->bytesAvailable() <2)
            return;
        in >> blockSize;
        if(clientSocket->bytesAvailable() < blockSize)
            return;
        blockSize = 0;
        emit NewMessage(this, in);
    }
}

void ClientHandler::HandleDisconnected()
{
    emit ClientDisconnected(this);
}

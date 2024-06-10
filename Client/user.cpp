#include "user.h"

User::User(QObject *parent)
    : QObject{parent}, socket(new QTcpSocket(this))
{
    blockSize = 0;
    connect(socket, &QTcpSocket::readyRead, this, &User::HandleReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &User::HandleDisconnected);
}

User::User(QTcpSocket* socket, int id, QString nickname, QString sex, QObject *parent)
    : QObject{parent}
{
    this->socket = socket;
    this->id = id;
    this->nickname = nickname;
    this->sex = sex;
    connect(socket, &QTcpSocket::readyRead, this, &User::HandleReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &User::HandleDisconnected);
    blockSize = 0;
}

void User::SetID(int ID)
{
    if(ID > 0)
        this->id = ID;
}

void User::SetNickname(const QString &nickname)
{
    if(!nickname.isEmpty())
        this->nickname = nickname;
}

void User::SetSex(const QString &sex)
{
    if(!sex.isEmpty())
        this->sex = sex;
}

bool User::Connect(const QString& addr, int port)
{
    socket->connectToHost(addr, port);
    return socket->waitForConnected(3000);
}

int User::GetID()
{
    return id;
}

QString User::GetNickname()
{
    return nickname;
}

QString User::GetSex()
{
    return sex;
}

void User::SendData(QByteArray& data)
{
    socket->write(data);
}

void User::HandleReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() != QDataStream::Ok)
        return;
    //циклически получаем блоки, пока не получим все сообщение
    while(true)
    {
        if(blockSize != 0 || socket->bytesAvailable() < 2)
            return;
        in >> blockSize;
        if(socket->bytesAvailable() < blockSize)
            return;
        blockSize = 0;
        emit NewCommand(in);
    }
}

void User::HandleDisconnected()
{
    socket->deleteLater();
    emit ClientDisconnected();
}

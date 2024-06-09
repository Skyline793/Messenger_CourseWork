#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpSocket>

class User : public QObject
{
    Q_OBJECT
public:
    User(QObject *parent = nullptr);
    User(QTcpSocket* socket, int id, QString nickname, QString sex, QObject *parent = nullptr);
    void SetID(int ID);
    void SetNickname(const QString& nickname);
    void SetSex(const QString& sex);
    int GetID();
    QString GetNickname();
    QString GetSex();
    void SendData(QByteArray& data);
    bool Connect(const QString& addr, int port);

signals:
    void NewMessage(QDataStream& in);
    void ClientDisconnected();
private slots:
    void HandleReadyRead();
    void HandleDisconnected();

private:
    QTcpSocket* socket;
    int id;
    QString nickname;
    QString sex;
    quint32 blockSize;
};

#endif // USER_H

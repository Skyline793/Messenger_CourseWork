#ifndef USER_H
#define USER_H

#include <QTcpSocket>
#include <QString>

///
/// \brief Класс Пользователь мессенджера
///
class User : public QObject
{
    Q_OBJECT
    //Публичные методы
public:
    User(QObject *parent = nullptr);
    User(QTcpSocket* socket, int id, QString nickname, QString sex, QObject *parent = nullptr);
    ///
    /// \brief Сеттер id пользователя
    /// \param ID
    ///
    void SetID(int ID);
    ///
    /// \brief Геттер id пользователя
    /// \return id пользователя
    ///
    int GetID();
    ///
    /// \brief Сеттер ника пользователя
    /// \param nickname - ник
    ///
    void SetNickname(const QString& nickname);
    ///
    /// \brief Геттер ника пользователя
    /// \return ник
    ///
    QString GetNickname();
    ///
    /// \brief Сеттер пола пользователя
    /// \param sex - пол
    ///
    void SetSex(const QString& sex);
    ///
    /// \brief GetSex - Геттер пола пользователя
    /// \return пол
    ///
    QString GetSex();
    ///
    /// \brief Отправить данные на сервер через сокет
    /// \param data - массив данных
    ///
    void SendData(QByteArray& data);
    ///
    /// \brief Подключить сокет к серверу
    /// \param addr - адрес сервера
    /// \param port - номер порта сервера
    /// \return 1 - подключение успешно, 0 - нет
    ///
    bool Connect(const QString& addr, int port);

    //сигналы
signals:
    ///
    /// \brief Сигнал о новом сообщении от сервера
    /// \param in - ссылка на поток данных
    ///
    void NewCommand(QDataStream& in);
    ///
    /// \brief Сигнал об отключении клиента от сервера
    ///
    void ClientDisconnected();

    //приватные слоты
private slots:
    ///
    /// \brief Обработчик события readyRead от сокета
    ///
    void HandleReadyRead();
    ///
    /// \brief Обрабтчик события disconnected от сокета
    ///
    void HandleDisconnected();

    //Приватные поля
private:
    ///
    /// \brief tcp cокет клиента
    ///
    QTcpSocket* socket;
    ///
    /// \brief id пользователя из базы
    ///
    int id;
    ///
    /// \brief никнейм пользователя
    ///
    QString nickname;
    ///
    /// \brief пол пользователя
    ///
    QString sex;
    ///
    /// \brief размер принимаего блока
    ///
    quint32 blockSize;
};

#endif // USER_H

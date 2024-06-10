#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>

///
/// \brief The Класс для работы с базой данных мессенджера
///
class Database {
    //публичные методы
public:
    ///
    /// \brief Конструктор
    /// \param dbName - имя файла с базой данных
    ///
    Database(const QString &dbName);
    ///
    /// \brief Проверить, открыта ли база данных
    /// \return 1 - открыта, 0 - нет
    ///
    bool IsOpen();
    ///
    /// \brief Добавить пользователя в базу
    /// \param nickname - никнейм
    /// \param name - имя
    /// \param sex - пол
    /// \param password - пароль
    /// \return 1 - пользователь добавлен, 0 - нет
    ///
    bool AddUser(const QString &nickname, const QString &name, const QString& sex, const QString &password);
    ///
    /// \brief Добавить личный чат
    /// \param members - участники чата
    /// \return id чата
    ///
    int AddPersonalChat(const QString& members);
    ///
    /// \brief Добавить групповой чат
    /// \param nazv - название чата
    /// \param members - участники чата
    /// \return id чата
    ///
    int AddGroupChat(const QString& nazv, const QString& members);
    ///
    /// \brief Добавить сообщение
    /// \param chatID - id чата
    /// \param senderID - id отправителя
    /// \param date - дата и время отправки
    /// \param text - текст сообщения
    /// \return 1 - сообщение добавлено, 0 - нет
    ///
    bool AddMessage(const int chatID, const int senderID, const QString& date, const QString& text);
    ///
    /// \brief Проверить, существует ли пользователь
    /// \param nickname - никнейм
    /// \param password - пароль
    /// \return 1 - существует, 0 - нет
    ///
    bool IsUserExists(const QString &nickname, const QString &password);
    ///
    /// \brief Проверить, существует ли чат
    /// \param nazv - название чата
    /// \param members - список членов чата
    /// \return 1 - существует, 0 - нет
    ///
    bool IsChatExists(const QString& nazv, const QString& members);
    ///
    /// \brief Получить список участников чата
    /// \param chatID - id чата
    /// \return вектор id участников
    ///
    QVector<int> GetChatMembers(const int chatID);
    ///
    /// \brief Получить список чатов пользователя
    /// \param userID - id пользователя
    /// \return список id чатов пользователя
    ///
    QStringList GetUserChats(const int userID);
    ///
    /// \brief Получить список сообщений чата
    /// \param chatID - id чата
    /// \return список сообщений
    ///
    QStringList GetChatMessages(const int chatID);
    ///
    /// \brief Получить id пользователя
    /// \param nickname - никнейм
    /// \return id пользователя
    ///
    int GetUserID(const QString& nickname);
    ///
    /// \brief Получить никнейм пользователя
    /// \param userID - id пользователя
    /// \return никнейм пользователя
    ///
    QString GetUserNickname(const int userID);
    ///
    /// \brief Получить пол пользователя
    /// \param userID - id пользователя
    /// \return пол пользователя
    ///
    QString GetUserSex(const int userID);
    ///
    /// \brief Получить список никнеймов пользователей
    /// \return список никнеймов
    ///
    QStringList GetUserNicknames();

    //приватные поля
private:
    ///
    /// \brief объект для доступа к базе данных
    ///
    QSqlDatabase db;
};

#endif // DATABASE_H

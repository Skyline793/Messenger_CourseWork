#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QList>

class Database {
public:
    Database(const QString &dbName);
    bool IsOpen();
    bool AddUser(const QString &nickname, const QString &name, const QString& sex, const QString &password);
    int AddPersonalChat(const QString& members);
    int AddGroupChat(const QString& nazv, const QString& members);
    bool AddMessage(const int chatID, const int senderID, const QString& date, const QString& text);
    bool RemoveUser(const QString &nickname);
    bool IsUserExists(const QString &nickname, const QString &password);
    bool IsChatExists(const QString& nazv, const QString& members);
    QVector<int> GetChatMembers(int chatID);
    QStringList GetUserChats(int userID);
    QStringList GetChatMessages(int chatID);
    int GetUserID(const QString& nickname);
    QString GetUserNickname(int userID);
    QString GetUserSex(int userID);
    QStringList GetUserNicknames();
    QStringList GetUserNicknames(QString& usersID);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

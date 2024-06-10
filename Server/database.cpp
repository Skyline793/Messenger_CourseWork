#include "database.h"

Database::Database(const QString &dbName) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        qCritical() << "Ошибка: не удалось подключиться к базе данных";
    }
    else {
        QSqlQuery query;
        query.exec(                   "CREATE TABLE IF NOT EXISTS users ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "nickname TEXT UNIQUE NOT NULL,"
                                      "name TEXT NOT NULL, "
                                      "sex TEXT NOT NULL, "
                                      "password TEXT NOT NULL,"
                                      "CHECK(sex = 'М' OR sex = 'Ж')"
                                      ") ;");
        query.exec(                   "CREATE TABLE IF NOT EXISTS chats ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "nazv TEXT,"
                                      "members TEXT NOT NULL"
                                      ") ;");
        query.exec(                   "CREATE TABLE IF NOT EXISTS messages ("
                                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "chat INTEGER NOT NULL,"
                                      "sender INTEGER NOT NULL,"
                                      "date TEXT NOT NULL,"
                                      "text TEXT NOT NULL,"
                                      "FOREIGN KEY (sender) REFERENCES users (id),"
                                      "FOREIGN KEY (chat) REFERENCES chats (id)"
                                      ");");
    }
}

bool Database::IsOpen()
{
    return db.isOpen();
}

bool Database::AddUser(const QString &nickname, const QString &name, const QString& sex, const QString &password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (nickname, name, sex, password) VALUES (:nickname, :name, :sex, :password)");
    query.bindValue(":nickname", nickname);
    query.bindValue(":name", name);
    query.bindValue(":sex", sex);
    query.bindValue(":password", password);
    return query.exec();
}

int Database::AddPersonalChat(const QString& members)
{
    int id = 0;
    QSqlQuery query;
    query.prepare("INSERT INTO chats (members) VALUES (:members)");
    query.bindValue(":members", members);
    if(query.exec())
    {
        query.prepare("SELECT id FROM chats WHERE members = :members");
        query.bindValue(":members", members);
        query.exec();
        if(query.next())
            id = query.value(0).toInt();
    }
    return id;
}

int Database::AddGroupChat(const QString& nazv, const QString& members)
{
    int id = 0;
    QSqlQuery query;
    query.prepare("INSERT INTO chats (nazv, members) VALUES (:nazv, :members)");
    query.bindValue(":nazv", nazv);
    query.bindValue(":members", members);
    if(query.exec())
    {
        query.prepare("SELECT id FROM chats WHERE nazv = :nazv AND members = :members");
        query.bindValue(":nazv", nazv);
        query.bindValue(":members", members);
        query.exec();
        if(query.next())
            id = query.value(0).toInt();
    }
    return id;
}

bool Database::AddMessage(const int chatID, const int senderID, const QString& date, const QString& text)
{
    QSqlQuery query;
    query.prepare("INSERT INTO messages (chat, sender, date, text) VALUES (:chat, :sender, :date, :text)");
    query.bindValue(":chat", chatID);
    query.bindValue(":sender", senderID);
    query.bindValue(":date", date);
    query.bindValue(":text", text);
    return query.exec();
}

bool Database::IsUserExists(const QString &nickname, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE nickname = :nickname AND password = :password");
    query.bindValue(":nickname", nickname);
    query.bindValue(":password", password);
    query.exec();
    return query.next();
}

bool Database::IsChatExists(const QString &nazv, const QString &members)
{
    QSqlQuery query;
    QString sql;
    if(nazv.isEmpty())
        sql = QString("SELECT * FROM chats WHERE nazv IS NULL AND members = '%1\'").arg(members);
    else
        sql = QString("SELECT * FROM chats WHERE nazv = '%1' AND members = '%2'").arg(nazv, members);
    query.exec(sql);
    return query.next();
}

QVector<int> Database::GetChatMembers(const int chatID)
{
    QSqlQuery query;
    QVector<int> chatMembers;
    query.prepare("SELECT members FROM chats WHERE id = :chatID");
    query.bindValue(":chatID", chatID);
    query.exec();
    if(query.next())
    {
        QStringList list = query.value(0).toString().split(",");
        foreach(QString member, list)
        {
            chatMembers.append(member.toInt());
        }
    }
    return chatMembers;
}

QStringList Database::GetUserChats(const int userID)
{
    QSqlQuery query;
    QStringList chats;
    QString sql = QString("SELECT id, nazv, members FROM chats WHERE members GLOB '%1,*' OR members GLOB '*,%2,*' OR members GLOB '*,%3'").arg
            (QString::number(userID), QString::number(userID), QString::number(userID));
    query.prepare(sql);
    query.exec();
    while(query.next())
    {
        QStringList membersID = query.value(2).toString().split(",");
        QStringList membersNicks;
        foreach(QString id, membersID)
        {
            membersNicks.append(GetUserNickname(id.toInt()));
        }

        QString chat = QString("%1$%2$%3").arg(query.value(0).toString(), query.value(1).toString(), membersNicks.join(","));
        chats.append(chat);
    }

    return chats;
}

QStringList Database::GetChatMessages(const int chatID)
{
    QSqlQuery query;
    QStringList messages;
    query.prepare("SELECT u.nickname, m.text, m.date FROM messages AS m, users AS u WHERE m.chat = :chatID AND u.id = m.sender ORDER BY m.id");
    query.bindValue(":chatID", chatID);
    query.exec();
    while(query.next())
    {
        QString m = QString("%1$%2$%3").arg(query.value(0).toString(), query.value(1).toString(), query.value(2).toString());
        messages.append(m);
    }
    return messages;
}

int Database::GetUserID(const QString& nickname)
{
    QSqlQuery query;
    int id = 0;
    query.prepare("SELECT id FROM users WHERE nickname = :nickname");
    query.bindValue(":nickname", nickname);
    query.exec();
;    if(query.next())
    {
        id = query.value(0).toInt();
    }
    return id;
}

QString Database::GetUserNickname(const int userID)
{
    QString nickname;
    QSqlQuery query;
    query.prepare("SELECT nickname FROM users WHERE id = :userID");
    query.bindValue(":userID", userID);
    query.exec();
    if (query.next())
    {
        nickname = query.value(0).toString();
    }
    return nickname;
}

QString Database::GetUserSex(const int userID)
{
    QString sex;
    QSqlQuery query;
    query.prepare("SELECT sex FROM users WHERE id = :userID");
    query.bindValue(":userID", userID);
    query.exec();
    if (query.next())
    {
        sex = query.value(0).toString();
    }
    return sex;
}

QStringList Database::GetUserNicknames() {
    QStringList nicknames;
    QSqlQuery query("SELECT nickname FROM users ORDER BY nickname");
    query.exec();
    while (query.next()) {
        nicknames.append(query.value(0).toString());
    }
    return nicknames;
}


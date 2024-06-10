#ifndef CHAT_H
#define CHAT_H

#include <QString>
#include <QList>

#include "message.h"

///
/// \brief Класс Чат
///
class Chat
{
    //публичные методы
public:
    ///
    /// \brief Конструктор
    /// \param chatID - id чата из бд
    /// \param nazv - название чата
    /// \param members - список ников участников чата
    ///
    Chat(const int chatID, const QString& nazv, const QStringList& members);
    ///
    /// \brief Геттер id чата
    /// \return id чата
    ///
    int GetID();
    ///
    /// \brief Геттер названия чата
    /// \return название чата
    ///
    QString GetNazv();
    ///
    /// \brief Геттер списка участников
    /// \return список ников участников
    ///
    QStringList GetMembers();
    ///
    /// \brief Геттер списка сообщений чата
    /// \return - список соообщений
    ///
    QList<Message*> GetMessages();
    ///
    /// \brief Добавить новое сообщение в чат
    /// \param m - объект типа Message
    ///
    void AddMessage(Message* m);
    ///
    /// \brief Получить дату и время отправки последнего сообщения в чате
    /// \return строка с датой и времененем
    ///
    QString GetLastMessageDateTime();

    //приватные поля
private:
    ///
    /// \brief id чата
    ///
    int chatID;
    ///
    /// \brief Название чата
    ///
    QString nazv;
    ///
    /// \brief Строковый список ников участников чата
    ///
    QStringList membersNicks;
    ///
    /// \brief список сообщений
    ///
    QList<Message*> messages;
};

#endif // CHAT_H

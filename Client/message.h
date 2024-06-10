#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

///
/// \brief Класс текстового сообщения
///
class Message
{
    //Публичные методы
public:
    ///
    /// \brief Конструктор
    /// \param sender - ник отправителя
    /// \param text - текст сообщения
    /// \param date - дата и время отправки сообщения
    ///
    Message(const QString& sender, const QString& text, const QString& date);
    ///
    /// \brief Геттер отправителя
    /// \return ник отправителя
    ///
    QString GetSender();
    ///
    /// \brief Геттер текста
    /// \return текст сообщения
    ///
    QString GetText();
    ///
    /// \brief Геттер даты и времени
    /// \return дата и время отправки сообщения
    ///
    QString GetDate();
    ///
    /// \brief Получить сообщение в формате строки "[date] sender : text"
    /// \return строка сообщения
    ///
    QString ToString();

    //Приватные поля
private:
    ///
    /// \brief Ник отправителя
    ///
    QString sender;
    ///
    /// \brief Текст сообщения
    ///
    QString text;
    ///
    /// \brief Дата и время отправки сообщения
    ///
    QString date;
};

#endif // MESSAGE_H

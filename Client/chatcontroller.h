#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QDateTime>
#include "user.h"
#include "Commands.h"
#include "chat.h"

///
/// \brief Класс контроллер чатов
///
class ChatController : public QObject
{
    Q_OBJECT
    //Публичные методы
public:
    ///
    /// \brief Конструктор
    /// \param user - указатель на обьект Пользователь
    /// \param parent
    ///
    ChatController(User* user, QObject *parent = nullptr);
    ///
    /// \brief Сеттер активного чата
    /// \param chatID - id чата
    ///
    void SetActiveChat(int chatID);
    ///
    /// \brief Геттер id активного чата
    /// \return id
    ///
    int GetActiveChatID();
    ///
    /// \brief Геттер названия чата по id
    /// \param chatID - id чата
    /// \return строковое название чата
    ///
    QString GetChatNazv(int chatID);
    ///
    /// \brief Геттер списка участников чата
    /// \param chatID - id чата
    /// \return список ников участников чата
    ///
    QStringList GetChatMembers(int chatID);
    ///
    /// \brief Отправить новое сообщение в текущий активный чат
    /// \param text - текст сообщения
    ///
    void SendMessage(const QString& text);
    ///
    /// \brief Отправить на сервер запрос о создании группового чата
    /// \param nazv - название чата
    /// \param members - список ников участников чата
    ///
    void CreateGroupChat(const QString& nazv, QStringList members);
    ///
    /// \brief Отправить на сервер запрос о создании личного чата
    /// \param member - ник собеседника
    ///
    void CreatePersonalChat(const QString& member);
    ///
    /// \brief Осуществить подключение пользователя к серверу
    /// \param addr - адрес сервера
    /// \param port - номер порта сервера
    /// \return 1 - подключение успешно, 0 - нет
    ///
    bool ConnectToServer(const QString& addr, int port);
    ///
    /// \brief Отправить на сервер запрос об авторизации пользователя
    /// \param nickname - никнейм пользователя
    /// \param password - пароль пользователя
    ///
    void Login(const QString& nickname, const QString& password);
    ///
    /// \brief Отправить на сервер запрос о регистрации пользователя
    /// \param nickname - никнейм пользователя
    /// \param name - имя пользователя
    /// \param sex - пол пользователя
    /// \param password - пароль пользователя
    ///
    void SignUp(const QString& nickname, const QString& name, const QString& sex, const QString& password);
    ///
    /// \brief Отправить на сервер запрос истории чатов пользователя
    ///
    void RequestChatHistory();
    ///
    /// \brief Отправить на сервер запрос списка пользователей мессенджера
    ///
    void RequestUserlist();
    ///
    /// \brief Получить список сообщений текущего активного чата
    /// \return список сообщений в формате строк
    ///
    QStringList GetActiveChatMessages();
    ///
    /// \brief Получить список чатов пользователя
    /// \return Список чатов в виде пар <ID чата, Название чата>
    ///
    QList<QPair<int, QString>> GetChatsList();

    //Сигналы
signals:
    ///
    /// \brief Сигнал об успешной авторизации
    ///
    void SuccessfulLogin();
    ///
    /// \brief Сигнал о провальной авторизации
    ///
    void FailedLogin();
    ///
    /// \brief Сигнал об успешной регистрации
    ///
    void SuccessfulSignUp();
    ///
    /// \brief Сигнал о провальной регистрации
    ///
    void FailedSignUp();
    ///
    /// \brief Сигнал о получении списка пользователей от сервера
    /// \param users - список ников пользователей
    ///
    void UserlistReceived(QStringList users);
    ///
    /// \brief Сигнал об обновлении списка чатов
    /// \param Обновленный список чатов
    ///
    void ChatsListUpdated(QList<QPair<int, QString>> chats);
    ///
    /// \brief Сигнал о поступлении нового сообщения
    /// \param chatID - id чата, в который пришло сообщение
    ///
    void NewMessage(int chatID);
    ///
    /// \brief Сигнал об отключении клиента от сервера
    ///
    void Disconnection();
    ///
    /// \brief Сигнал о провальной попытке создания чата
    ///
    void FailedNewChat();

    //Приватные слоты
private slots:
    ///
    /// \brief Обрабочик входящей команды от сервера
    /// \param in - поток данных
    ///
    void HandleNewCommand(QDataStream& in);
    ///
    /// \brief Обработчик отключения клиента от сервера
    ///
    void HandleClientDisconnected();

    //Приватные методы
private:
    ///
    /// \brief Метод сортировки списка чатов в дате получения последнего сообщения
    ///
    void SortChats();
    ///
    /// \brief Принять входящее сообщение и добавить в чат
    /// \param in - поток данных с сообщением
    ///
    void ProcessIncomingMessage(QDataStream& in);
    ///
    /// \brief Принять историю сообщений чата от сервера
    /// \param in - поток данных с информацией о чате и сообщениями
    ///
    void LoadChatHistory(QDataStream& in);
    ///
    /// \brief Добавить новый чат, полученный от сервера
    /// \param in - поток данных с информацией о чате
    ///
    void AddNewChat(QDataStream& in);
    ///
    /// \brief Обработать сообщение об успешной авторизации
    /// \param in - поток данных с id, ником и полом пользователя
    ///
    void ProcessLoginSuccess(QDataStream& in);
    ///
    /// \brief Обработать сообщение об провальной авторизации
    /// \param in
    ///
    void ProcessLoginFail(QDataStream& in);
    ///
    /// \brief Обработать сообщение об успешной регистрации
    /// \param in
    ///
    void ProcessSignUpSuccess(QDataStream& in);
    ///
    /// \brief Обработать сообщение о провальной регистрации
    /// \param in
    ///
    void ProcessSignUpFail(QDataStream& in);
    ///
    /// \brief Обработать полученный от сервера список пользователей
    /// \param in - поток данных со списком ников пользователей
    ///
    void ProcessReceivedUserlist(QDataStream& in);
    ///
    /// \brief Обрабоать сообщение о провальной попытке создания чата
    /// \param in
    ///
    void ProcessNewChatFail(QDataStream& in);

    //Приватные поля
private:
    ///
    /// \brief Объект пользователя
    ///
    User* user;
    ///
    /// \brief Список чатов
    ///
    QList<Chat*> chats;
    ///
    /// \brief id активного чата
    ///
    int activeChatID;
    ///
    /// \brief массив данных, используемый для отправки сообщений серверу
    ///
    QByteArray data;
};

#endif // CHATCONTROLLER_H

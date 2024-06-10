#ifndef COMMANDS_H
#define COMMANDS_H

///
/// \brief Перечисление передаваемых команд
///
enum Commands
{
    IncomingMessage, //входящее сообщение
    OutcomingMessage, //исходящее сообщение
    SignUpRequest, //запрос регистрации
    SignUpSuccess, //успешная регистрация
    SignUpFail, //провальная регистрация
    LogInRequest, //запрос на авторизацию
    LogInSuccess, //успешная авторизация
    LogInFail, //провальная авторизация
    NewChatRequest, //запрос на создание чата
    NewChatFail, //провал содания чата
    NewChat, //рассылка нового чата
    UserlistRequest, //запрос списка пользователей
    Userlist, //ответ на запрос списка пользователей
    ChatHistoryRequest, //запрос истории чатов сообщений
    ChatHistory //ответ на запрос истории сообщений
};

#endif // COMMANDS_H

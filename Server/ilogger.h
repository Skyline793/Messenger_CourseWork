#ifndef ILOGGER_H
#define ILOGGER_H

#include <QString>

///
/// \brief Интерфейс логгера событий сервера
///
class ILogger {
    //публичные методы
public:
    ///
    /// \brief Логирование запуска сервера
    /// \param port - порт сервера
    ///
    virtual void LogStart(const QString &port) = 0;
    ///
    /// \brief Логирование нового подключения
    /// \param clientInfo - данные клиента
    ///
    virtual void LogConnection(const QString &clientInfo) = 0;
    ///
    /// \brief Логирование отключения клиента
    /// \param clientInfo - данные клиента
    ///
    virtual void LogDisconnection(const QString &clientInfo) = 0;
};

#endif // ILOGGER_H

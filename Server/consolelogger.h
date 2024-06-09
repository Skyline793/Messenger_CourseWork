#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "ilogger.h"

///
/// \brief Класс логгера в консоль
///
class ConsoleLogger : public ILogger {
public:
    ///
    /// \brief Логирование запуска сервера
    /// \param port - порт сервера
    ///
    virtual void LogStart(const QString &port);
    ///
    /// \brief Логирование нового подключения
    /// \param clientInfo - данные клиента
    ///
    virtual void LogConnection(const QString &clientInfo);
    ///
    /// \brief Логирование отключения клиента
    /// \param clientInfo - данные клиента
    ///
    virtual void LogDisconnection(const QString &clientInfo);
};

#endif // CONSOLELOGGER_H

#ifndef TXTLOGGER_H
#define TXTLOGGER_H

#include "ilogger.h"

///
/// \brief Класс логгера в текстовый файл
///
class TxtLogger : public ILogger {
public:
    TxtLogger();
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

private:
    ///
    /// \brief Сгенерировать имя файла
    /// \return имя файла
    ///
    QString GenerateLogFileName();

    ///
    /// \brief имя файла с логами
    ///
    QString logFileName;
};

#endif // TXTLOGGER_H

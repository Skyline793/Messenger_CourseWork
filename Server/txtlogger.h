#ifndef TXTLOGGER_H
#define TXTLOGGER_H

#include <QFile>
#include <QDateTime>
#include <QDebug>

#include "ilogger.h"

///
/// \brief Класс логгера в текстовый файл
///
class TxtLogger : public ILogger {
     //публичные методы
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

    //приватные методы
private:
    ///
    /// \brief Сгенерировать имя файла
    /// \return имя файла
    ///
    QString GenerateLogFileName();

    //приватные поля
private:
    ///
    /// \brief имя файла с логами
    ///
    QString logFileName;
};

#endif // TXTLOGGER_H

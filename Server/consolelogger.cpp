#include "consolelogger.h"
#include <QDebug>
#include <QDateTime>

void ConsoleLogger::LogStart(const QString &port)
{
    qDebug() << QDateTime::currentDateTime().toString() << " - Сервер запущен на порту: " << port;
}

void ConsoleLogger::LogConnection(const QString &clientInfo) {
    qDebug() << QDateTime::currentDateTime().toString() << " - Клиент подключился" << clientInfo;
}

void ConsoleLogger::LogDisconnection(const QString &clientInfo) {
    qDebug() << QDateTime::currentDateTime().toString() << " - Клиент отключился" << clientInfo;
}

#include "txtlogger.h"

TxtLogger::TxtLogger() {
    logFileName = GenerateLogFileName();
}

void TxtLogger::LogStart(const QString &port)
{
    QFile file(logFileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString() << " - Сервер запущен на порту: " << port << "\n";
    }
}

void TxtLogger::LogConnection(const QString &clientInfo) {
    QFile file(logFileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString() << " - Клиент подключился: " << clientInfo << "\n";
    }
}

void TxtLogger:: LogDisconnection(const QString &clientInfo) {
    QFile file(logFileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString() << " - Клиент отключился: " << clientInfo << "\n";
    }
}

QString TxtLogger::GenerateLogFileName() {
    int index = 1;
    QString fileName;
    do {
        fileName = QString("ServerLogs%1.txt").arg(index);
        index++;
    } while (QFile::exists(fileName));
    return fileName;
}

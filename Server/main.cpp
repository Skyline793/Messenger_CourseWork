#include <QCoreApplication>

#include "server.h"
#include "consolelogger.h"
#include "txtlogger.h"
#include "database.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Database db("messengerDB.db");
    if(!db.IsOpen())
        return 0;
    Server server(&db);
    ConsoleLogger consoleLogger;
    TxtLogger fileLogger;
    server.AddLogger(&consoleLogger);
    server.AddLogger(&fileLogger);
    server.StartServer(8080);

    return a.exec();
}

#include "messengerwindow.h"
#include "loginwindow.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->show();
    QObject::connect(loginWindow, &LoginWindow::AuthorizationSucceded, [&](ChatController *cc) {
        qDebug() << "FEFEFE";
        MessengerWindow *messengerWindow = new MessengerWindow(cc);
        messengerWindow->show();
    });
    return a.exec();
}

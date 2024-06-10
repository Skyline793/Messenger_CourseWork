#include "messengerwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->show();
    QObject::connect(loginWindow, &LoginWindow::AuthorizationSucceded, [&](ChatController *cc) {
        MessengerWindow *messengerWindow = new MessengerWindow(cc);
        messengerWindow->show();
    });
    return a.exec();
}

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTcpSocket>
#include <chatcontroller.h>
#include "loginsettings.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void AuthorizationSucceded(ChatController* cc);

private slots:
    void HandleSuccesfulLogin();
    void HandleFailedLogin();
    void HandleSuccessfulSignUp();
    void HandleFailedSignUp();

    void on_connectToServer_pushButton_clicked();

    void on_login_pushButton_clicked();

    void on_resetSettings_pushButton_clicked();

    void on_signup_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    ChatController* cc;
    LoginSettings* settings;
};

#endif // LOGINWINDOW_H

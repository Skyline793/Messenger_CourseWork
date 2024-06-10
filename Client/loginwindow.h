#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>

#include <chatcontroller.h>
#include "loginsettings.h"
#include "Commands.h"

namespace Ui {
class LoginWindow;
}

///
/// \brief Класс формы авторизации/регистрации
///
class LoginWindow : public QDialog
{
    Q_OBJECT

    //публичные методы
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    //сигналы
signals:
    ///
    /// \brief Сигнал об успешном завершении авторизации
    /// \param cc - объект контроллера чатов
    ///
    void AuthorizationSucceded(ChatController* cc);

    //приватные слоты
private slots:
    ///
    /// \brief Обработчик сигнала об успешной авторизации от контроллера чатов
    ///
    void HandleSuccesfulLogin();
    ///
    /// \brief Обработчик сигнала о провальной авторизации от контроллера чатов
    ///
    void HandleFailedLogin();
    ///
    /// \brief Обработчик сигнала об успешной регистрации от контроллера чатов
    ///
    void HandleSuccessfulSignUp();
    ///
    /// \brief Обработчик сигнала о провальной регистрации от контроллера чатов
    ///
    void HandleFailedSignUp();
    ///
    /// \brief Обработчик нажатия на кнопку подключения к серверу
    ///
    void on_connectToServer_pushButton_clicked();
    ///
    /// \brief Обработчик нажатия на кнопку Войти
    ///
    void on_login_pushButton_clicked();
    ///
    /// \brief Обработчик нажатия на кнопку сброса настроек
    ///
    void on_resetSettings_pushButton_clicked();
    ///
    /// \brief Обработчик нажатияна кнопку Зарегистрироваться
    ///
    void on_signup_pushButton_clicked();

    //приватные поля
private:
    Ui::LoginWindow *ui;
    ///
    /// \brief Объект контроллера чатов
    ///
    ChatController* cc;
};

#endif // LOGINWINDOW_H

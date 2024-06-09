#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "Commands.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    cc = new ChatController(new User());
    connect(cc, &ChatController::SuccessfulLogin, this, &LoginWindow::HandleSuccesfulLogin);
    connect(cc, &ChatController::FailedLogin, this, &LoginWindow::HandleFailedLogin);
    connect(cc, &ChatController::SuccessfulSignUp, this, &LoginWindow::HandleSuccessfulSignUp);
    connect(cc, &ChatController::FailedSignUp, this, &LoginWindow::HandleFailedSignUp);
    settings = new LoginSettings();
    ui->authorization_tabWidget->setCurrentIndex(0);
    if(settings->IsConfigured())
    {
        ui->serverAddr_lineEdit->setText(settings->GetServerAddress());
        ui->serverPort_lineEdit->setText(QString::number(settings->GetServerPort()));
        ui->loginNickname_lineEdit->setText(settings->GetNickname());
        ui->loginPassword_lineEdit->setText(settings->GetPassword());
        ui->resetSettings_pushButton->setEnabled(true);
    }
    ui->authorization_tabWidget->setEnabled(false);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete settings;
}

void LoginWindow::HandleSuccesfulLogin()
{
    QMessageBox::information(this, "Вход", "Вы успешно вошли в свой аккаунт");
    emit AuthorizationSucceded(cc);
    this->close();
}

void LoginWindow::HandleFailedLogin()
{
    QMessageBox::critical(this, "Ошибка входа", "Не удалось войти в аккаунт. Проверьте корректность данных");
    ui->loginNickname_lineEdit->clear();
    ui->loginPassword_lineEdit->clear();
}

void LoginWindow::HandleSuccessfulSignUp()
{
    QMessageBox::information(this, "Вход", "Вы успешно зарегистрировались");
    ui->signupNickname_lineEdit->clear();
    ui->signupPassword_lineEdit->clear();
    ui->signupName_lineEdit->clear();
    ui->signupPasswordRepeat_lineEdit->clear();
    ui->sex_comboBox->setCurrentIndex(-1);
    ui->authorization_tabWidget->setCurrentIndex(0);
}

void LoginWindow::HandleFailedSignUp()
{
    QMessageBox::critical(this, "Ошибка регистрации", "Не удалось зарегистрироваться. Возможно, аккаунт с таким ником уже существует");
    ui->signupNickname_lineEdit->clear();
    ui->signupPassword_lineEdit->clear();
    ui->signupName_lineEdit->clear();
    ui->signupPasswordRepeat_lineEdit->clear();
    ui->sex_comboBox->setCurrentIndex(-1);
    ui->authorization_tabWidget->setCurrentIndex(0);
}




void LoginWindow::on_connectToServer_pushButton_clicked()
{
    QString addr = ui->serverAddr_lineEdit->text().trimmed();
    if(addr.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Адрес сервера не указан");
        return;
    }
    bool ok;
    int port = ui->serverPort_lineEdit->text().trimmed().toInt(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Ошибка", "Порт сервера не указан или указан неверно");
        ui->serverPort_lineEdit->clear();
        return;
    }
    if(!cc->ConnectToServer(addr, port))
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к серверу. Проверьте адрес и порт сервера");
        ui->serverAddr_lineEdit->clear();
        ui->serverPort_lineEdit->clear();
        return;
    }
    QMessageBox::information(this, "Успех", "Соединение с сервером установлено");
    ui->authorization_tabWidget->setEnabled(true);
    ui->serverAddr_lineEdit->setEnabled(false);
    ui->serverPort_lineEdit->setEnabled(false);
    ui->connectToServer_pushButton->setEnabled(false);
}


void LoginWindow::on_login_pushButton_clicked()
{
    QString nickname = ui->loginNickname_lineEdit->text().trimmed();
    if(nickname.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Никнейм пользователя не указан");
        return;
    }
    QString password = ui->loginPassword_lineEdit->text().trimmed();
    if(nickname.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Пароль пользователя не указан");
        return;
    }
    if(ui->save_checkBox->isChecked())
    {
        settings->SetServerAddress(ui->serverAddr_lineEdit->text());
        settings->SetServerPort(ui->serverPort_lineEdit->text().toInt());
        settings->SetNickname(nickname);
        settings->SetPassword(password);
        settings->SaveSettings();
    }
    cc->Login(nickname, password);
}


void LoginWindow::on_resetSettings_pushButton_clicked()
{
    settings->ResetSettings();
    ui->serverAddr_lineEdit->clear();
    ui->serverPort_lineEdit->clear();
    ui->loginNickname_lineEdit->clear();
    ui->loginPassword_lineEdit->clear();
}



void LoginWindow::on_signup_pushButton_clicked()
{

    QString nickname = ui->signupNickname_lineEdit->text().trimmed();
    if(nickname.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Никнейм пользователя не указан");
        return;
    }
    QString name = ui->signupName_lineEdit->text().trimmed();
    if(name.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Имя пользователя не указано");
        return;
    }
    if(ui->sex_comboBox->currentIndex() == -1)
    {
        QMessageBox::critical(this, "Ошибка", "Пол не выбран");
        return;
    }
    QString sex = ui->sex_comboBox->currentText();
    QString password1 = ui->signupPassword_lineEdit->text().trimmed();
    if(password1.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Пароль пользователя не указан");
        return;
    }
    QString password2 = ui->signupPasswordRepeat_lineEdit->text().trimmed();
    if(password2.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Введите пароль повторно");
        return;
    }
    if(password1 != password2)
    {
        QMessageBox::critical(this, "Ошибка", "Пароли не совпадают");
        ui->signupPassword_lineEdit->clear();
        ui->signupPasswordRepeat_lineEdit->clear();
        return;
    }
    cc->SignUp(nickname, name, sex, password1);
    ui->signupNickname_lineEdit->clear();
    ui->signupName_lineEdit->clear();
    ui->signupPassword_lineEdit->clear();
    ui->signupPasswordRepeat_lineEdit->clear();
    ui->sex_comboBox->setCurrentIndex(-1);

}


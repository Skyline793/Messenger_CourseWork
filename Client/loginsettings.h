#ifndef LOGINSETTINGS_H
#define LOGINSETTINGS_H

#include <QString>
#include <QSettings>

///
/// \brief Класс-синглтон для сохранения учетных данных пользователя и адреса/порта сервера
///
class LoginSettings {
    //Публичные методы
public:
    ///
    /// \brief Статический геттер объекта настроек
    /// \return указатель на объект настроек
    ///
    static LoginSettings *GetInstance();
    ~LoginSettings();
    ///
    /// \brief Сеттер адреса сервера
    /// \param address - ipv4 адрес сервера
    ///
    void SetServerAddress(const QString &address);
    ///
    /// \brief Геттер адреса сервера
    /// \return ipv4 адрес сервера
    ///
    QString GetServerAddress();
    ///
    /// \brief Сеттер порта сервера
    /// \param port - номер порта
    ///
    void SetServerPort(int port);
    ///
    /// \brief Геттер порта сервера
    /// \return номер порта
    ///
    int GetServerPort();
    ///
    /// \brief Сеттер никнейма пользователя
    /// \param nicknamе - никнейм
    ///
    void SetNickname(const QString &nickname);
    ///
    /// \brief Геттер никнейма пользователя
    /// \return никнейм
    ///
    QString GetNickname();
    ///
    /// \brief Сеттер пароля пользователя
    /// \param password - пароль пользователя
    ///
    void SetPassword(const QString &password);
    ///
    /// \brief Геттер пароля пользователя
    /// \return  пароль
    ///
    QString GetPassword();
    ///
    /// \brief Сохранить текущие параметры
    ///
    void SaveSettings();
    ///
    /// \brief Загрузить параметры
    ///
    void LoadSettings();
    ///
    /// \brief Проверить, сохранены ли пользовательские параметры
    /// \return 1 - сохранены, 0 - нет
    ///
    bool IsConfigured();
    ///
    /// \brief Сбросить пользовательские параметры
    ///
    void ResetSettings();

    //Приватные методы
private:
    ///
    /// \brief Приватный конструктор
    /// \param organization
    /// \param application
    ///
    LoginSettings(const QString& organization = "MyApp", const QString& application = "MessengerClient");

    //Приватные поля
private:
    ///
    /// \brief статический экземпляр объекта настроек
    ///
    static LoginSettings* instance;
    ///
    /// \brief объект класса QSettings, осуществляющий сохранение параметров
    ///
    QSettings* settings;
    ///
    /// \brief Адрес сервера
    ///
    QString serverAddress;
    ///
    /// \brief номер порта сервера
    ///
    int serverPort;
    ///
    /// \brief Никнейм пользователя
    ///
    QString nickname;
    ///
    /// \brief Пароль пользователя
    ///
    QString password;
};

#endif // LOGINSETTINGS_H


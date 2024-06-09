#ifndef LOGINSETTINGS_H
#define LOGINSETTINGS_H

#include <QString>
#include <QSettings>

class LoginSettings {
public:
    LoginSettings(const QString& organization = "MyApp", const QString& application = "MessengerClient");
    ~LoginSettings();

    void SetServerAddress(const QString &address);
    QString GetServerAddress() const;

    void SetServerPort(int port);
    int GetServerPort() const;

    void SetNickname(const QString &nickname);
    QString GetNickname() const;

    void SetPassword(const QString &password);
    QString GetPassword() const;

    void SaveSettings() const;
    void LoadSettings();

    bool IsConfigured() const;
    void ResetSettings();

private:
    QString serverAddress;
    int serverPort;
    QString nickname;
    QString password;

    QSettings *settings;
};

#endif // LOGINSETTINGS_H


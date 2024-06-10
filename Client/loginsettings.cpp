#include "loginsettings.h"

LoginSettings* LoginSettings::instance = nullptr;

LoginSettings::LoginSettings(const QString& organization, const QString& application)
    : settings(new QSettings(organization, application)) {
    LoadSettings();
}

LoginSettings* LoginSettings::GetInstance()
{
    if(instance == nullptr)
        instance = new LoginSettings();
    return instance;
}

LoginSettings::~LoginSettings() {
    delete settings;
}

void LoginSettings::SetServerAddress(const QString &address) {
    serverAddress = address;
}

QString LoginSettings::GetServerAddress() {
    return serverAddress;
}

void LoginSettings::SetServerPort(int port) {
    serverPort = port;
}

int LoginSettings::GetServerPort() {
    return serverPort;
}

void LoginSettings::SetNickname(const QString &nickname) {
    this->nickname = nickname;
}

QString LoginSettings::GetNickname() {
    return nickname;
}

void LoginSettings::SetPassword(const QString &password) {
    this->password = password;
}

QString LoginSettings::GetPassword() {
    return password;
}

void LoginSettings::SaveSettings() {
    settings->setValue("server/address", serverAddress);
    settings->setValue("server/port", serverPort);
    settings->setValue("user/nickname", nickname);
    settings->setValue("user/password", password);
}

void LoginSettings::LoadSettings() {
    serverAddress = settings->value("server/address", "").toString();
    serverPort = settings->value("server/port", -1).toInt();
    nickname = settings->value("user/nickname", "").toString();
    password = settings->value("user/password", "").toString();
}

bool LoginSettings::IsConfigured() {
    return settings->contains("server/address") && settings->contains("server/port")
            && settings->contains("user/nickname") && settings->contains("user/password");
}

void LoginSettings::ResetSettings() {
    settings->clear();
    serverAddress.clear();
    serverPort = -1;
    nickname.clear();
    password.clear();
}

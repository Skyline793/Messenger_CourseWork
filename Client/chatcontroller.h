#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "user.h"
#include "Commands.h"
#include "chat.h"

class ChatController : public QObject
{
    Q_OBJECT
public:
    explicit ChatController(User* user, QObject *parent = nullptr);
    void SetActiveChat(int chatID);
    int GetActiveChatID();
    QString GetChatNazv(int chatID);
    QStringList GetChatMembers(int chatID);

    void SendMessage(const QString& text);
    void CreateGroupChat(QString nazv, QStringList members);
    void CreatePersonalChat(QString member);
    bool ConnectToServer(const QString& addr, int port);
    void Login(const QString& nickname, const QString& password);
    void SignUp(const QString& nickname, const QString& name, const QString& sex, const QString& password);
    void RequestChatHistory();
    void RequestUserlist();
    QStringList GetActiveChatMessages();
    QList<QPair<int, QString>> GetChatsList();

signals:
    void SuccessfulLogin();
    void FailedLogin();
    void SuccessfulSignUp();
    void FailedSignUp();
    void UserlistReceived(QStringList users);
    void ChatsListUpdated(QList<QPair<int, QString>> chats);
    void NewMessage(int chatID);
    void ClientDisconnected();
    void FailedNewChat();

public slots:
    void HandleNewCommand(QDataStream& in);
    void HandleClientDisconnected();

private:
    void SortChats();
    void ProcessIncomingMessage(QDataStream& in);
    void LoadChatHistory(QDataStream& in);
    void AddNewChat(QDataStream& in);
    void ProcessLoginSuccess(QDataStream& in);
    void ProcessLoginFail(QDataStream& in);
    void ProcessSignUpSuccess(QDataStream& in);
    void ProcessSignUpFail(QDataStream& in);
    void ProcessReceivedUserlist(QDataStream& in);
    void ProcessNewChatFail(QDataStream& in);


private:
    User* user;
    QList<Chat*> chats;
    int activeChatID;
    QByteArray data;

};

#endif // CHATCONTROLLER_H

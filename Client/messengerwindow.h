#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QMainWindow>
#include "chatcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MessengerWindow; }
QT_END_NAMESPACE

class MessengerWindow : public QMainWindow
{
    Q_OBJECT

public:
    MessengerWindow(QWidget *parent = nullptr);
    MessengerWindow(ChatController* cc, QWidget *parent = nullptr);
    ~MessengerWindow();

private slots:
    void HandleNewMessage(int chatID);
    void HandleDisconnection();
    void UpdateChatsListView(QList<QPair<int, QString>> chats);
    void HandleFailedNewChat();

    void on_chats_listView_clicked(const QModelIndex &index);
    void on_newMessage_lineEdit_textChanged(const QString &arg1);
    void on_send_pushButton_clicked();
    void on_newMessage_lineEdit_returnPressed();
    void on_chatInfo_pushButton_clicked();

    void on_newChat_pushButton_clicked();

private:
    void UpdateChat();
    void SendMessage();

    Ui::MessengerWindow *ui;
    ChatController* cc;
};
#endif // MESSENGERWINDOW_H

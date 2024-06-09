#ifndef CHATCREATIONWINDOW_H
#define CHATCREATIONWINDOW_H

#include <QDialog>
#include "chatcontroller.h"

namespace Ui {
class ChatCreationWindow;
}

class ChatCreationWindow : public QDialog
{
    Q_OBJECT

public:
    ChatCreationWindow(ChatController* cc, QWidget *parent = nullptr);
    ~ChatCreationWindow();

private slots:
    void LoadUserlist(QStringList users);

    void on_personal_radioButton_clicked();

    void on_group_radioButton_clicked();

    void on_create_pushButton_clicked();

private:
    void CreatePersonalChat();
    void CreateGroupChat();
    Ui::ChatCreationWindow *ui;
    ChatController* cc;
};

#endif // CHATCREATIONWINDOW_H

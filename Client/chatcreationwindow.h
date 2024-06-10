#ifndef CHATCREATIONWINDOW_H
#define CHATCREATIONWINDOW_H

#include <QDialog>
#include <QStringListModel>
#include <QMessageBox>

#include "chatcontroller.h"

namespace Ui {
class ChatCreationWindow;
}

///
/// \brief Класс формы создания чата
///
class ChatCreationWindow : public QDialog
{
    Q_OBJECT
    //публичные методы
public:
    ChatCreationWindow(ChatController* cc, QWidget *parent = nullptr);
    ~ChatCreationWindow();

    //приватные слоты
private slots:
    ///
    /// \brief Загрузить список пользователей, полученный от сервера
    /// \param users - список ников пользователей
    ///
    void LoadUserlist(QStringList users);

    ///
    /// \brief обработчик клика по радиокнопке "Личный чат"
    ///
    void on_personal_radioButton_clicked();
    ///
    /// \brief Обработчик клика по радикнопке "Групповой чат"
    ///
    void on_group_radioButton_clicked();
    ///
    /// \brief Обработчик клика по кнопке "Создать"
    ///
    void on_create_pushButton_clicked();

    //приватные методы
private:
    ///
    /// \brief Метод инициирования запроса на создания личного чата
    ///
    void CreatePersonalChat();
    ///
    /// \brief  Метод инициирования запроса на создания группового чата
    ///
    void CreateGroupChat();

    //приватные поля
private:
    Ui::ChatCreationWindow *ui;
    ///
    /// \brief Объект контроллера чатов
    ///
    ChatController* cc;
};

#endif // CHATCREATIONWINDOW_H

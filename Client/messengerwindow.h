#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>

#include "chatcontroller.h"
#include "chatcreationwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MessengerWindow; }
QT_END_NAMESPACE

///
/// \brief Класс основной формы мессенджера
///
class MessengerWindow : public QMainWindow
{
    Q_OBJECT

    //публичные методы
public:
    MessengerWindow(ChatController* cc, QWidget *parent = nullptr);
    ~MessengerWindow();

    //приватные слоты
private slots:
    ///
    /// \brief Обработчик сигнала о новом сообщении от контроллера чатов
    /// \param chatID - id чата
    ///
    void HandleNewMessage(int chatID);
    ///
    /// \brief Обработчик сигнала об отключении от сервера
    ///
    void HandleDisconnection();
    ///
    /// \brief Обрабочик сигнала об обновлении списка чатов, обновляет модель ListView
    /// \param chats - список чатов
    ///
    void HandleChatsListUpdated(QList<QPair<int, QString>> chats);
    ///
    /// \brief Обработчик сигнала о провале попытке создания чата
    ///
    void HandleFailedNewChat();
    ///
    /// \brief Обработчик нажатия на элемент ListView
    /// \param index
    ///
    void on_chats_listView_clicked(const QModelIndex &index);
    ///
    /// \brief обработчик изменения текста поля ввода нового сообщения
    /// \param arg1 - текст
    ///
    void on_newMessage_lineEdit_textChanged(const QString &arg1);
    ///
    /// \brief Обработчик клика на кнопку отправки сообщения
    ///
    void on_send_pushButton_clicked();
    ///
    /// \brief Обработчик нажатия Enter на поле ввода нового сообщения
    ///
    void on_newMessage_lineEdit_returnPressed();
    ///
    /// \brief Обработчик клика по кнопке информации о чате
    ///
    void on_chatInfo_pushButton_clicked();
    ///
    /// \brief Обработчик клика по кнопке "Новый чат"
    ///
    void on_newChat_pushButton_clicked();

    //приватные методы
private:
    ///
    /// \brief Обновить поле отображения сообщений чата
    ///
    void UpdateChat();
    ///
    /// \brief Инициировать отправку сообщения
    ///
    void SendMessage();

    //приватные поля
private:
    Ui::MessengerWindow *ui;
    ///
    /// \brief Объект контроллера чатов
    ///
    ChatController* cc;
};
#endif // MESSENGERWINDOW_H

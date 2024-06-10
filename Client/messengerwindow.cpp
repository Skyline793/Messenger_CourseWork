#include "messengerwindow.h"
#include "ui_messengerwindow.h"

MessengerWindow::MessengerWindow(ChatController *cc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MessengerWindow)
{
    ui->setupUi(this);
    this->cc = cc;
    cc->setParent(this);
    cc->RequestChatHistory();
    connect(cc, &ChatController::ChatsListUpdated, this, &MessengerWindow::HandleChatsListUpdated);
    connect(cc, &ChatController::NewMessage, this, &MessengerWindow::HandleNewMessage);
    connect(cc, &ChatController::Disconnection, this, &MessengerWindow::HandleDisconnection);
    connect(cc, &ChatController::FailedNewChat, this, &MessengerWindow::HandleFailedNewChat);
}

MessengerWindow::~MessengerWindow()
{
    delete ui;
}

void MessengerWindow::HandleNewMessage(int chatID)
{
    if(chatID == cc->GetActiveChatID())
    {
        UpdateChat();
    }
    else
    {
        QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->chats_listView->model());
        for (int i = 0; i < model->rowCount(); ++i) {
            QStandardItem *item = model->item(i);
            if (item->data(Qt::UserRole).toInt() == chatID) {
                item->setForeground(QBrush(Qt::green));
                break;
            }
        }
    }
}

void MessengerWindow::HandleDisconnection()
{
    QMessageBox::critical(this, "Отключение", "Вы отключены от сервера");
    this->close();
}

void MessengerWindow::HandleChatsListUpdated(QList<QPair<int, QString>> chats)
{
    QAbstractItemModel* oldModel = ui->chats_listView->model();
    QStandardItemModel *model = new QStandardItemModel(this);

    foreach(auto &chat, chats) {
        QStandardItem *item = new QStandardItem(chat.second);
        item->setData(chat.first, Qt::UserRole);
        model->appendRow(item);
    }

    ui->chats_listView->setModel(model);
    ui->chats_listView->setSelectionMode(QAbstractItemView::SingleSelection);
    delete oldModel;
}

void MessengerWindow::HandleFailedNewChat()
{
    QMessageBox::critical(this, "Ошибка", "Не удалось содать чат. Такой чат уже существует");
}

void MessengerWindow::on_chats_listView_clicked(const QModelIndex &index)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->chats_listView->model());
    QStandardItem* item = model->itemFromIndex(index);
    item->setForeground(QBrush(Qt::black));
    int chatID = index.data(Qt::UserRole).toInt();
    QString chatName = index.data().toString();
    ui->chatName_label->setText(chatName);
    cc->SetActiveChat(chatID);
    UpdateChat();
}

void MessengerWindow::UpdateChat()
{
    ui->textBrowser->clear();
    QStringList messages = cc->GetActiveChatMessages();
    if(messages.isEmpty())
    {
        ui->textBrowser->setAlignment(Qt::Alignment(Qt::AlignHCenter));
        ui->textBrowser->append("В чате еще нет сообщений");
        return;
    }
    ui->textBrowser->setAlignment(Qt::Alignment(Qt::AlignLeft));
    foreach(QString message, messages)
    {
        ui->textBrowser->append(message);
    }
}

void MessengerWindow::SendMessage()
{
    if(cc->GetActiveChatID() == -1)
        return;
    QString text = ui->newMessage_lineEdit->text().trimmed();
    if(text.isEmpty())
        return;
    cc->SendMessage(text);
    ui->newMessage_lineEdit->clear();
}


void MessengerWindow::on_newMessage_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.trimmed().isEmpty())
        ui->send_pushButton->setEnabled(false);
    else
        ui->send_pushButton->setEnabled(true);
}


void MessengerWindow::on_send_pushButton_clicked()
{
    SendMessage();
}


void MessengerWindow::on_newMessage_lineEdit_returnPressed()
{
    SendMessage();
}


void MessengerWindow::on_chatInfo_pushButton_clicked()
{
    QString nazv = cc->GetChatNazv(cc->GetActiveChatID());
    QStringList members = cc->GetChatMembers(cc->GetActiveChatID());
    QString info = QString("Чат '%1'\nУчастники:\n%2").arg(nazv, members.join("\n"));
    QMessageBox::information(this, "Инфо", info);
}


void MessengerWindow::on_newChat_pushButton_clicked()
{
   ChatCreationWindow* window = new ChatCreationWindow(cc, this);
   window->show();
}


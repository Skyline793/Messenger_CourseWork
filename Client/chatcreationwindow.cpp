#include "chatcreationwindow.h"
#include "ui_chatcreationwindow.h"

ChatCreationWindow::ChatCreationWindow(ChatController* cc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatCreationWindow)
{
    ui->setupUi(this);
    this->cc = cc;
    connect(cc, &ChatController::UserlistReceived, this, &ChatCreationWindow::LoadUserlist);
    this->cc->RequestUserlist();
    ui->personal_radioButton->setChecked(true);
    emit ui->personal_radioButton->clicked();
}

ChatCreationWindow::~ChatCreationWindow()
{
    delete ui;
}

void ChatCreationWindow::LoadUserlist(QStringList users)
{
    QAbstractItemModel* oldModel = ui->users_listView->model();
    QStringListModel* model = new QStringListModel(this);
    model->setStringList(users);
    ui->users_listView->setModel(model);
    delete oldModel;
}

void ChatCreationWindow::on_personal_radioButton_clicked()
{
    ui->users_listView->clearSelection();
    ui->nazv_lineEdit->setEnabled(false);
    ui->nazv_lineEdit->clear();
    ui->nazv_lineEdit->setPlaceholderText("");
    ui->users_listView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void ChatCreationWindow::on_group_radioButton_clicked()
{
    ui->users_listView->clearSelection();
    ui->nazv_lineEdit->setEnabled(true);
    ui->nazv_lineEdit->clear();
    ui->nazv_lineEdit->setPlaceholderText("Ведите название чата");
    ui->users_listView->setSelectionMode(QAbstractItemView::MultiSelection);
}

void ChatCreationWindow::on_create_pushButton_clicked()
{
    if(ui->personal_radioButton->isChecked())
    {
        CreatePersonalChat();
    }
    else if(ui->group_radioButton->isChecked())
    {
        CreateGroupChat();
    }
    this->close();
    delete this;
}

void ChatCreationWindow::CreatePersonalChat()
{
    QModelIndexList selectedIndexes = ui->users_listView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Не выбран ни один пользователь");
        return;
    }
    QString selectedUser = selectedIndexes[0].data().toString();
    cc->CreatePersonalChat(selectedUser);
}

void ChatCreationWindow::CreateGroupChat()
{
    QModelIndexList selectedIndexes = ui->users_listView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Не выбран ни один пользователь");
        return;
    }
    QStringList selectedUsers;
    foreach (const QModelIndex &selectedIndex, selectedIndexes) {
        QString nickname = selectedIndex.data().toString();
        selectedUsers.append(nickname);
    }
    QString nazv = ui->nazv_lineEdit->text().trimmed();
    if(nazv.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Введите название группового чата");
        return;
    }
    cc->CreateGroupChat(nazv, selectedUsers);
}




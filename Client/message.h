#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message
{
public:
    Message(QString sender, QString text, QString date);
    QString GetSender();
    QString GetText();
    QString GetDate();
    QString ToString();

private:
    QString sender;
    QString text;
    QString date;
};

#endif // MESSAGE_H

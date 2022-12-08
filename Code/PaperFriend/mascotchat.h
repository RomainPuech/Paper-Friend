#ifndef MASCOTCHAT_H
#define MASCOTCHAT_H
#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <string>
#include <vector>


class MascotChat
{
public:
    MascotChat(QScrollArea *area);
    void operator<<(std::string txt);
    void operator<<(QString txt);
    //getters
    QString get_last_message() const;

private:
    void add_message(QString txt);
    void add_message(std::string txt);
    QScrollArea *scrollArea;
};


#endif // MASCOTCHAT_H

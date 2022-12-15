#ifndef MASCOTCHAT_H
#define MASCOTCHAT_H
#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <string>
#include <vector>
#include <mascot.h>

class MascotChat
{
public:
    MascotChat(QScrollArea *area);
    void operator<<(std::string txt);
    void operator<<(QString txt);
    //getters
    QString get_last_message() const;
    QScrollArea* get_scrollArea();

private:
    //void add_message(QString txt);
    void add_message_mascot(QString txt);
    //void add_message(std::string txt);
    void add_message_mascot(std::string txt);
    QScrollArea *scrollArea;
    Mascot *mascot;
};


#endif // MASCOTCHAT_H

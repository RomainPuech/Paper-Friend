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
    void add_mascot();
    //getters
    QString get_last_message() const;
    QScrollArea* get_scrollArea();

private:
    void add_message(QString txt);
    void add_message(std::string txt);
    QScrollArea *scrollArea;
    Mascot *mascot;
};


class Message : public QLabel
{
public:
    Message();
    virtual void paintEvent( QPaintEvent* aEvent ) override;
};


#endif // MASCOTCHAT_H

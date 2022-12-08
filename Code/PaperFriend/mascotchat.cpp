#include "mascotchat.h"
#include <string>
#include<QLabel>
#include <QVBoxLayout>
MascotChat::MascotChat(QScrollArea *area):scrollArea(area)
{
    /*
    QLabel *label = new QLabel();
    label->setText(txt);
    messages.push_back(label);
    */
    QVBoxLayout *chat_layout = new QVBoxLayout();
    scrollArea->widget()->setLayout(chat_layout);
}


//getters
QString MascotChat::get_last_message() const{
    return QString();
    // to implement. Get last message from the scrollArea. Be careful if it is empty!
}

//public methods
void MascotChat::operator<<(std::string txt){
    add_message(txt);
}
void MascotChat::operator<<(QString txt){
    add_message(txt);
}

//private methods
void MascotChat::add_message(QString txt){
    QLabel *label = new QLabel();
    label->setText(txt);
    scrollArea->widget()->layout()->addWidget(label);
}

void MascotChat::add_message(std::string txt){
    add_message(QString::fromStdString(txt));
}



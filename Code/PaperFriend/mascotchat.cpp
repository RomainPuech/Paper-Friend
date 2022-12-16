#include "mascotchat.h"
#include "mascot.h"
#include "qpainter.h"
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
QScrollArea* MascotChat::get_scrollArea(){
    return scrollArea;
}
//public methods
void MascotChat::operator<<(std::string txt){
    add_message_mascot(txt);
    //add_message(txt);
}
void MascotChat::operator<<(QString txt){
    add_message_mascot(txt);
    //add_message(txt);
}

//private methods
/*void MascotChat::add_message(QString txt){
    QLabel *label = new QLabel();
    label->setText(txt);
    scrollArea->widget()->layout()->addWidget(label);
}*/
void MascotChat::add_message_mascot(QString txt){

    QHBoxLayout *test = new QHBoxLayout();

    QLabel *l = new QLabel;
    l->setTextFormat(Qt::RichText);
    l->setText("<img src=:/pictures/rsc/peaceout-resized.png align=middle height=\"100\">");
    l->setFixedWidth(100);
    // following commented code helps for debugging by showing the actual size of the label
    /*
    QPalette pali = QPalette();
    pali.setColor(QPalette::Window, Qt::green);
    l->setAutoFillBackground(true);
    l->setPalette(pali);
    */
    QLabel *l2 = new QLabel;
    l2->setTextFormat(Qt::RichText);
    l2->setText(txt);
    l2->setIndent(0);
    //for debug
    /*
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    l2->setAutoFillBackground(true);
    l2->setPalette(pal);
    */
    test->addWidget(l);
    test->addWidget(l2);
    QFrame *testu = new QFrame();
    testu->setLayout(test);
    scrollArea->widget()->layout()->addWidget(testu);
    //QLabel * textLabel = new QLabel();
    //QLabel * imageLabel = new QLabel();
    //imageLabel->setPixmap(QPixmap(":/pictures/rsc/peaceout-resized.png"));
    //textLabel->setText(txt);
    //scrollArea->widget()->layout()->addWidget(imageLabel);
    //scrollArea->widget()->layout()->addWidget(textLabel);
}

/*void MascotChat::add_message(std::string txt){
    add_message_mascot(QString::fromStdString(txt));
    add_message(QString::fromStdString(txt));
}*/
void MascotChat::add_message_mascot(std::string txt){
    add_message_mascot(QString::fromStdString(txt));}





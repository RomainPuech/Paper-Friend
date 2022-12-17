#include "mascotchat.h"
#include "mascot.h"
#include "qpainter.h"
#include <string>
#include<QLabel>
#include <QVBoxLayout>
#include <QPainterPath>
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


    QLabel *image_label = new QLabel;
    image_label->setTextFormat(Qt::RichText);
    image_label->setText("<img src=:/pictures/rsc/excited-resized.png align=middle height=\"85\">");
    image_label->setFixedWidth(85);
    // setting a background color helps for debugging by showing the actual size of the label
    /*
    QPalette pali = QPalette();
    pali.setColor(QPalette::Window, Qt::green);
    image_label->setAutoFillBackground(true);
    image_label->setPalette(pali);
    */

    Message *text_label = new Message();
    text_label->setTextFormat(Qt::RichText);
    text_label->setText(txt);

    scrollArea->widget()->layout()->addWidget(text_label);
    scrollArea->widget()->layout()->addWidget(image_label);


}

/*void MascotChat::add_message(std::string txt){
    add_message_mascot(QString::fromStdString(txt));
    add_message(QString::fromStdString(txt));
}*/
void MascotChat::add_message_mascot(std::string txt)
{
    add_message_mascot(QString::fromStdString(txt));
}

Message::Message()
{
    this->setStyleSheet("background-color: white; border: 1px solid white; border-radius:5px; border-bottom-left-radius:0px; margin-bottom:10px;");
}

void Message::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint xy = this->rect().bottomLeft();
    qDebug()<<this->rect().topLeft();
    qDebug()<<this->rect().bottomLeft();

    int x = xy.x();
    int y = xy.y()-10;
    QRectF mrect = QRectF(x, y, 10, 10);

    QPainterPath path;
    path.moveTo(mrect.left() + (mrect.width() / 2), mrect.bottom());
    path.lineTo(mrect.topLeft());
    path.lineTo(mrect.topRight());
    path.lineTo(mrect.left() + (mrect.width() / 2), mrect.bottom());

    painter.fillPath(path, QBrush(QColor ("white")));
    QLabel::paintEvent(pe);

}





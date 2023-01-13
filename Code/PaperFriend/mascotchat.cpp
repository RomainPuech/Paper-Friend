#include "mascotchat.h"
#include "mascot.h"
#include "qpainter.h"
#include "qradiobutton.h"
#include <string>
#include<QLabel>
#include <QVBoxLayout>
#include <QPainterPath>
#include <cstring>

void MascotChat:: set_scroll_area(QScrollArea *area){
    chat_layout = new QVBoxLayout();
    chat_layout->setSizeConstraint(QLayout::SetMinimumSize);
    scrollArea->widget()->setLayout(chat_layout);
}

MascotChat::MascotChat(QScrollArea *area):scrollArea(area)
{
    set_scroll_area(area);
}

MascotChat::MascotChat():scrollArea()
{}


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
    add_message(txt);
}
void MascotChat::operator<<(QString txt){
    add_message(txt);
}

//private methods
void MascotChat::add_mascot(int num){
    QLabel *image_label = new QLabel;
    Mascot *mascot = new Mascot();
    QString text_to_set = mascot -> get_emotion(num);
    image_label->setTextFormat(Qt::RichText);
    //image_label->setText("<img src=:/pictures/rsc/excited-resized.png align=middle height=\"85\">");
    image_label->setText(text_to_set);
    image_label->setFixedWidth(85);
    // setting a background color helps for debugging by showing the actual size of the label
    /*
    QPalette pali = QPalette();
    pali.setColor(QPalette::Window, Qt::green);
    image_label->setAutoFillBackground(true);
    image_label->setPalette(pali);
    */
    scrollArea->widget()->layout()->addWidget(image_label);

}
void MascotChat::add_message(QString txt){
    Message *text_label = new Message();
    text_label->setTextFormat(Qt::RichText);
    text_label->setWordWrap(true);
    text_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    //text_label ->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    text_label->setText(txt);

    scrollArea->widget()->layout()->addWidget(text_label);
}

void MascotChat::add_message(std::string txt){
    add_message(QString::fromStdString(txt));
}
void MascotChat::display(std::vector<QString> Qstr_vect, int num){
    if(Qstr_vect.size() == 0){return;}
    else if(Qstr_vect.size() == 1){
        add_message(Qstr_vect[0]);
        add_mascot(num);}
    else{for(int i=0; i < int(Qstr_vect.size()); i++){
               add_message(Qstr_vect[i]);
            }
            add_mascot(num);
        }
}
void MascotChat::prompt_msg(std::string question, int answer, int num){
    QHBoxLayout* btn_layout = new QHBoxLayout();
    QRadioButton* yes = new QRadioButton("YES");//i have to make them into mypushbutton to override the clicked event
    yes -> setCheckable(0);
    QRadioButton* no = new QRadioButton("NO");
    no -> setCheckable(0);
    btn_layout->addWidget(yes);
    btn_layout->addWidget(no);
    add_message(question);
    add_mascot(num);
    chat_layout -> addLayout(btn_layout);
    if (yes -> isChecked()){
        answer = 1;
    }
    else if (no -> isChecked()){
        answer = 0;
    }
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





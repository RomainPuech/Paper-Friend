#include "mascotchat.h"
#include "mascot.h"
#include "qpainter.h"
#include "qradiobutton.h"
#include <QLabel>
#include <QPainterPath>
#include <QVBoxLayout>
#include <cstring>
#include <string>

void MascotChat::set_scroll_area(QScrollArea *area) {
  QVBoxLayout* chat_layout = new QVBoxLayout();
  chat_layout->setSizeConstraint(QLayout::SetMinimumSize);
  scrollArea->widget()->setLayout(chat_layout);
}

MascotChat::MascotChat(QScrollArea *area) : scrollArea(area) {
  set_scroll_area(area);
}

MascotChat::MascotChat() : scrollArea() {}

// getters
QString MascotChat::get_last_message() const {
  return QString();
  // to implement. Get last message from the scrollArea. Be careful if it is
  // empty!
}
QScrollArea *MascotChat::get_scrollArea() { return scrollArea; }
// public methods
void MascotChat::operator<<(std::string txt) { add_message(txt); }

void MascotChat::operator<<(QString txt) { add_message(txt); }

void MascotChat::add_achievement(std::vector<QStringList> vect){
    if (vect.size() == 0) {
      return;
    }
    else {
      for (int i = 0; i < int(vect.size()); i++) {
          QString days_qstr = vect[i].at(2);
          QString habit_name = vect[i].at(0);
          if (days_qstr.toInt() == 5){
              QString msg1 = "You've been practicing ";
              QString msg2 = " for 5 days now.";
              QString full_msg = msg1+habit_name+msg2;
              add_message(full_msg);
              add_mascot(60);
          }
          else if (days_qstr.toInt() == 66){
              QString msg1 = "You've been practicing ";
              QString msg2 = " for 66 days now and according to research 66 days is enough for the habit to become automatic";
              QString full_msg = msg1+habit_name+msg2;
              add_message(full_msg);
              add_mascot(60);
          }
    }
   }
}

void MascotChat::add_mascot(int num) {
    //display the mascot image in the chat box
  QLabel *image_label = new QLabel;
  Mascot *mascot = new Mascot();
  QString text_to_set = mascot->get_emotion(num);
  image_label->setTextFormat(Qt::RichText);
  image_label->setText(text_to_set);
  image_label->setFixedWidth(85);
  image_label -> setMargin(5);
  scrollArea->widget()->layout()->addWidget(image_label);
}

void MascotChat::display(std::vector<QString> Qstr_vect, int num) {
  //takes a vector and displays the messages or message with the mascot according to the mood corresponding to num
  if (Qstr_vect.size() == 0) {
    return;
  }
  else if (Qstr_vect.size() == 1) {
    add_message(Qstr_vect[0]);
    add_mascot(num);
  }
  else {
    for (int i = 0; i < int(Qstr_vect.size()); i++) {
      add_message(Qstr_vect[i]);
    }
    add_mascot(num);
  }
}
void MascotChat::prompt_msg(std::string question, int num) {
  //takes a std string and displays said string with a mascot according to the mood deduced from num
  QHBoxLayout *btn_layout = new QHBoxLayout(scrollArea->widget());
  QRadioButton *yes = new QRadioButton("YES", btn_layout->widget()); 
  yes->setCheckable(0);
  QRadioButton *no = new QRadioButton("NO", btn_layout->widget());
  no->setCheckable(0);
  add_message(question);
  add_mascot(num);
}

// private methods
void MascotChat::add_message(QString txt) {
  //takes QString and displays it in the chat box
  Message *text_label = new Message();
  text_label->setTextFormat(Qt::RichText);
  text_label->setWordWrap(true);
  //text_label->setSizePolicy(QSizePolicy::Preferred,
                            //QSizePolicy::MinimumExpanding);
  text_label ->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  text_label->setText(txt);
  text_label -> setMargin(3);
  //add_notif_sound();
  scrollArea->widget()->layout()->addWidget(text_label);
}

void MascotChat::add_message(std::string txt) {
  //takes an std string and displays this message in the chat box
  add_message(QString::fromStdString(txt));
}

Message::Message() {
  this->setStyleSheet(
      "background-color: white; border: 1px solid white; border-radius:5px; "
      "border-bottom-left-radius:0px; margin-bottom:10px;");
  // this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  // this->setWordWrap(true);
}

void Message::paintEvent(QPaintEvent *pe) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  QPoint xy = this->rect().bottomLeft();

  int x = xy.x();
  int y = xy.y() - 10;
  QRectF mrect = QRectF(x, y, 10, 10);
  QPainterPath path;
  path.moveTo(mrect.left() + (mrect.width() / 2), mrect.bottom());
  path.lineTo(mrect.topLeft());
  path.lineTo(mrect.topRight());
  path.lineTo(mrect.left() + (mrect.width() / 2), mrect.bottom());

  painter.fillPath(path, QBrush(QColor("white")));
  QLabel::paintEvent(pe);
  QLabel::adjustSize();
}

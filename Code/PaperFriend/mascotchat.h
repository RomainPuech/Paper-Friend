#ifndef MASCOTCHAT_H
#define MASCOTCHAT_H
#include "qboxlayout.h"
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <mascot.h>
#include <string>
#include <vector>

class MascotChat {
public:
  MascotChat();
  MascotChat(QScrollArea *area);
  void operator<<(std::string txt);
  void operator<<(QString txt);
  void add_mascot(int num);
  void display(std::vector<QString> Qstr_vect, int num);
  void prompt_msg(std::string question, int num);
  // getters
  QString get_last_message() const;
  QScrollArea *get_scrollArea();

private:
  void set_scroll_area(QScrollArea *area);
  void add_invisible_message();
  void add_message(QString txt);
  void add_message(std::string txt);
  QScrollArea *scrollArea;
  QVBoxLayout *chat_layout;
  Mascot *mascot;
};

class Message : public QLabel {
public:
  Message();
  virtual void paintEvent(QPaintEvent *aEvent) override;
};

#endif // MASCOTCHAT_H

#ifndef MASCOTCHAT_H
#define MASCOTCHAT_H
#pragma once

#include "qboxlayout.h"
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <Frontend/mascot.h>
#include <string>
#include <vector>

class MascotChat {
public:
  MascotChat();
  MascotChat(QScrollArea *area);
  void operator<<(std::string txt);
  void operator<<(QString txt);
  void add_mascot(int num); //display the mascot image in the chat box
  void display(std::vector<QString> Qstr_vect, int num);//takes a vector and displays the messages or message with the mascot according to the mood corresponding to num
  void prompt_msg(std::string question, int num);//takes a std string and displays said string with a mascot according to the mood deduced from num
  void add_achievement(std::vector<QStringList> vect);
  // getters
  QString get_last_message() const;//returns last message
  QScrollArea *get_scrollArea();

private:
  void set_scroll_area(QScrollArea *area);
  void add_message(QString txt);//takes QString and displays it in the chat box
  void add_message(std::string txt);//takes an std string and displays this message in the chat box
  QScrollArea *scrollArea;
};

class Message : public QLabel {
public:
  Message();
  virtual void paintEvent(QPaintEvent *aEvent) override;
};

#endif // MASCOTCHAT_H

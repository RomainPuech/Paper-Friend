#ifndef DISPLAY_DAILY_HABIT_H
#define DISPLAY_DAILY_HABIT_H
#pragma once

#include "ui_display_daily_habit.h"
#include <QDialog>

namespace Ui {
class Display_Daily_Habit;
}

class Display_Daily_Habit : public QDialog {
  Q_OBJECT

public:
  explicit Display_Daily_Habit(QString habit_name, QString streak, QWidget *parent = nullptr);
  ~Display_Daily_Habit();

private slots:
  void on_yes_button_clicked();
  void on_no_button_clicked();
  void on_delete_button_clicked();

private:
  Ui::Display_Daily_Habit *ui;
};

#endif // DISPLAY_DAILY_HABIT_H

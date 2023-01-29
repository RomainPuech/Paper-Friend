#ifndef ALL_HABITS_H
#define ALL_HABITS_H
#pragma once

#include "ui_mainwindow.h"
#include <ui_mainwindow.h>
#include <QDialog>
#include <QObject>

namespace Ui {
class All_Habits;
}

class All_Habits : public QDialog {
  Q_OBJECT

public:
  explicit All_Habits(Ui::MainWindow *ui_mainwindow, QWidget *parent = nullptr);
  ~All_Habits();
  bool savedStatus = true;
  void closeEvent(QCloseEvent *event);
  bool duplicates_between_entered_saved_habits();
  bool duplicates_between_entered_habits();
  bool more_than_50_char_entered_habits();
  bool unnamed_habits();
  std::vector<QStringList> get_habits_to_be_displayed();

private slots:
  void on_add_habit_button_clicked();
  void on_save_habit_button_clicked();

private:
  Ui::MainWindow *ui_mainwindow;
  Ui::All_Habits *ui;
};

namespace Ui {
class add_habit_cell;
}

class Add_Habit_Cell : public QWidget {
  Q_OBJECT

public:
  explicit Add_Habit_Cell(QWidget *parent = nullptr);
  ~Add_Habit_Cell();

private:
  //Ui::MainWindow *ui_mainwindow;
  Ui::add_habit_cell *ui;

private slots:
  void on_delete_habit_button_clicked();
};

#endif // ALL_HABITS_H

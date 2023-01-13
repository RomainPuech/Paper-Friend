#ifndef ALL_HABITS_H
#define ALL_HABITS_H

#include <QDialog>
//#include "add_habit_cell.h"

namespace Ui {
class All_Habits;
}

class All_Habits : public QDialog
{
    Q_OBJECT

public:
    explicit All_Habits(QWidget *parent = nullptr);
    ~All_Habits();
    bool savedStatus = true;
    void closeEvent(QCloseEvent *event);

private slots:
  void on_add_habit_button_clicked();
  void on_save_habit_button_clicked();

private:
    Ui::All_Habits *ui;
};

namespace Ui {
class add_habit_cell;
}

class Add_Habit_Cell : public QWidget
{
    Q_OBJECT

public:
    explicit Add_Habit_Cell(QWidget *parent = nullptr);
    ~Add_Habit_Cell();

private:
    Ui::add_habit_cell *ui;

private slots:
    void on_delete_habit_button_clicked();
};

#endif // ALL_HABITS_H

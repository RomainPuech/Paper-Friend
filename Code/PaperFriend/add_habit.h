#ifndef ADD_HABIT_H
#define ADD_HABIT_H

#include <QDialog>

namespace Ui {
class add_habit;
}

class Add_Habit : public QDialog
{

    Q_OBJECT

public:
    explicit Add_Habit(QWidget *parent = nullptr);
    ~Add_Habit();

private:
    Ui::add_habit *ui;
};

#endif // ADD_HABIT_H

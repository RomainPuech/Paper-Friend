#ifndef ADD_HABIT_H
#define ADD_HABIT_H

#include <QDialog>

namespace Ui {
class add_habit;
}

class add_habit : public QDialog {

  Q_OBJECT

public:
  explicit add_habit(QWidget *parent = nullptr);
  ~add_habit();

private:
  Ui::add_habit *ui;
};

#endif // ADD_HABIT_H

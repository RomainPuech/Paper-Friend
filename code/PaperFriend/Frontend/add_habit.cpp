#include "add_habit.h"
#include "ui_add_habit.h"

add_habit::add_habit(QWidget *parent) : QDialog(parent), ui(new Ui::add_habit) {
  ui->setupUi(this);
}

add_habit::~add_habit() { delete ui; }

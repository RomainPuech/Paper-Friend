#include "add_habit.h"
#include "ui_add_habit.h"

Add_Habit::Add_Habit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_habit)
{
    ui->setupUi(this);
}

Add_Habit::~Add_Habit()
{
    delete ui;
}

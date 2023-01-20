#include "display_daily_habit.h"
#include "ui_display_daily_habit.h"
#include "file_processing/file_processing/file_save_and_load.h"

Display_Daily_Habit::Display_Daily_Habit(QString habit_name, QString streak, QWidget *parent)
    : QDialog(parent), ui(new Ui::Display_Daily_Habit) {
  ui->setupUi(this);
  ui->habit_label->setText(habit_name + ".\nYou did it " + streak + " time! Did you do it today?");
}

Display_Daily_Habit::~Display_Daily_Habit() {
    delete ui;
}

void Display_Daily_Habit::on_yes_button_clicked(){
    QAbstractButton *yes_button = qobject_cast<QAbstractButton *>(sender());
    QWidget *parent = qobject_cast<QWidget *>(yes_button->parent());
    QPushButton *no_button = parent->findChild<QPushButton *>("no_button");
    QPushButton *delete_button = parent->findChild<QPushButton *>("delete_button");
    yes_button->setDisabled(true);
    no_button->setDisabled(true);
    delete_button->setDisabled(true);
    QLabel *habit_label = parent->findChild<QLabel *>("habit_label");
    QStringList tmp = habit_label->text().split(".");
    int i = save_incrementation_of_habits(tmp[0]);
    habit_label->setText(tmp[0] + ".\nYou just did it " + QString::number(i) + " time!");
}

void Display_Daily_Habit::on_no_button_clicked() {
    QAbstractButton *no_button = qobject_cast<QAbstractButton *>(sender());
    QWidget *parent = qobject_cast<QWidget *>(no_button->parent());
    QPushButton *yes_button = parent->findChild<QPushButton *>("yes_button");
    QPushButton *delete_button =
        parent->findChild<QPushButton *>("delete_button");
    yes_button->setDisabled(true);
    no_button->setDisabled(true);
    delete_button->setDisabled(true);
    QLabel *habit_label = parent->findChild<QLabel *>("habit_label");
    QStringList tmp = habit_label->text().split(".");
    save_reset_of_habits(tmp[0]);
    habit_label->setText(tmp[0] + ".\nIt got reset to 0.");
}

void Display_Daily_Habit::on_delete_button_clicked() {
    QAbstractButton *delete_button = qobject_cast<QAbstractButton *>(sender());
    QWidget *parent = qobject_cast<QWidget *>(delete_button->parent());
    QPushButton *no_button = parent->findChild<QPushButton *>("no_button");
    QPushButton *yes_button = parent->findChild<QPushButton *>("yes_button");
    yes_button->setDisabled(true);
    no_button->setDisabled(true);
    delete_button->setDisabled(true);
    QLabel *habit_label = parent->findChild<QLabel *>("habit_label");
    QStringList tmp = habit_label->text().split(".");
    save_delete_of_habits(tmp[0]);
    habit_label->setTextFormat(Qt::RichText);
    habit_label->setText("<s>" + tmp[0] + "</s>");
}

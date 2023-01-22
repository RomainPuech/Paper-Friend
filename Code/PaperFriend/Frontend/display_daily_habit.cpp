#include "display_daily_habit.h"
#include "ui_display_daily_habit.h"
#include "file_processing/file_processing/file_save_and_load.h"

Display_Daily_Habit::Display_Daily_Habit(QString habit_name, QString streak, QWidget *parent)
    : QDialog(parent), ui(new Ui::Display_Daily_Habit) {
  ui->setupUi(this); //sets up the ui
  ui->habit_label->setText(habit_name + ".\nYou did it " + streak + " time! Did you do it today?"); //Adds the ui to the mainwindow
}

Display_Daily_Habit::~Display_Daily_Habit() {
    delete ui;
}

void Display_Daily_Habit::on_yes_button_clicked(){
    QAbstractButton *yes_button = qobject_cast<QAbstractButton *>(sender()); //gets the object which sent the signal
    QWidget *parent = qobject_cast<QWidget *>(yes_button->parent()); //gets the parent widget which contains label and buttons
    QPushButton *no_button = parent->findChild<QPushButton *>("no_button");
    QPushButton *delete_button = parent->findChild<QPushButton *>("delete_button"); //finds the other two button
    yes_button->setDisabled(true);
    no_button->setDisabled(true);
    delete_button->setDisabled(true); //sets the three button disabled so the user can't answer the questions again
    QLabel *habit_label = parent->findChild<QLabel *>("habit_label"); //finds the label
    QStringList tmp = habit_label->text().split("."); //get the habit from the label
    int i = save_incrementation_of_habits(tmp[0]); //saves the incrementation
    habit_label->setText(tmp[0] + ".\nYou just did it " + QString::number(i) + " time!"); //update the text of the label
}

void Display_Daily_Habit::on_no_button_clicked() {
    QAbstractButton *no_button = qobject_cast<QAbstractButton *>(sender()); //gets the object which sent the signal
    QWidget *parent = qobject_cast<QWidget *>(no_button->parent()); //gets the parent widget which contains label and buttons
    QPushButton *yes_button = parent->findChild<QPushButton *>("yes_button");
    QPushButton *delete_button = parent->findChild<QPushButton *>("delete_button"); //finds the other two button
    yes_button->setDisabled(true);
    no_button->setDisabled(true);
    delete_button->setDisabled(true); //sets the three button disabled so the user can't answer the questions again
    QLabel *habit_label = parent->findChild<QLabel *>("habit_label");//finds the label
    QStringList tmp = habit_label->text().split(".");//get the habit from the label
    save_reset_of_habits(tmp[0]);//saves the rest
    habit_label->setText(tmp[0] + ".\nIt got reset to 0.");//update the text of the label
}

void Display_Daily_Habit::on_delete_button_clicked() {
    QAbstractButton *delete_button = qobject_cast<QAbstractButton *>(sender());//gets the object which sent the signal
    QWidget *parent = qobject_cast<QWidget *>(delete_button->parent()); //gets the parent widget which contains label and buttons
    QPushButton *no_button = parent->findChild<QPushButton *>("no_button");
    QPushButton *yes_button = parent->findChild<QPushButton *>("yes_button");//finds the other two button
    yes_button->setDisabled(true);
    no_button->setDisabled(true);
    delete_button->setDisabled(true);//sets the three button disabled so the user can't answer the questions again
    QLabel *habit_label = parent->findChild<QLabel *>("habit_label"); //finds the label
    QStringList tmp = habit_label->text().split(".");//get the habit from the label
    save_delete_of_habits(tmp[0]);//saves the delete
    habit_label->setTextFormat(Qt::RichText);
    habit_label->setText("<s>" + tmp[0] + "</s>");//update the text of the label
}

#include "all_habits.h"
#include "qevent.h"
#include "ui_add_habit_cell.h"
#include "ui_all_habits.h"
#include <QString>
#include "file_processing/file_processing/file_save_and_load.h"
#include <QMessageBox>
#include <QWidget>
#include <iostream>
#include <fstream>
#include <QFileInfo>


All_Habits::All_Habits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::All_Habits)
{
    ui->setupUi(this);
    std::vector<QStringList> current_habits = load_habits();
    QString text_to_insert;
    if (current_habits.size()>0){
        for (int i = 0; i < current_habits.size()-1; i++) {
            text_to_insert += current_habits[i][0] + ", " + current_habits[i][1] + '\n';
        }
        ui->all_habits_label->setText(text_to_insert);
    }
}

All_Habits::~All_Habits() {
    delete ui;
}


void All_Habits::on_add_habit_button_clicked()
{
    Add_Habit_Cell *new_habit_cell = new Add_Habit_Cell(this);
    ui->habits_cell_layout->addWidget(new_habit_cell);
    savedStatus = false;
}

void All_Habits::on_save_habit_button_clicked() {
    savedStatus = true;
    QFile file("habits.txt");
    if(file.exists()) {
        std::ofstream myfile;
        myfile.open("habits.txt",std::ios::app);
        for (int i = 1; i < ui->habits_cell_layout->count(); i++) {
            QWidget *widget = ui->habits_cell_layout->itemAt(i)->widget();
              if (widget != NULL)
              {
                  if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()){
                      myfile<<ui->habits_cell_layout->itemAt(i)->widget()->findChild<QLineEdit*>("habit_name")->text().toStdString() +
                                  " |" +ui->habits_cell_layout->itemAt(i)->widget()->findChild<QComboBox*>("habit_frequency")->currentText().toStdString()<<std::endl;
                  }
              }
        }
        myfile.close();
    }
    else {
        std::cout<<"Creating new habits file"<<std::endl;
        std::ofstream myfile;
        myfile.open("habits.txt");
        for (int i = 1; i < ui->habits_cell_layout->count(); i++) {
            QWidget *widget = ui->habits_cell_layout->itemAt(i)->widget();
              if (widget != NULL)
              {
                  if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()){

                      myfile<<ui->habits_cell_layout->itemAt(i)->widget()->findChild<QLineEdit*>("habit_name")->text().toStdString() +
                                  " |" +ui->habits_cell_layout->itemAt(i)->widget()->findChild<QComboBox*>("habit_frequency")->currentText().toStdString()<<std::endl;
                  }
              }
        }
        myfile.close();
    }
    file.close();
}

void All_Habits::closeEvent (QCloseEvent *event){
    int c = 0;
    for (int i = 1; i < ui->habits_cell_layout->count(); i++) {
        QWidget *widget = ui->habits_cell_layout->itemAt(i)->widget();
          if (widget != NULL)
          {
              if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()){
                  c += 1;
              }
          }
    }
    if (savedStatus == false && c >0){
        QMessageBox::StandardButton answr_btn = QMessageBox::warning( this, "", "Are you sure you would like to proceed without saving your habit(s)",
                                                                      QMessageBox::Yes | QMessageBox::No);

        if (answr_btn != QMessageBox::Yes) {
            event->ignore();
        }
        else {
            this->close();
        }
    }
}


Add_Habit_Cell::Add_Habit_Cell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_habit_cell)
{
    ui->setupUi(this);
    ui->habit_frequency->addItem("Every Monday");
    ui->habit_frequency->addItem("Every Tuesday");
    ui->habit_frequency->addItem("Every Wednesday");
    ui->habit_frequency->addItem("Every Thursday");
    ui->habit_frequency->addItem("Every Friday");
    ui->habit_frequency->addItem("Every Saturday");
    ui->habit_frequency->addItem("Every Sunday");
    ui->habit_frequency->addItem("Every Weekday");
    ui->habit_frequency->addItem("Every Weekend");
    ui->habit_frequency->addItem("Every Day");
}

Add_Habit_Cell::~Add_Habit_Cell()
{
    delete ui;
}

/*void Add_Habit_Cell::set_habit_cell_name(QString cellName){
    ui->habit_name->setText(cellName);
    ui->habit_name->setMaxLength(30);
}

void Add_Habit_Cell::set_habit_frequency(int type){
    ui->habit_frequency->setCurrentIndex(type);
}*/

void Add_Habit_Cell::on_delete_habit_button_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "", "Are you sure you want to delete the habit?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
        this->setVisible(false);
        this->close();;
    }
}

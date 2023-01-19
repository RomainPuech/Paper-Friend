#include "all_habits.h"
#include "file_processing/file_processing/file_save_and_load.h"
#include "qevent.h"
#include "ui_add_habit_cell.h"
#include "ui_all_habits.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <fstream>
#include <iostream>

All_Habits::All_Habits(QWidget *parent)
    : QDialog(parent), ui(new Ui::All_Habits) {
  ui->setupUi(this);
  std::vector<QStringList> current_habits = load_habits();
  QString text_to_insert;
  if (current_habits.size() > 0) {
    for (unsigned long i = 0; i < current_habits.size(); i++) {
      text_to_insert += current_habits[i][0] + ", " + current_habits[i][1] +
                        ", done " + current_habits[i][2] +
                        " time(s) in a row.\n";
    }
    ui->all_habits_label->setText(text_to_insert);
  }
}

All_Habits::~All_Habits() { delete ui; }

void All_Habits::on_add_habit_button_clicked() {
  Add_Habit_Cell *new_habit_cell = new Add_Habit_Cell(this);
  ui->habits_cell_layout->addWidget(new_habit_cell);
  savedStatus = false;
}

void All_Habits::on_save_habit_button_clicked() {
  bool duplicates = false;
  std::vector<QStringList> current_habits = load_habits();
  for (int i = 0; i < ui->habits_cell_layout->count(); i++) {
    QWidget *widget = ui->habits_cell_layout->itemAt(i)->widget();
    if (widget != nullptr) {
      if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
        for (int j = 0; j < current_habits.size(); j++) {
          if (ui->habits_cell_layout->itemAt(i)
                  ->widget()
                  ->findChild<QLineEdit *>("habit_name")
                  ->text() == current_habits[j][0]) {
            duplicates = true;
          }
        }
      }
    }
  }
  bool duplicates_amoung_entered_habits = false;
  for (int i = 0; i < ui->habits_cell_layout->count() - 1; i++) {
    QWidget *widget1 = ui->habits_cell_layout->itemAt(i)->widget();
    if (widget1 != nullptr) {
      if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
        for (int j = i; j < ui->habits_cell_layout->count(); j++) {
          QWidget *widget2 = ui->habits_cell_layout->itemAt(i)->widget();
          if (widget2 != nullptr) {
            if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
              if (ui->habits_cell_layout->itemAt(i)
                      ->widget()
                      ->findChild<QLineEdit *>("habit_name")
                      ->text() == ui->habits_cell_layout->itemAt(j)
                                      ->widget()
                                      ->findChild<QLineEdit *>("habit_name")
                                      ->text()) {
                duplicates_amoung_entered_habits = true;
              }
            }
          }
        }
      }
    }
  }
  if (duplicates) {
    QMessageBox::warning(this, "", "One or more habits entered already exist.",
                         QMessageBox::Close);
  } else if (duplicates_amoung_entered_habits) {
    QMessageBox::warning(this, "", "One or more habits entered are the same.",
                         QMessageBox::Close);
  } else {
    QDate today = QDate::currentDate();
    QDate yesterday = today.addDays(-1);
    savedStatus = true;
    std::vector<QStringList> new_habits;
    for (int i = 0; i < ui->habits_cell_layout->count(); i++) {
      QStringList tmp;
      QWidget *widget = ui->habits_cell_layout->itemAt(i)->widget();
      if (widget != nullptr) {
        if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
          tmp.push_back(ui->habits_cell_layout->itemAt(i)
                            ->widget()
                            ->findChild<QLineEdit *>("habit_name")
                            ->text());
          tmp.push_back(ui->habits_cell_layout->itemAt(i)
                            ->widget()
                            ->findChild<QComboBox *>("habit_frequency")
                            ->currentText());
          tmp.push_back("0");
          tmp.push_back(yesterday.toString());
        }
      }
      if (tmp.size() > 0) {
        new_habits.push_back(tmp);
      }
    }
    if (new_habits.size() > 0) {
      save_habits_to_file(new_habits);
      QMessageBox::about(this, "", "All entered habits have been saved.");
      this->close();
    } else {
      QMessageBox::about(this, "", "You haven't entered any habits.");
    }
  }
}

void All_Habits::closeEvent(QCloseEvent *event) {
  int c = 0;
  for (int i = 0; i < ui->habits_cell_layout->count(); i++) {
    QWidget *widget = ui->habits_cell_layout->itemAt(i)->widget();
    if (widget != nullptr) {
      if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
        c += 1;
      }
    }
  }
  if (savedStatus == false && c > 0) {
    QMessageBox::StandardButton answr_btn = QMessageBox::warning(
        this, "",
        "Are you sure you would like to proceed without saving your habit(s)",
        QMessageBox::Yes | QMessageBox::No);

    if (answr_btn != QMessageBox::Yes) {
      event->ignore();
    } else {
      this->close();
    }
  }
}

Add_Habit_Cell::Add_Habit_Cell(QWidget *parent)
    : QWidget(parent), ui(new Ui::add_habit_cell) {
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

Add_Habit_Cell::~Add_Habit_Cell() { delete ui; }

void Add_Habit_Cell::on_delete_habit_button_clicked() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::warning(this, "",
                               "Are you sure you want to delete the habit?",
                               QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    this->setVisible(false);
    this->close();
    ;
  }
}

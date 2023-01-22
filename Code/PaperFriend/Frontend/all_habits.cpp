#include "all_habits.h"
#include "display_daily_habit.h"
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


All_Habits::All_Habits(Ui::MainWindow *ui_mainwindow, QWidget *parent)
    : QDialog(parent), ui(new Ui::All_Habits) {
  this->ui_mainwindow = ui_mainwindow;
  ui->setupUi(this); //Creates new ui defined in all_habits.ui.
  std::vector<QStringList> current_habits = load_habits(); //Gets a vector of all habits loaded from habits.txt.
  QString text_to_insert;
  if (current_habits.size() > 0) {
    for (unsigned long i = 0; i < current_habits.size(); i++) {
      text_to_insert += current_habits[i][0] + ", " + current_habits[i][1] +
                        ", done " + current_habits[i][2] +
                        " time(s) in a row.\n";
    }
    ui->all_habits_label->setText(text_to_insert); //Adds the custom text defined in the loop above to the plain
                                                   //text edit. Disabled the possibility to edit the text inserted,
                                                   //which turnd into a big scrollable label.
  }
}

All_Habits::~All_Habits() { delete ui; }

void All_Habits::on_add_habit_button_clicked() {
  Add_Habit_Cell *new_habit_cell = new Add_Habit_Cell(this);
  ui->habits_cell_layout->addWidget(new_habit_cell);//Adds the ui defined in add_habit_cell.ui into the a scrollable
                                                    //area of our current ui (which is the pop up of all habits).

  savedStatus = false; //Variable to keep track of the saved status of the habits. Initially false since no habits
                       //have been added, so no habits to save. Explanation coming soon on why we keep track of this state.
}

bool All_Habits::duplicates_between_entered_saved_habits() {
    bool duplicates = false; //Variable to keep track of the existance of duplicates between entered habits and previously.
                             //saved habits.
    std::vector<QStringList> current_habits = load_habits();
    for (int i = 0; i < ui->habits_cell_layout->count(); i++) { //Iterate over each element of habits_cell_layout, which are
                                                                //going to be the added add_habit_cell.ui.
        if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) { //Method to check if we still want to consider the ui
                                                                        //add_habit_cell.ui added, since when removing by
                                                                        //pressing on delete, it remains in the children of
                                                                        //habits_cell_layout (I don't know why it does this).
                                                                        //Fixed it by setting the widget add_hbait_cell of
                                                                        //add_habit_cell.ui by setting the unwanted ones not visible.
          for (unsigned long j = 0; j < current_habits.size(); j++) {
            if (ui->habits_cell_layout->itemAt(i)
                    ->widget()
                    ->findChild<QLineEdit *>("habit_name")
                    ->text() == current_habits[j][0]) { //Check if we have same habits entered and previously saved.
              duplicates = true; //Update of our varibale.
            }
          }
        }
    }
    return duplicates;
}

bool All_Habits::duplicates_between_entered_habits() { //This function is quite similar to the one above, the only difference is we check for duplicates amoung entered habits.
    bool duplicates_amoung_entered_habits = false;
    for (int i = 0; i < ui->habits_cell_layout->count() - 1; i++) {
        if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
          for (int j = i+1; j < ui->habits_cell_layout->count(); j++) {
              if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
                if (ui->habits_cell_layout->itemAt(i)->widget()->findChild<QLineEdit *>("habit_name")->text() ==
                        ui->habits_cell_layout->itemAt(j)->widget()->findChild<QLineEdit *>("habit_name")->text()) {
                  duplicates_amoung_entered_habits = true;
                }
              }
          }
        }
    }
    return duplicates_amoung_entered_habits;
}

bool All_Habits::unnamed_habits() { //This function checks if the entered habits have no entered text
  bool unnamed = false;
  std::vector<QStringList> current_habits = load_habits();
  for (int i = 0; i < ui->habits_cell_layout->count(); i++) {
    if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) {
      for (unsigned long j = 0; j < current_habits.size(); j++) {
        if (ui->habits_cell_layout->itemAt(i)->widget()->findChild<QLineEdit *>("habit_name")->text() == "") {
          unnamed = true;
        }
      }
    }
  }
  return unnamed;
}

bool All_Habits::more_than_50_char_entered_habits() { //This function checks if the habits entered have more than 50 characters
    bool excess = false;
    for (int i = 0; i < ui->habits_cell_layout->count(); i++) {
        if (ui->habits_cell_layout->itemAt(i)->widget()->findChild<QLineEdit *>("habit_name")->text().size() > 50) {
            excess = true;
        }
    }
    return excess;
}

std::vector<QStringList> All_Habits::get_habits_to_be_displayed(){ //This function gets the habits that are going to be displayed on the mainwindow with the questions and buttons
    std::vector<QString> displayed_habits;
    for (int i = 0; i < ui_mainwindow->verticalLayout_daily_habits->count(); i++) {
        displayed_habits.push_back(ui_mainwindow->verticalLayout_daily_habits->itemAt(i)->widget()->findChild<QLabel *>("habit_label")->text().split(".")[0]);
    }
    //The lines above get the habits already displayed in order not to display them twice
    std::vector<QStringList> to_return;
    std::vector<QStringList> daily_habits = get_daily_habits();
    for (unsigned long i = 0; i < daily_habits.size(); i++) {
        bool different = true;
        for (unsigned long j = 0; j < displayed_habits.size(); j++) {
            if (daily_habits[i][0] == displayed_habits[j]) {
                different = false; //Checks if habits from .txt file are already displayed in the mainwindow
            }
        }
        if (different) { //If they are not, then we add them to our vector
            to_return.push_back(daily_habits[i]);
        }
    }
    return to_return; //return the vector of habits which ahve to be displayed
}

void All_Habits::on_save_habit_button_clicked() {
  bool duplicates = duplicates_between_entered_saved_habits();
  bool duplicates_amoung_entered_habits = duplicates_between_entered_habits();
  bool excess = more_than_50_char_entered_habits();
  bool unnamed = unnamed_habits();
  if (duplicates) {
    QMessageBox::warning(this, "", "One or more habits entered already exist.",
                         QMessageBox::Close); //Pop up message in case of duplicates between entered habits and previously saved habits.
  } else if (duplicates_amoung_entered_habits) {
    QMessageBox::warning(this, "", "One or more habits entered are the same.",
                         QMessageBox::Close); //Pop up message in case of duplicates amoung entered habits.
  }  else if (excess) {
      QMessageBox::warning(this, "", "One or more habits entered have more than 50 characters. Please decrease the character count.",
                           QMessageBox::Close); //Pop up message in case there is more than 50 characters in one of the entered habits.
  } else if (unnamed) {
    QMessageBox::warning(this, "", "No habit name entered.",
                         QMessageBox::Close); //Pop up message in case one of the habits is without a name.
    } else { //If no duplicates found, we proceed with saving our entered habits.
    QDate today = QDate::currentDate();
    QDate yesterday = today.addDays(-1); //We save yesterday's date to be able to ask the question on the mainwindow whether the user
                                         //did his habit or no, or delete it, on the same day specified.
    /*Example if I decide to enter a habit h1 today (which is a monday) and I do it every monday, then we want to be able to ask today to the user
      if he has done his habit or no, or if he would like to delete it. This way, once the question answered, the last date where the user answered will
      be saved along it's corresponding habit and the question won't be asked several times on the same day.
     */
    savedStatus = true; //Update our saved status to true, explanation coming soon on why we keep track of this state.
    std::vector<QStringList> new_habits;
    for (int i = 0; i < ui->habits_cell_layout->count(); i++) {
      QStringList tmp; //Initialisaton of a temprory vector of QString.
        if (ui->habits_cell_layout->itemAt(i)->widget()->isVisible()) { //Same explanation as above.
          tmp.push_back(ui->habits_cell_layout->itemAt(i)
                            ->widget()
                            ->findChild<QLineEdit *>("habit_name")
                            ->text()); //Add to the vector the habit entered.
          tmp.push_back(ui->habits_cell_layout->itemAt(i)
                            ->widget()
                            ->findChild<QComboBox *>("habit_frequency")
                            ->currentText()); //Add to the vector the day we repeat the habit.
          tmp.push_back("0"); //Add value of streak of habit (keeping track the numbers of days he has done his habit without breaks). Initially 0.
          tmp.push_back(yesterday.toString()); //Add date to each habit.
        }
      if (tmp.size() > 0) { //Safety check in order to avoid empty elements and result in bugs while saving/loading habits.txt.
        new_habits.push_back(tmp);
      }
    }
    if (new_habits.size() > 0) { //Same safety check but for the whole vector of Qstring vectors
      save_habits_to_file(new_habits); //Function to save habits
      QMessageBox::about(this, "", "All entered habits have been saved."); //Pop up message to inform user that entered habits have been saved successfully.

      std::vector<QStringList> new_habits_of_the_day = get_habits_to_be_displayed();
      if (new_habits_of_the_day.size() > 0) {
          if (ui_mainwindow->generic_habit_label->isVisible()) { //If the generic label is visible it means that no habits have been displayed before, so we have to set it invisible
              ui_mainwindow->generic_habit_label->setVisible(false); //which we do here
              ui_mainwindow->habits_scrollArea->setVisible(true); //and set the scroll are for the questions visible
          }
          for (unsigned long i = 0; i < new_habits_of_the_day.size(); i++) {
            Display_Daily_Habit *new_daily_habit = new Display_Daily_Habit(new_habits_of_the_day[i][0], new_habits_of_the_day[i][2]); //creates the ui for each habit
            ui_mainwindow->verticalLayout_daily_habits->addWidget(new_daily_habit); //displays them in mainwindow
          }
      }

      this->close(); //Automatically close the ui.s
    } else {
      QMessageBox::about(this, "", "You haven't entered any habits."); //Pop up message to inform user that no habits have been entered.
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
  //The lines of code above counts the number of visible widget for add_habit_cell
  if (savedStatus == false && c > 0) { //SavedStatus used here to check if entered habits have not been previously saved, and we have some visible widgets(habits)
                                       //we would like to add.
    QMessageBox::StandardButton answr_btn = QMessageBox::warning(
        this, "",
        "Are you sure you would like to proceed without saving your habit(s)",
        QMessageBox::Yes | QMessageBox::No); //Pop up message warning the user that entered habits have not been saved.

    if (answr_btn == QMessageBox::Yes) {
      this->close(); //If answer is yes, then close ui without saving the habits.
    }
  }
}

Add_Habit_Cell::Add_Habit_Cell(QWidget *parent)
    : QWidget(parent), ui(new Ui::add_habit_cell) {
  ui->setupUi(this);
  //Setting values for QComboBox in add_habit_cell.ui
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

Add_Habit_Cell::~Add_Habit_Cell() {
    delete ui;
}

void Add_Habit_Cell::on_delete_habit_button_clicked() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::warning(this, "",
                               "Are you sure you want to delete the habit?",
                               QMessageBox::Yes | QMessageBox::No); //Pop up message warning the user about deletion of entered habits (but not saved).
  if (reply == QMessageBox::Yes) {
    this->setVisible(false); //If answer is yes, then set widget invisible (in order to track later habits we would like to consider since closing them is not enough).
    this->close(); //close ui (which is the add_habit_cell_ui.
    ;
  }
}

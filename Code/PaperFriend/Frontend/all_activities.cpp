#include "all_activities.h"
#include "activity_cell.h"
#include "activityclasses.h"
#include "mainwindow.h"
#include "ui_activity_cell.h"
#include "ui_all_activities.h"
#include <QFile>
#include <QMessageBox>

all_activities::all_activities(MainWindow *mainwindow,
                               std::vector<Activity> &vector_activity,
                               QWidget *parent)
    : mainwindowptr(mainwindow), vector_activities(vector_activity),
      QDialog(parent), ui(new Ui::all_activities) {
  ui->setupUi(this);
  ActivitiesCellNumberTotal = 0;
  this->add_previous_cells();
  disable_text_change();
}

all_activities::~all_activities() { delete ui; }

void all_activities::on_add_activity_button_clicked() { addNewCell(); }

void all_activities::addNewCell(QString cellName, int type) {
  // are_equal=false;
  activity_cell *new_activity_cell =
      new activity_cell(this); // Create a new activity_cell.
  ui->activities_cell_layout->addWidget(
      new_activity_cell); // add a widget in the activities_cell_layout.
  connect(new_activity_cell, SIGNAL(closeThisCell(int)), this,
          SLOT(closeCell(int)));
  new_activity_cell->setAttribute(
      Qt::WA_DeleteOnClose, true); // here we set an attribute so whenever we
                                   // close the cell it is indeed deleted.
  new_activity_cell->ActivitiesCellNumber =
      ActivitiesCellNumberTotal; // here in the new_activity_cell I defined the
                                 // activity cell number to be equal to the
                                 // total activities cell number.
  // new_activity_cell->setTextData(cellText); // this line set the text.
  new_activity_cell->set_activity_cell_name(cellName);
  allCellPtr.append(new_activity_cell); // here I append this new activity cell
                                        // to the data vector.

  new_activity_cell->set_activity_type(type);
  vector_activities.push_back(Activity(cellName.toStdString(), type, 0));
  ActivitiesCellNumberTotal++; // the total number of activities is incremented by 1.

}

void all_activities::add_previous_cells() {
  for (long long unsigned i = 0; i < vector_activities.size(); i++) {
    addNewCell(QString::fromStdString(vector_activities.at(i).get_name()),
               vector_activities.at(i).get_type());
    vector_activities.pop_back();
  }
}

void all_activities::closeCell(int ActivitiesCellNumber) {
  for (int i = ActivitiesCellNumber + 1; i < allCellPtr.length(); i++) {
    allCellPtr[i]->ActivitiesCellNumber--;
  }
  ActivitiesCellNumberTotal--;
  allCellPtr[ActivitiesCellNumber]->close();
  allCellPtr.remove(ActivitiesCellNumber);
}

void all_activities::on_save_activity_button_clicked() {
  if (!error_messages()) {
    QApplication::processEvents();
    QString name_activity;
    int type_activity;
    vector_activities.clear();
    for (int i = 0; i < allCellPtr.size(); ++i) {
      name_activity = allCellPtr[i]->get_activity_name();
      type_activity = allCellPtr[i]->get_activity_type();
      vector_activities.push_back(
          Activity(name_activity.toStdString(), type_activity, 0));
    }
    save_activities(vector_activities);

    bool condition = false;
    for (int i = 0; i < allCellPtr.size(); ++i) {
      name_activity = allCellPtr[i]->get_activity_name();
      type_activity = allCellPtr[i]->get_activity_type();
      if (allCellPtr.size() == vector_activities.size() &&
          name_activity != "" && type_activity != 0) {
        condition = true;
      } else {
        condition = false;
      }
    }
    if (condition == true) {
      QMessageBox::StandardButton reply;
      reply = QMessageBox::information(
          this, "Save Confirmation", "All your activities and friends are saved.",
          QMessageBox::Ok);
      if (reply == QMessageBox::Ok) {
        this->close();
      }
    } else {
      this->close();
    }
  }


  /*
  activity_cell A;
  int dlt_number;
  dlt_number = A.number_clicked();
  if (dlt_number != 0) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(
        this, "Save Confirmation", "All your activities and friends are saved.",
        QMessageBox::Ok);
    if (reply == QMessageBox::Ok) {
      this->close();
    }
  }
  */

  // we add the activity with value 0 to all existing entryPerso.
  // In terms of complexity it is not the best option but given that the number
  // of entries will reasonably be less than 1000 it is going to be immediate in
  // practice and saves us a lot of time in terms of coding

  MainWindow::remove_activities_from_old_entries();
  mainwindowptr->add_new_activities_to_old_enties();
  MainWindow::refresh_activities();
}

void all_activities::disable_text_change() {
  QString name_activity;
  int type_activity;
  for (int i = 0; i < allCellPtr.size(); ++i) {
    name_activity = allCellPtr[i]->get_activity_name();
    type_activity = allCellPtr[i]->get_activity_type();
    if (name_activity != "n") {
      // qDebug()<<QString("hey");
      allCellPtr[i]->ui->activity_name->setReadOnly(true);
    }if(type_activity != 1000) {
        allCellPtr[i]->ui->activity_type->setDisabled(true);
    }
  }
}

void all_activities::closeEvent(QCloseEvent *event) {
  bool changed_type = false;
    if (unsigned(allCellPtr.size()) != vector_activities.size()) {
      QMessageBox::warning(this, tr("Paper friend"),
                           tr("Please save your changes."),
                           QMessageBox::Ok);
      event->ignore();
    } else {
      for (int i = 0; i < allCellPtr.size(); ++i) {
          if(i< vector_activities.size()){
        QString name_activity_acp;
        name_activity_acp = allCellPtr[i]->get_activity_name();
        std::string name_activity_vec;
        name_activity_vec = vector_activities[i].get_name();
        int type_activity_acp;
        type_activity_acp = allCellPtr[i]->get_activity_type();
        int type_activity_vec;
        type_activity_vec = vector_activities[i].get_type();
        if (name_activity_acp.toStdString() != name_activity_vec ||
          type_activity_acp != type_activity_vec) {
            changed_type = true;
          }
          }
      }
      if (changed_type == true) {
        QMessageBox::warning(this, tr("Paper friend"),
                             tr("Please save your changes."),
                             QMessageBox::Ok);
        event->ignore();
      } else if (error_messages()) {
        event->ignore();
      }
    }
}

bool all_activities::error_messages() {
  bool type_error = false;
  bool name_error = false;
  for (int i = 0; i < allCellPtr.size(); ++i) {
    QString name_activity_acp;
    name_activity_acp = allCellPtr[i]->get_activity_name();
    std::string name_activity_vec;
    name_activity_vec = vector_activities[i].get_name();
    int type_activity_acp;
    type_activity_acp = allCellPtr[i]->get_activity_type();
    if (type_activity_acp == 0) {
      type_error = true;
    }
    if (name_activity_acp.toStdString() == "") {
      name_error = true;
    }
  }
  if (name_error == true) {
    QMessageBox::warning(this, tr("Paper friend"),
                         tr("Please enter an activity/friend name."),
                         QMessageBox::Ok);
    return true;
  } else if (type_error == true) {
    QMessageBox::warning(this, tr("Paper friend"),
                         tr("Please enter an activity/friend type."),
                         QMessageBox::Ok);
    return true;
  } else {
    bool same_name = false ;
    for (int i = 0; i < allCellPtr.size(); ++i) {
      for (int j = 0; j < allCellPtr.size(); ++j) {
        if (i != j && allCellPtr[j]->get_activity_name() ==
                allCellPtr[i]->get_activity_name()) {
          same_name = true;
        } else {
          same_name = false;
        }
      }
      if (same_name == true) {
        QMessageBox::warning(this, tr("Paper friend"),
                             tr("Some activities/friends have the same name. It is not allowed."),
                             QMessageBox::Ok);
        return true;
      }
    }
  }
  return false;
}

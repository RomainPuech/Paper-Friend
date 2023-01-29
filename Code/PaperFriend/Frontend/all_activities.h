#ifndef ALL_ACTIVITIES_H
#define ALL_ACTIVITIES_H
#pragma once

#include "activityclasses.h"
#include "mainwindow.h"
#include <QChartView>
#include <QDialog>
#include <QLineSeries>
#include <QVector>
#include <QtCharts>
#include <Frontend/activity_cell.h>

namespace Ui {
class all_activities;
}

class all_activities : public QDialog {
  Q_OBJECT

public:
  explicit all_activities(MainWindow *mainwindow,
                          std::vector<Activity> &vector_activities,
                          QWidget *parent = nullptr);
  ~all_activities();
  int ActivitiesCellNumberTotal; // The total number of the activities.
  QVector<activity_cell *>
      allCellPtr; // This vector saves all the data of the activity cell.
  void add_previous_cells();
  void closeEvent(QCloseEvent *event);
  void disable_text_change();

private slots:
  void on_add_activity_button_clicked();

  void addNewCell(QString cellName = "", int type = 0);

  void on_save_activity_button_clicked();

  bool error_messages();

public slots:
  void closeCell(int);

private:
  MainWindow *mainwindowptr;
  std::vector<Activity> &vector_activities;
  Ui::all_activities *ui;
};

#endif // ALL_ACTIVITIES_H

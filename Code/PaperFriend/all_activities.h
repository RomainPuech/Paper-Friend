#ifndef ALL_ACTIVITIES_H
#define ALL_ACTIVITIES_H

#include "activityclasses.h"
#include <QChartView>
#include <QDialog>
#include <QLineSeries>
#include <QVector>
#include <QtCharts>
#include <activity_cell.h>

namespace Ui {
class all_activities;
}

class all_activities : public QDialog {
  Q_OBJECT

public:
  explicit all_activities(std::vector<Activity> &vector_activities,
                          QWidget *parent = nullptr);
  ~all_activities();
  int ActivitiesCellNumberTotal; // The total number of the activities.
  QVector<activity_cell *>
      allCellPtr; // This vector saves all the data of the activity cell.
  void add_previous_cells();
  void closeEvent(QCloseEvent *event);

private slots:
  void on_add_activity_button_clicked();

  void addNewCell(QString cellText = "", QString cellName = "Activity name", int type = 0);


  void on_save_activity_button_clicked();

public slots:
  void closeCell(int);

private:
  std::vector<Activity> &vector_activities;
  Ui::all_activities *ui;
};

#endif // ALL_ACTIVITIES_H

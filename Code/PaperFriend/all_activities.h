#ifndef ALL_ACTIVITIES_H
#define ALL_ACTIVITIES_H

#include <QDialog>
#include<QVector>
#include <QtCharts>
#include <QChartView>
#include<QLineSeries>
#include<activity_cell.h>>
#include"activityclasses.h"

namespace Ui {
class all_activities;
}

class all_activities : public QDialog
{
    Q_OBJECT

public:
    explicit all_activities(std::vector<Activity> &vector_activities,QWidget *parent = nullptr);
    ~all_activities();
    static int ActivitiesCellNumberTotal; // The total number of the activities.
    static QVector<activity_cell *> allCellPtr; // This vector saves all the data of the activity cell.
    void add_previous_cells();
    void closeEvent (QCloseEvent *event);

private slots:
    void on_add_activity_button_clicked();

    void addNewCell(QString cellText="", QString cellName="Cell Name");

    void on_save_activity_button_clicked();

public slots:
    void closeCell(int);

private:
    std::vector<Activity> &vector_activities;
    Ui::all_activities *ui;
};

#endif // ALL_ACTIVITIES_H

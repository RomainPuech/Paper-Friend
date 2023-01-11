#ifndef ALL_PEOPLE_H
#define ALL_PEOPLE_H

#include "friendclasses.h"
#include <people_cell.h>
#include <QLineSeries>
#include <QChartView>
#include <QtCharts>
#include <QDialog>
#include <QVector>

namespace Ui {
class all_people;
}

class all_people : public QDialog
{
    Q_OBJECT

public:
    explicit all_people(std::vector<Friend>&vector_friends,
                        QWidget *parent = nullptr);
    ~all_people();
    int PersonCellNumberTotal; // The total number of people.
    QVector<people_cell *>PersonallCellPtr; // This vector saves all the data of the people_cell.
    void add_previous_cells();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_add_people_button_clicked();

    void addNewCell(QString cellText = "", QString cellName = "Person name", int type = 0);

    void on_save_people_button_clicked();

public slots:
  void closeCell(int);

private:
    std::vector<Friend> &vector_friends;
    Ui::all_people *ui;
};

#endif // ALL_PEOPLE_H

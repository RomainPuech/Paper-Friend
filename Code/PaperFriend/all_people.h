#ifndef ALL_PEOPLE_H
#define ALL_PEOPLE_H

#include "friendclasses.h"
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
    explicit all_people(std::vector<Friend>vector_friends,
                        QWidget *parent = nullptr);
    ~all_people();

private:
    std::vector<Friend>vector_friends;
    Ui::all_people *ui;
};

#endif // ALL_PEOPLE_H

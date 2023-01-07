#ifndef DYNAMICGRAPH_H
#define DYNAMICGRAPH_H

#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entryclasses.h"
#include <vector>

class DynamicGraph
{
public:
    DynamicGraph(std::vector<EntryPerso*> &entries, QString tracked_parameter);
    void display(QLayout *parent_frame) const;
    //getters and setters
    std::vector<EntryPerso*> get_entries() const;

private:
    std::vector<QLineSeries*> listofseries;
    std::vector<EntryPerso*> entries;
    QScatterSeries *visible_green_points;
    QScatterSeries *visible_orange_points;
    QScatterSeries *visible_red_points;
    QColor level_colors[3] = {"red","orange","green"};
    enum parameterlevel{
        bad,
        medium,
        good
    };

    //methods
    parameterlevel associated_parameter_level(double parameter) const;
    void set_color(QLineSeries* series, parameterlevel level);
    void get_dummy_point(double y1,double y2, double x1, double x2, double (&res)[2]);
    double parameter_value(EntryPerso *entry, QString tracked_parameter);

};

#endif // DYNAMICGRAPH_H

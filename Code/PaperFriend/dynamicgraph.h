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
    DynamicGraph(std::vector<EntryPerso*> entries);
    void display(QLayout *parent_frame) const;
    //getters and setters
    std::vector<EntryPerso*> get_entries() const;

private:
    std::vector<QLineSeries*> listofseries;
    std::vector<EntryPerso*> entries;
    QColor level_colors[3] = {"red","orange","green"};
    enum moodlevel{
        bad,
        medium,
        good
    };

    //methods
    moodlevel associated_mood_level(double mood) const;
    void set_color(QLineSeries* series,moodlevel level);
    void get_dummy_point(double y1,double y2, double x1, double x2, double (&res)[2]);


};

#endif // DYNAMICGRAPH_H

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
    DynamicGraph(std::vector<EntryPerso> entries);
    void display(QLayout *parent_frame) const;
    void set_entries(std::vector<EntryPerso>);
    std::vector<EntryPerso> get_entries() const;



private:
    QSplineSeries *series1;
    QSplineSeries *series2;
    std::vector<EntryPerso> entries;
};

#endif // DYNAMICGRAPH_H

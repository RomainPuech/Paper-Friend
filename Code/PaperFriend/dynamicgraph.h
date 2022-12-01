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
    DynamicGraph(QFrame *parent_frame,std::vector<EntryPerso> entries);
    void display() const;
    void set_parent(QFrame *parent_frame);
    QFrame* get_parent() const;



private:
    QFrame *parent_frame;
    QLineSeries *series;
    std::vector<EntryPerso> entries;
};

#endif // DYNAMICGRAPH_H

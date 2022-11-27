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
    DynamicGraph(QWidget *parent_frame,std::vector<EntryPerso> entries);
    void display() const;
    void set_parent(QWidget *parent_frame);
    QWidget* get_parent() const;



private:
    QWidget *parent_frame;
    QLineSeries *series;
    std::vector<EntryPerso> entries;
};

#endif // DYNAMICGRAPH_H

#ifndef DYNAMICGRAPH_H
#define DYNAMICGRAPH_H

#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class DynamicGraph
{
public:
    DynamicGraph(Ui::MainWindow *ui);
    void display() const;
private:
    Ui::MainWindow *ui;
};

#endif // DYNAMICGRAPH_H

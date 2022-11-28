#include "dynamicgraph.h"
#include <QApplication>
#include <QtCharts>
#include <QChartView>
#include<QLineSeries>
// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>
// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>
// Used to create a line chart
#include <QtCharts/QLineSeries>
// Used to change names on axis
#include <QtCharts/QCategoryAxis>
#include "mainwindow.h"
#include "entryclasses.h"
#include "ui_mainwindow.h"

DynamicGraph::DynamicGraph(QWidget *frame, std::vector<EntryPerso> entries)
    :parent_frame(frame),series(new QLineSeries()),entries(entries)
{
    int i =0;
    for(std::vector<EntryPerso>::iterator e=entries.begin();e!=entries.end();e++){
        series->append(i,e->get_mood());
        i++;
    }
    //series->append(0,6);
    //series->append(1,5);
    //*series<< QPointF(11,1)<<QPointF(13,3);
    //just dummy points
}

//setters and getters
void DynamicGraph::set_parent(QWidget *new_parent){parent_frame = new_parent;}
QWidget* DynamicGraph::get_parent() const{return parent_frame;}

//display the graph in its parent frame
void DynamicGraph::display() const
{
    QChart *mood_chart = new QChart();
    mood_chart->legend()->hide();
    mood_chart->addSeries(series);
    mood_chart->setTitle("Mood");
    QChartView *mood_view = new QChartView(mood_chart);
    //mood_view->setMaximumSize(parent_frame->width(),100);
    mood_view->setRenderHint(QPainter::Antialiasing);
    mood_view->setParent(parent_frame);//displays the graph on the screen in the parent frame
}

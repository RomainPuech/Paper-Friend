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

DynamicGraph::DynamicGraph(std::vector<EntryPerso> entries)
    :series1(new QSplineSeries()),series2(new QSplineSeries()),entries(entries)
{

    QPen pen = series1->pen();
    pen.setWidth(3);
    pen.setColor("red");
    series1->setPen(pen);
    int i =0;
    for(std::vector<EntryPerso>::iterator e=entries.begin();e!=entries.end();e++){
        *series1<<QPointF(i,e->get_mood());
        *series2<<QPointF(entries.size()+i,e->get_mood());
        i++;

    }
    //series->append(0,6);
    //series->append(1,5);
    //*series<< QPointF(11,1)<<QPointF(13,3);
    //just dummy points
}

//setters and getters


//display the graph in its parent frame
void DynamicGraph::display(QLayout *layout) const
{
    QChart *mood_chart = new QChart();
    mood_chart->legend()->hide();
    mood_chart->addSeries(series1);
    mood_chart->addSeries(series2);
    mood_chart->createDefaultAxes();
    mood_chart->axes(Qt::Vertical).first()->setRange(0, 20);
    mood_chart->setTitle("Mood");
    QChartView *mood_view = new QChartView(mood_chart);
    mood_view->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(mood_view);//displays the graph on the screen in the indicated layout
}

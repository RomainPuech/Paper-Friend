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

DynamicGraph::DynamicGraph()
{
    QLineSeries* series = new QLineSeries();
    series->append(0,6);
    series->append(1,3);

    *series<< QPointF(11,1)<<QPointF(13,3);
    QChart *mood_chart = new QChart();
    mood_chart->legend()->hide();
    mood_chart->addSeries(series);
    mood_chart->setTitle("Mood");
    QChartView *mood_view = new QChartView(mood_chart);
    mood_view->setRenderHint(QPainter::Antialiasing);
    //mood_view->setParent(ui->horizontalFrame);
}

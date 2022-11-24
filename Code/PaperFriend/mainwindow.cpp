#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //test
    DynamicGraph moodGraph = DynamicGraph(ui);
    moodGraph.display();
}

MainWindow::~MainWindow()
{
    delete ui;
}


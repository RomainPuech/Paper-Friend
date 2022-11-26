#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //test
    DynamicGraph moodGraph = DynamicGraph(ui);
    moodGraph.display();
    // test for the EntryCard class
    EntryPerso *e = new EntryPerso();
    EntryCard *c = new EntryCard(20, 300, 300, "beige", e);
    c->display(ui->frame);
}

MainWindow::~MainWindow()
{
    delete ui;
}


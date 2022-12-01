#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // display canvas created in drag-and-drop


    // test for the EntryCard class
    EntryPerso *e = new EntryPerso();
    EntryCard *c = new EntryCard(20, 300, 300, "beige", e);
    c->display(ui->main_frame); //displays the entry in the main_frame.

    //test for the DynamicGraph class
    EntryPerso *e1 = new EntryPerso(); //create an entry
    EntryPerso *e2 = new EntryPerso();
    e1->set_mood(10.); //put a dummy mood
    e2->set_mood(12.);
    std::vector<EntryPerso> entries; //put entries in a vector
    entries.push_back(*e1);
    entries.push_back(*e2);
    DynamicGraph moodGraph = DynamicGraph(ui->graph_frame,entries); // the parent frame (frame in which the graph is going to be displayed) is ui->frame
    moodGraph.display(); //displays the graph

    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide(); //hide the settings menu on launch

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
    hide();
    all_habits = new All_Habits(this);
    all_habits -> show();
}


void MainWindow::on_settingsButton_clicked() {
    auto settings = findChild<QWidget*>("settings_frame");
    settings->show();
    auto standard = findChild<QWidget*>("standard_frame");
    standard->hide();
}

void MainWindow::on_save_settings_clicked() {
    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide();
    auto standard = findChild<QWidget*>("standard_frame");
    standard->show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"

#include <iostream>
#include <fstream>

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
    std::ofstream myfile;
    myfile.open("journal_settings.txt");
    if (findChild<QCheckBox*>("mood")->isChecked()) {
        myfile << "mood:true\n";
    } else {
        myfile << "mood:false\n";
    }
    if (findChild<QCheckBox*>("sleep")->isChecked()) {
        myfile << "sleep:true\n";
    } else {
        myfile << "sleep:false\n";
    }
    if (findChild<QCheckBox*>("eating_healthy")->isChecked()) {
        myfile << "eating_healthy:true\n";
    } else {
        myfile << "eating_healthy:false\n";
    }
    if (findChild<QCheckBox*>("productivity")->isChecked()) {
        myfile << "productivity:true\n";
    } else {
        myfile << "productivity:false\n";
    }
    if (findChild<QCheckBox*>("communications")->isChecked()) {
        myfile << "communications:true\n";
    } else {
        myfile << "communications:false\n";
    }
    if (findChild<QCheckBox*>("screen_time")->isChecked()) {
        myfile << "screen_time:true\n";
    } else {
        myfile << "screen_time:false\n";
    }
    myfile.close();
    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide();
    auto standard = findChild<QWidget*>("standard_frame");
    standard->show();
}

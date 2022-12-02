#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"
#include "all_activities.h"
#include "file_processing/file_processing/file_save_and_load.h"

#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // display canvas created in drag-and-drop


    Entry en = Entry("text", "title");
    save_entry_encrypt(en, "./output", "123");
    std::cout << "saving" << std::endl;
    Entry en2 = load_entry_decrypt("./output/12.02.2022.json", "123");
    std::cout << "loading" << std::endl;
    std::cout << en2.get_text() << std::endl;
    std::cout << en2.get_title() << std::endl;

    // test for the EntryCard class
    EntryPerso *e = new EntryPerso();

    EntryCard *c = new EntryCard(20, 300, 300, "beige", e);
    c->display(ui->main_frame); //displays the entry in the main_frame.

    //test for the DynamicGraph class
    //std::vector<EntryPerso> entries = sample_entries(10);
    EntryPerso e1 =EntryPerso();
    EntryPerso e2 =EntryPerso();
    EntryPerso e3 =EntryPerso();
    e1.set_mood(10.);
    e2.set_mood(12.);
    e3.set_mood(11.);
    std::vector<EntryPerso> entries;
    entries.push_back(e1);
    entries.push_back(e2);
    entries.push_back(e3);
    DynamicGraph moodGraph = DynamicGraph(entries); // the parent frame (frame in which the graph is going to be displayed) is ui->frame
    moodGraph.display(ui->graph_frame); //displays the graph
    this -> showMaximized();

    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide(); //hide the settings menu on launch
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::closeEvent (QCloseEvent *event){
    QMessageBox::StandardButton answr_btn = QMessageBox::question( this, tr("Paper friend"), tr("Are you sure?\n"),
                                         QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if (answr_btn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}


void MainWindow::on_pushButton_clicked() {
    hide();
    all_habits = new All_Habits(this);
    all_habits -> showMaximized();
}



void MainWindow::on_activitie_button_clicked()
{
    all_activities my_activities;
    my_activities.setModal(true);
    my_activities.exec();

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

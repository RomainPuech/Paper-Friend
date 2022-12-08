#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"
#include "all_activities.h"
#include "file_processing/file_processing/file_save_and_load.h"
#include "texteditor.h"
#include "ui_texteditor.h"
#include "settings.h"

#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // display canvas created in drag-and-drop
    // We use Friend function to embed the TextEditor into the MainWindow
    textEditor = new TextEditor();
    textEditor->mainUi = this;

    Entry en = Entry("text", "title");
    save_entry_encrypt(en, "./output", "123");
    std::cout << "saving" << std::endl;
    Entry en2 = load_entry_decrypt("./output/12.02.2022.json", "123");
    std::cout << "loading" << std::endl;
    std::cout << en2.get_text() << std::endl;
    std::cout << en2.get_title() << std::endl;

    // test for the EntryCard class
    EntryPerso *e = new EntryPerso();
    std::vector<Friend*> fr;
    fr.push_back(new Friend("fr1", 1));
    std::vector<Activity*> activity;
    activity.push_back( new Activity("act1", 1));
    e->set_friends(fr);
    e->set_activities(activity);
    e->set_title("THIS IS A TITLE");
    e->set_text("some text...");
    EntryCard *c = new EntryCard(20, 300, 300, "white", e);
    //Card *c = new Card();
    c->display(ui->main_frame); //displays the entry in the main_frame.

    //test for the DynamicGraph class
    //std::vector<EntryPerso> entries = sample_entries(10);
    //double moods[10]={7,8,6,5,18,13,15,16,17,12};
    EntryPerso e1 =EntryPerso();
    EntryPerso e2 =EntryPerso();
    EntryPerso e3 =EntryPerso();
    EntryPerso e4 =EntryPerso();
    EntryPerso e5 =EntryPerso();
    EntryPerso e6 =EntryPerso();
    EntryPerso e7 =EntryPerso();
    EntryPerso e8 =EntryPerso();
    EntryPerso e9 =EntryPerso();
    EntryPerso e10 =EntryPerso();
    e1.set_mood(7);
    e2.set_mood(8);
    e3.set_mood(6);
    e4.set_mood(5);
    e5.set_mood(18);
    e6.set_mood(13);
    e7.set_mood(15);
    e8.set_mood(16.);
    e9.set_mood(17.);
    e10.set_mood(12.);
    std::vector<EntryPerso> entries;
    entries.push_back(e1);
    entries.push_back(e2);
    entries.push_back(e3);
    entries.push_back(e4);
    entries.push_back(e5);
    entries.push_back(e6);
    entries.push_back(e7);
    entries.push_back(e8);
    entries.push_back(e9);
    entries.push_back(e10);
    DynamicGraph moodGraph = DynamicGraph(entries);
    moodGraph.display(ui->graph_frame); //displays the graph
    this -> showMaximized();

    //Chatbox tests
    //overload with too much messages
    QVBoxLayout *chat_layout = new QVBoxLayout();
    //chat_layout->addWidget(btn);
    ui->scrollArea->widget()->setLayout(chat_layout);
    for(int i = 0; i<20 ; i++){
        QLabel *label = new QLabel(this);
        label->setText(QString::number(i));
         ui->scrollArea->widget()->layout()->addWidget(label);
    }



    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide(); //hide the settings menu on launch
    findChild<QCheckBox*>("mood")->setChecked(saved_mood());
    findChild<QCheckBox*>("sleep")->setChecked(saved_sleep());
    findChild<QCheckBox*>("eating_healthy")->setChecked(saved_eating_healthy());
    findChild<QCheckBox*>("productivity")->setChecked(saved_productivity());
    findChild<QCheckBox*>("communications")->setChecked(saved_communications());
    findChild<QCheckBox*>("screen_time")->setChecked(saved_screen_time());
    //setting the icon for the setting button
    QPixmap pix(":/pictures/rsc/checklist icon.png");
    int w = ui->settingsButton->width();
    int h = ui->settingsButton->height();
    ui->settingsButton->setIcon(QIcon(pix.scaled(w,h,Qt::KeepAspectRatio)));
    //
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::toggle_visibility(QWidget *component){
    if(component->isVisible()){
        component->hide();
    }
    else{
        component->show();
    }
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
    toggle_visibility(settings);
    auto chat = findChild<QWidget*>("scrollArea");
    toggle_visibility(chat);
}

void MainWindow::on_save_settings_clicked() {
    std::ofstream myfile;
    myfile.open("settings.txt");
    myfile << findChild<QCheckBox*>("mood")->isChecked() << "\n";
    myfile << findChild<QCheckBox*>("sleep")->isChecked() << "\n";
    myfile << findChild<QCheckBox*>("eating_healthy")->isChecked() << "\n";
    myfile << findChild<QCheckBox*>("productivity")->isChecked() << "\n";
    myfile << findChild<QCheckBox*>("communications")->isChecked() << "\n";
    myfile << findChild<QCheckBox*>("screen_time")->isChecked() << "\n";
    myfile.close();
    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide();
    auto chat = findChild<QWidget*>("scrollArea");
    chat->show();
}


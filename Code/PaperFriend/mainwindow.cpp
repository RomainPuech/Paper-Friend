#include "mainwindow.h"
#include "mascot.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"
#include "all_activities.h"
#include "file_processing/file_processing/file_save_and_load.h"
#include "texteditor.h"
#include "ui_texteditor.h"
#include "settings.h"
#include "mascotchat.h"


#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // display canvas created in drag-and-drop

    //create layout for central scrollable area
    QVBoxLayout *entries_layout = new QVBoxLayout();
    ui->EntriesScroll->widget()->setLayout(entries_layout);

    // We use Friend function to embed the TextEditor into the MainWindow
    textEditor = new TextEditor();
    textEditor->mainUi = this;

    std::vector<EntryPerso*> entries = test(10);
    display_graph(entries, ui);
    display_entries(entries, ui);

    //Chatbox
    MascotChat chat = MascotChat(ui->scrollArea);
    //tests
    for(int i = 0; i<20 ; i++){
        chat<<QString::number(i);
    }
    QString lastm = chat.get_last_message();
    chat<<lastm;

    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide(); //hide the settings menu on launch
    //setting the icon for the setting button
    QPixmap pix(":/pictures/rsc/checklist icon.png");
    int w = ui->settingsButton->width();
    int h = ui->settingsButton->height();
    ui->settingsButton->setIcon(QIcon(pix.scaled(w,h,Qt::KeepAspectRatio)));
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

void MainWindow::toggle_visibility(QWidget *component){
    if(component->isVisible()){
        component->hide();
    }
    else{
        component->show();
    }
}

void MainWindow::display_entries(std::vector<EntryPerso*> entries, Ui::MainWindow *ui) {
    while(!ui->EntriesScroll->widget()->layout()->isEmpty()) {
        ui->graph_frame->removeItem(ui->EntriesScroll->widget()->layout()->takeAt(0));
    }
    for (auto entry: entries) {
        EntryCard *c = new EntryCard(20, 300, 300, "white", entry);
        c->display(ui->EntriesScroll->widget()->layout()); //displays the entry in the main_frame.
    }
}

void MainWindow::display_graph(std::vector<EntryPerso*> entries, Ui::MainWindow *ui) {
    while(!ui->graph_frame->isEmpty()) {
        ui->graph_frame->removeItem(ui->graph_frame->takeAt(0));
    }
    DynamicGraph moodGraph = DynamicGraph(entries);
    moodGraph.display(ui->graph_frame); //displays the graph
    this -> showMaximized();
}

void MainWindow::on_pushButton_clicked() {
    hide();
    all_habits = new All_Habits(this);
    all_habits -> showMaximized();
}

void MainWindow::on_activitie_button_clicked() {
    all_activities my_activities;
    my_activities.setModal(true);
    my_activities.exec();
}

void MainWindow::on_settingsButton_clicked() {
    findChild<QCheckBox*>("mood")->setChecked(saved_mood());
    findChild<QCheckBox*>("sleep")->setChecked(saved_sleep());
    findChild<QCheckBox*>("eating_healthy")->setChecked(saved_eating_healthy());
    findChild<QCheckBox*>("productivity")->setChecked(saved_productivity());
    findChild<QCheckBox*>("communications")->setChecked(saved_communications());
    findChild<QCheckBox*>("screen_time")->setChecked(saved_screen_time());
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

void MainWindow::on_filterButton_clicked() {
    auto spinBox = findChild<QSpinBox*>("numberOfEntries");
    int n = spinBox->value();
    std::vector<EntryPerso*> entries = test(n);
    display_graph(entries, ui);
    display_entries(entries, ui);
}

//helps with debugging; to be replaced later
std::vector<EntryPerso*> MainWindow::test(int n) {
    std::vector<EntryPerso*> entries;
    for (int i = 1; i <= n; i++) {
        EntryPerso *e = new EntryPerso();
        e->set_mood(1+std::rand()%20);
        e->set_qdate(QDate(2022,11,i));
        std::vector<Friend*> fr;
        fr.push_back(new Friend("fr", 1));
        std::vector<Activity*> activity;
        activity.push_back(new Activity("act", 1));
        e->set_friends(fr);
        e->set_activities(activity);
        e->set_title("THIS IS A TITLE2");
        e->set_text("some text ...");
        entries.push_back(e);
    }
    return entries;
}

#include "mainwindow.h"
#include "entryfilter.h"
#include "error_dlg.h"
#include "mascot.h"
#include "ui_all_activities.h"
#include "ui_mainwindow.h"
#include "dynamicgraph.h"
#include "cardclasses.h"
#include "all_activities.h"
#include "file_processing/file_processing/file_save_and_load.h"
#include "texteditor.h"
#include "ui_texteditor.h"
#include "settings.h"
#include "mascotchat.h"
#include "loadHabits.h"
#include <sstream>
#include <iostream>
#include <fstream>

std::vector<Filter_param> filter_params;

std::vector<EntryPerso*> MainWindow::vector_entries;
std::vector<Activity> MainWindow::vector_activities;
std::vector<Friend> MainWindow::vector_friends;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // display canvas created in drag-and-drop

    ////////////////////////////////////////////////////////////////
    /// WHAT YOU CAN ASSUME WE HAVE:
    /// VECTORS THAT ARE SHARED BY ALL COMPONENTS
    ///    std::vector<EntryPerso*>vector_entries;  All the entries
    ///    std::vector<Activity>vector_activities;  All the possible activities to choose from
    ///    std::vector<Friend>vector_friends;       All the friends we can choose from


    //create layout for central scrollable area
    QVBoxLayout *entries_layout = new QVBoxLayout();
    ui->EntriesScroll->widget()->setLayout(entries_layout);

    // We use Friend function to embed the TextEditor into the MainWindow
    textEditor = new TextEditor();
    textEditor->mainUi = this;

    vector_entries = sample_entries(10);
    EntryPerso *e2 = new EntryPerso();
    e2->set_mood(30);
    e2->set_qdate(QDate::currentDate().addDays(-2));

    EntryPerso *e3 = new EntryPerso();
    e3->set_mood(30);
    e3->set_qdate(QDate::currentDate().addDays(-1));

    vector_entries.push_back(e2);
    vector_entries.push_back(e3);

    display_graph(vector_entries, ui);
    display_entries(vector_entries, ui);

    //Chatbox
    MascotChat chat = MascotChat(ui->scrollArea);
    //tests
    for(int i = 0; i<20 ; i++){
        chat<<QString::number(i);
    }
    chat<<std::string("Hello! this is quite a long message  ahbybf zuxh eudh euhfxz xu_ehdx <br>**yezhx**<b>zfhfx</b> zy_h xze hyzehfhx yzeefbxy_zehxy_ze hyehxf uyzhe xfyzehxyzxe hyezh xyzehe hxfyzeh fzyehfx zyehexyzeh f yzehf zef ezyh yze  hfyzeh efzeh uz eh fuzeudh  we can try to add a lot of lines to see what happends...");
    QString lastm = chat.get_last_message();
    chat<<lastm;

    auto settings = findChild<QWidget*>("settings_frame");
    settings->hide(); //hide the settings menu on launch
    //setting the icon for the setting button
    QPixmap pix(":/pictures/rsc/checklist icon.png");
    int w = ui->settingsButton->width();
    int h = ui->settingsButton->height();
    ui->settingsButton->setIcon(QIcon(pix.scaled(w,h,Qt::KeepAspectRatio)));

    std::vector<std::string> current_habits = load_habits();
    for (int i = 0; i<current_habits.size(); i++) {
        ui->habits_label->setText(ui->habits_label->text() + "\n" +QString::fromStdString (current_habits[i]));
    }
}


MainWindow::~MainWindow() {
    delete ui;
}


std::vector<Activity> MainWindow::get_activities(){
    return vector_activities;
}

std::vector<Friend> MainWindow::get_friends(){
    return vector_friends;
}

void MainWindow::update_activities(std::vector<Activity> activities){
    vector_activities = activities;
}

void MainWindow::update_friends(std::vector<Friend> friends){
    vector_friends = friends;
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
    } else {
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
    all_activities *my_activities = new all_activities();
    my_activities->add_previous_cells();
    my_activities->setModal(true);
    my_activities->exec();
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

    vector_entries = sample_entries(100); // this line should be changed to aquire source of entries

    QString type_filter_value = findChild<QComboBox*>("type_filter")->currentText();
    std::string type_filter_str = type_filter_value.toStdString();
    QString operator_filter_value = findChild<QComboBox*>("operation_filter")->currentText();
    std::string operator_filter_str = operator_filter_value.toStdString();
    QString value_filter_value = findChild<QDoubleSpinBox*>("value_filter")->text();
    double value = value_filter_value.toDouble();

    //construct a filter_param object
    struct Filter_param filt;
    filt.is_value_compare = true;
    filt.keyword = type_filter_str;
    filt.opt = operator_filter_str;
    filt.value = value;
    filt.display_num = n;

    //handling duplicated filters
    bool is_insert = true;
    for (int i=0; i<filter_params.size(); i++) {
        if (filter_params[i].keyword == filt.keyword && filter_params[i].opt == filt.opt && filter_params[i].value == filt.value) {
            is_insert = false;
            break;
        }
        if (filter_params[i].keyword == filt.keyword && filt.opt == "=") {
            filter_params.erase(filter_params.begin() + i);
            i--;
        }
        else if (filter_params[i].keyword == filt.keyword && filter_params[i].opt == "=") {
            is_insert = false;
            break;
        }
        if (filter_params[i].keyword == filt.keyword && filter_params[i].opt == filt.opt) {
            if (filt.opt == "<" && filt.value > filter_params[i].value) {
                is_insert = false;
                break;
            }
            else if (filt.opt == "<" && filt.value < filter_params[i].value) {
                filter_params.erase(filter_params.begin() + i);
            }
            else if (filt.opt == ">" && filt.value < filter_params[i].value) {
                is_insert = false;
                break;
            }
            else if (filt.opt == ">" && filt.value > filter_params[i].value) {
                filter_params.erase(filter_params.begin() + i);
            }
        }
    }

    if(is_insert) {
        filter_params.push_back(filt);
    }

    //filter the entries
    std::vector<EntryPerso*> filtered_entries = filter(vector_entries, filter_params[0]);
    for(int i=1; i<filter_params.size(); i++) {
        filtered_entries = filter(filtered_entries, filter_params[i]);
    }

    //error handling
    std::cout << "filtered" << std::endl;
    if (filtered_entries.size() == 0) {
        std::cout << "no entries" << std::endl;
        if(is_insert) {
            filter_params.pop_back();
        }
        // To implement a error dialog here. we have a filter_error.ui file. show the dialog
        QMessageBox::warning(this, "Error", "No entries found with the given filter");
        return;
    }

    

    // update and display the filters
    std::string f = "Filters:   ";
    for (int i=0; i<filter_params.size(); i++) {
        // value keeps 2 digits after the decimal point
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << filter_params[i].value;
        std::string s = stream.str();
        f += filter_params[i].keyword + " " + filter_params[i].opt + " " + s + ";  ";
    }
    findChild<QLabel*>("existing_filters")->setText(QString::fromStdString(f));
    if(filtered_entries.size() < n) {
        n = filtered_entries.size();
    }

    // select the n last entries
    std::vector<EntryPerso*> entries_to_display;
    for (int i=filtered_entries.size()-n; i<filtered_entries.size(); i++) {
        entries_to_display.push_back(filtered_entries[i]);
    }

    display_graph(entries_to_display, ui);
    display_entries(entries_to_display, ui);

}

void MainWindow::on_clear_button_clicked() {
    filter_params.clear();
    findChild<QLabel*>("existing_filters")->setText("Filters: ");
    vector_entries = sample_entries(10); // this line should be changed to aquire source of entries
    display_graph(vector_entries, ui);
    display_entries(vector_entries, ui);
}

void MainWindow::on_newEntryButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    EntryPerso *e = new EntryPerso();
    e->set_mood(0);
    e->set_qdate(QDate::currentDate());
    std::vector<Friend*> fr;
    fr.push_back(new Friend("fr", 1));
    std::vector<Activity*> activity;
    activity.push_back(new Activity("act", 1));
    e->set_friends(fr);
    e->set_activities(activity);
    e->set_title("");
    e->set_text("");
    vector_entries.insert(vector_entries.begin(), e);
    card = new EntryCard(20, 300, 300, "white", e);
    card->display(ui->newEntry);
    card->change();
    card->update();
}

void MainWindow::on_saveEntryButton_clicked() {
    display_graph(vector_entries, ui);
    display_entries(vector_entries, ui);
    ui->stackedWidget->setCurrentIndex(0);
    ui->newEntry->removeItem(ui->newEntry->takeAt(0));
}



//helps with debugging; to be replaced later
std::vector<EntryPerso*> MainWindow::test(int n) {
    std::vector<EntryPerso*> entries;
    for (int i = n; i >= 1; i--) {
        EntryPerso *e = new EntryPerso();
        e->set_mood(1+std::rand()%100);
        e->set_qdate(QDate(2022,11,i));
        std::vector<Friend*> fr;
        fr.push_back(new Friend("fr", 1));
        std::vector<Activity*> activity;
        activity.push_back(new Activity("act", 1));
        e->set_friends(fr);
        e->set_activities(activity);
        e->set_title("THIS IS A TITLE");
        e->set_text("some text ...");
        entries.push_back(e);
    }
    return entries;
}

#include "mainwindow.h"
#include "all_activities.h"
#include "cardclasses.h"
#include "dynamicgraph.h"
#include "entryfilter.h"
#include "error_dlg.h"
#include "file_processing/file_processing/file_save_and_load.h"
#include "loadHabits.h"
#include "mascot.h"
#include "mascotchat.h"
#include "settings.h"
#include "texteditor.h"
#include "ui_all_activities.h"
#include "ui_mainwindow.h"
#include "ui_texteditor.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Filter_param> filter_params;

std::vector<EntryPerso *> MainWindow::vector_entries;
std::vector<Activity> MainWindow::vector_activities;
std::vector<Friend> MainWindow::vector_friends;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this); // display canvas created in drag-and-drop

  ////////////////////////////////////////////////////////////////
  /// WHAT YOU CAN ASSUME WE HAVE:
  /// VECTORS THAT ARE SHARED BY ALL COMPONENTS
  ///    std::vector<EntryPerso*>vector_entries;  All the entries
  ///    std::vector<Activity>vector_activities;  All the possible activities to
  ///    choose from std::vector<Friend>vector_friends;       All the friends we
  ///    can choose from

  // create layout for central scrollable area
  QVBoxLayout *entries_layout = new QVBoxLayout();
  ui->EntriesScroll->widget()->setLayout(entries_layout);
  // get the width of the scrollable area

  // We use Friend function to embed the TextEditor into the MainWindow
  textEditor = new TextEditor();
  textEditor->mainUi = this;
  // we want to set the textEditor with the same size as the place of embedding
  /*vector_entries = sample_entries(10);
  EntryPerso *e2 = new EntryPerso();
  e2->set_mood(30);
  e2->set_qdate(QDate::currentDate().addDays(-2));

  EntryPerso *e3 = new EntryPerso();
  e3->set_mood(80);
  e3->set_qdate(QDate::currentDate().addDays(-1));


  vector_entries.push_back(e2);
  vector_entries.push_back(e3);*/

  // create a folder for the entries if it doesn't already exist
  if (!QDir("Entries").exists()) {
    QDir().mkdir("Entries");
  }

  // load previous entries
  QDir dir(QDir::currentPath() + "/Entries");
  for (const QString &filename : dir.entryList(QDir::Files)) {
    vector_entries.push_back(
        load_entryperso("Entries/" + filename.toStdString()));
  }

  // save the card corresponding to the current day in case it has to be
  // modified
  if (!vector_entries.empty()) {
    EntryPerso *newest_entry = vector_entries.back();
    if (newest_entry->get_qdate() == QDate::currentDate()) {
      today_card =
          new EntryCard(20, 300, 300, "white", newest_entry, true, this);
    }
  }

  display_graph(vector_entries, ui);
  display_entries(vector_entries, ui);

  // test for recap display
  EntryRecap *recap = new EntryRecap();
  EntryPerso *e = new EntryPerso();
  e->set_mood(1 + std::rand() % 100);
  std::vector<Friend *> fr;
  fr.push_back(new Friend("fr", 1));
  std::vector<Activity *> activity;
  activity.push_back(new Activity("act", 1));
  e->set_friends(fr);
  e->set_activities(activity);
  e->set_title("THIS IS A TITLE");
  e->set_text("some text ...");
  recap->set_best_day(*e);
  recap->set_worst_day(*e);
  EntryCard *entry_r = new EntryCard(15, 200, 200, "white", recap, false, this);
  entry_r->display(ui->EntriesScroll->widget()->layout());

  // Chatbox
  MascotChat chat = MascotChat(ui->scrollArea);
  // tests
  for (int i = 0; i < 20; i++) {
    chat << QString::number(i);
  }
  chat.add_mascot();
  chat << std::string(
      "this message is long to check if the whole thing would fit into the "
      "text label and also to be easy to track because it makes more sense");
  chat.add_mascot();
  QString lastm = chat.get_last_message();
  chat << lastm;
  chat.add_mascot();

  auto settings = findChild<QWidget *>("settings_frame");
  settings->hide(); // hide the settings menu on launch
  // setting the icon for the setting button
  QPixmap pix(":/pictures/rsc/checklist icon.png");
  int w = ui->settingsButton->width();
  int h = ui->settingsButton->height();
  ui->settingsButton->setIcon(QIcon(pix.scaled(w, h, Qt::KeepAspectRatio)));

  std::vector<std::string> current_habits = load_habits();
  for (int i = 0; i < current_habits.size(); i++) {
    ui->habits_label->setText(ui->habits_label->text() + "\n" +
                              QString::fromStdString(current_habits[i]));
  }
}

MainWindow::~MainWindow() { delete ui; }

std::vector<Activity> MainWindow::get_activities() { return vector_activities; }

Activity *MainWindow::get_activity_at_i(long long unsigned i) {
  return &vector_activities.at(i);
}

std::vector<Friend> MainWindow::get_friends() { return vector_friends; }

Friend *MainWindow::get_friend_at_i(long long unsigned i) {
  return &vector_friends.at(i);
}

void MainWindow::update_activities(std::vector<Activity> activities) {
  vector_activities = activities;
}

void MainWindow::update_friends(std::vector<Friend> friends) {
  vector_friends = friends;
}

void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton answr_btn = QMessageBox::question(
      this, tr("Paper friend"), tr("Are you sure?\n"),
      QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
      QMessageBox::Yes);
  if (answr_btn != QMessageBox::Yes) {
    event->ignore();
  } else {
    event->accept();
  }
}

void MainWindow::toggle_visibility(QWidget *component) {
  if (component->isVisible()) {
    component->hide();
  } else {
    component->show();
  }
}

void MainWindow::display_entries(std::vector<EntryPerso *> entries,
                                 Ui::MainWindow *ui) {
  while (!ui->EntriesScroll->widget()->layout()->isEmpty()) {
    QLayoutItem *item = ui->EntriesScroll->widget()->layout()->takeAt(0);
    ui->graph_frame->removeItem(item);
    delete item->widget();
    delete item;
    qDebug() << "removed";
  }
  /*for (auto entry: entries) {
      EntryCard *c = new EntryCard(20, 300, 300, "white", entry, true, this);
      c->display(ui->EntriesScroll->widget()->layout()); //displays the entry in
  the main_frame. qDebug()<< "displayed";
  }*/

  // displaying in reversed order
  for (auto entry = entries.rbegin(); entry != entries.rend(); ++entry) {
    if ((*entry)->get_qdate() == QDate::currentDate()) {
      today_card->display(ui->EntriesScroll->widget()->layout());
    } else {
      EntryCard *c = new EntryCard(20, 300, 300, "white", *entry, true, this);
      c->display(ui->EntriesScroll->widget()
                     ->layout()); // displays the entry in the main_frame.
      qDebug() << "displayed";
    }
  }
}

void MainWindow::display_graph(std::vector<EntryPerso *> entries,
                               Ui::MainWindow *ui) {
  while (!ui->graph_frame->isEmpty()) {
    ui->graph_frame->removeItem(ui->graph_frame->takeAt(0));
  }
  DynamicGraph moodGraph = DynamicGraph(entries);
  moodGraph.display(ui->graph_frame); // displays the graph
  this->showMaximized();
}

void MainWindow::on_pushButton_clicked() {
  hide();
  all_habits = new All_Habits(this);
  all_habits->showMaximized();
}

void MainWindow::on_activitie_button_clicked() {
  all_activities *my_activities = new all_activities(vector_activities);
  my_activities->add_previous_cells();
  my_activities->setModal(true);
  my_activities->exec();
}

void MainWindow::on_settingsButton_clicked() {
  findChild<QCheckBox *>("mood")->setChecked(saved_mood());
  findChild<QCheckBox *>("sleep")->setChecked(saved_sleep());
  findChild<QCheckBox *>("eating_healthy")->setChecked(saved_eating_healthy());
  findChild<QCheckBox *>("productivity")->setChecked(saved_productivity());
  findChild<QCheckBox *>("communications")->setChecked(saved_communications());
  findChild<QCheckBox *>("screen_time")->setChecked(saved_screen_time());
  auto settings = findChild<QWidget *>("settings_frame");
  toggle_visibility(settings);
  auto chat = findChild<QWidget *>("scrollArea");
  toggle_visibility(chat);
}

void MainWindow::on_save_settings_clicked() {
  std::ofstream myfile;
  myfile.open("settings.txt");
  myfile << findChild<QCheckBox *>("mood")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("sleep")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("eating_healthy")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("productivity")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("communications")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("screen_time")->isChecked() << "\n";
  myfile.close();
  auto settings = findChild<QWidget *>("settings_frame");
  settings->hide();
  auto chat = findChild<QWidget *>("scrollArea");
  chat->show();
}

void MainWindow::on_filterButton_clicked() {
  auto spinBox = findChild<QSpinBox *>("numberOfEntries");
  int n = spinBox->value();

  // vector_entries = sample_entries(100); // this line should be changed to
  // aquire source of entries

  QString type_filter_value =
      findChild<QComboBox *>("type_filter")->currentText();
  std::string type_filter_str = type_filter_value.toStdString();
  QString operator_filter_value =
      findChild<QComboBox *>("operation_filter")->currentText();
  std::string operator_filter_str = operator_filter_value.toStdString();
  //QString value_filter_value =
      //findChild<QDoubleSpinBox *>("value_filter")->text();
  double value = findChild<QDoubleSpinBox *>("value_filter")->value();

  // construct a filter_param object
  struct Filter_param filt;
  filt.is_value_compare = true;
  filt.keyword = type_filter_str;
  filt.opt = operator_filter_str;
  filt.value = value;
  filt.display_num = n;

  // handling duplicated filters
  bool is_insert = true;
  for (int i = 0; i < filter_params.size(); i++) {
    if (filter_params[i].keyword == filt.keyword &&
        filter_params[i].opt == filt.opt &&
        filter_params[i].value == filt.value) {
      is_insert = false;
      break;
    }
    if (filter_params[i].keyword == filt.keyword && filt.opt == "=") {
      filter_params.erase(filter_params.begin() + i);
      i--;
    } else if (filter_params[i].keyword == filt.keyword &&
               filter_params[i].opt == "=") {
      filter_params.erase(filter_params.begin() + i);
      i--;
    }
    if (filter_params[i].keyword == filt.keyword &&
        filter_params[i].opt == filt.opt) {
      filter_params.erase(filter_params.begin() + i);
      i--;
    }
  }

  if (is_insert) {
    filter_params.push_back(filt);
  }

  // filter the entries
  std::vector<EntryPerso *> filtered_entries =
      filter(vector_entries, filter_params[0]);
  for (int i = 1; i < filter_params.size(); i++) {
    filtered_entries = filter(filtered_entries, filter_params[i]);
  }

  // error handling
  std::cout << "filtered" << std::endl;
  if (filtered_entries.size() == 0) {
    std::cout << "no entries" << std::endl;
    if (is_insert) {
      filter_params.pop_back();
    }
    // To implement a error dialog here. we have a filter_error.ui file. show
    // the dialog
    QMessageBox::warning(this, "Error",
                         "No entries found with the given filter");
    return;
  }

  // update and display the filters
  std::string f = "Filters:   ";
  for (int i = 0; i < filter_params.size(); i++) {
    // value keeps 2 digits after the decimal point
    std::stringstream stream;
    //qDebug()<<filter_params[i].value<<"HERE";
    stream << std::fixed << std::setprecision(1) << filter_params[i].value;
    std::string s = stream.str();
    f +=
        filter_params[i].keyword + " " + filter_params[i].opt + " " + s + ";  ";
  }
  findChild<QLabel *>("existing_filters")->setText(QString::fromStdString(f));
  if (filtered_entries.size() < n) {
    n = filtered_entries.size();
  }

  // select the n last entries
  std::vector<EntryPerso *> entries_to_display;
  for (int i = filtered_entries.size() - n; i < filtered_entries.size(); i++) {
    entries_to_display.push_back(filtered_entries[i]);
  }

  display_entries(entries_to_display, ui);
  display_graph(entries_to_display, ui);
}

void MainWindow::on_helpFilterBox_clicked() {
  // implement a help dialog here. show the dialog.
  QMessageBox::information(this, "Help", "This is a help dialog");
}

void MainWindow::on_clear_button_clicked() {
  filter_params.clear();
  findChild<QLabel *>("existing_filters")->setText("Filters: ");
  // vector_entries = sample_entries(10); // this line should be changed to
  // aquire source of entries
  display_entries(vector_entries, ui);
  display_graph(vector_entries, ui);
}

void MainWindow::on_newEntryButton_clicked() {
  // more compact code for when the test entries are replaced with real entries
  /*
  if
  (!std::filesystem::exists("Entries/"+QDate::currentDate().toString("MM.dd.yyyy").toStdString()+".json"))
  { EntryPerso *today_entry = new EntryPerso(); save_entryperso(*today_entry);
      vector_entries.push_back(today_entry);
      today_card = new EntryCard(20, 300, 300, "white", today_entry, true,
  this); display_entries(vector_entries, ui);
  }
  */
  if (vector_entries.empty()) {
    EntryPerso *today_entry = new EntryPerso();
    save_entryperso(*today_entry);
    vector_entries.push_back(today_entry);
    today_card = new EntryCard(20, 300, 300, "white", today_entry, true, this);
    display_entries(vector_entries, ui);
  } else {
    if (vector_entries.back()->get_qdate() != QDate::currentDate()) {
      EntryPerso *today_entry = new EntryPerso();
      save_entryperso(*today_entry);
      vector_entries.push_back(today_entry);
      today_card =
          new EntryCard(20, 300, 300, "white", today_entry, true, this);
      display_entries(vector_entries, ui);
    }
  }
  ui->EntriesScroll->verticalScrollBar()->setValue(0);
  today_card->change();
}

// helps with debugging; to be replaced later
std::vector<EntryPerso *> MainWindow::test(int n) {
  std::vector<EntryPerso *> entries;
  for (int i = n; i >= 1; i--) {
    EntryPerso *e = new EntryPerso();
    e->set_mood(1 + std::rand() % 100);
    e->set_qdate(QDate(2022, 11, i));
    std::vector<Friend *> fr;
    fr.push_back(new Friend("fr", 1));
    std::vector<Activity *> activity;
    activity.push_back(new Activity("act", 1));
    e->set_friends(fr);
    e->set_activities(activity);
    e->set_title("THIS IS A TITLE");
    e->set_text("some text ...");
    entries.push_back(e);
  }
  return entries;
}

void MainWindow::update_graph() { display_graph(vector_entries, ui); }

void MainWindow::on_people_button_clicked() {}

void MainWindow::on_Test_entries_clicked() {
  vector_entries = sample_entries(100);
  display_entries(vector_entries, ui);
  display_graph(vector_entries, ui);
}

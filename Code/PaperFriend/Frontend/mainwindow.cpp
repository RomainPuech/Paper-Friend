#include "mainwindow.h"
#include "all_activities.h"
#include "cardclasses.h"
#include "display_daily_habit.h"
#include "dynamicgraph.h"
#include "entryfilter.h"
#include "error_dlg.h"
#include "file_processing/file_processing/file_save_and_load.h"
#include "mascot.h"
#include "mascotchat.h"
#include "settings.h"
#include "texteditor.h"
#include "ui_all_activities.h"
#include "ui_all_habits.h"
#include "ui_mainwindow.h"
#include "ui_texteditor.h"
#include <QDate>
#include <QDebug>
#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

//// Declarations
std::vector<Filter_param> filter_params;
std::vector<EntryPerso *> MainWindow::vector_entries; // All the personal
                                                      // entries
std::vector<EntryPerso *> MainWindow::displayed_entries;
std::vector<EntryRecap *> MainWindow::vector_recaps; // All the recap entries
std::vector<Activity>
    MainWindow::vector_activities; // All the possible activities to choose from
std::vector<EntryCard *> MainWindow::displayed_cards;

//// Helper functions
template <typename T> bool sort_by_date(const T e1, const T e2) {
  return e1->get_qdate().daysTo(e2->get_qdate()) > 0;
}

/// To generate example data for the presentation

std::vector<EntryPerso *>
MainWindow::for_presentation__generate_entries_from_date_mood(
    int n, std::vector<double> moods) {
  qDebug() << QString("data I'm called");
  std::vector<EntryPerso *> res;
  for (int i = n - 1; i > +0; ++i) {
    qDebug() << QString::number(i);
    EntryPerso *e = new EntryPerso();
    e->set_qdate(QDate::currentDate().addDays(i));
    e->set_mood(moods[i]);
    res.push_back(e);
  }
  return res;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), reacted_to_entry(false) {

  //////// Layout
  ui->setupUi(this); // display canvas created in drag-and-drop

  // create layout for central scrollable area
  QVBoxLayout *entries_layout = new QVBoxLayout();
  ui->EntriesScroll->widget()->setLayout(entries_layout);

  // get the width of the scrollable area
  // We use Friend function to embed the TextEditor into the MainWindow
  textEditor = new TextEditor();
  textEditor->mainUi = this;
  // we want to set the textEditor with the same size as the place of embedding

  connect(ui->type_filter, SIGNAL(currentTextChanged(const QString &)), this,
          SLOT(MainWindow::on_type_filter_currentTextChanged(const QString &)));

  /////// Loading of parameters and data
  // create a folder for the entries if it doesn't already exist
  if (!QDir("Entries").exists()) {
    QDir().mkdir("Entries");
  }
  if (!QDir("Recap_entries").exists()) {
    QDir().mkdir("Recap_entries");
  }

  // load previously entered activities
  if (!std::filesystem::exists("activities.json")) {
    save_activities(vector_activities);
  }
  vector_activities = load_activities();

  /// To generate example data for presentation:
  /*
  std::vector<double> moods = {10.,10.,40.,50.,99.};
  int n =5;
  std::vector<EntryPerso*> demo_data =
  MainWindow::for_presentation__generate_entries_from_date_mood(n,moods);
  qDebug()<<QString::number(demo_data.size())<<QString("Debug here");
  for(EntryPerso*e:demo_data){
      vector_entries.push_back(e);
  }
  */
  // load previous entries
  QDir dir(QDir::currentPath() + "/Entries");
  for (const QString &filename : dir.entryList(QDir::Files)) {
    vector_entries.push_back(
        load_entryperso(filename.toStdString(), vector_activities));
  }

  if(vector_entries.size()==0)
  {
      EntryPerso* demo_entry = new EntryPerso();
      demo_entry->set_title("Welcome in Paper Friend!");
      demo_entry->set_text("<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Click the Modify Entry button just below to start writing your first entry!</span></p>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p>\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You can write about:</p>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n<ul type=\"circle\" style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">How you <span style=\" font-weight:700;\">feel</span></li>\n<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">What you <span style=\" font-weight:700;\">did</span> today</li>\n<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">What could be <span style=\" font-weight:700;\">improved</span> in your day...</li></ul>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Script MT Bold'; font-size:10pt; font-weight:700;\">The possibilities are endless! </span></p>\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Script MT Bold'; font-size:10pt; font-weight:700;\"><br /></p></body></html>");
      vector_entries.push_back(demo_entry);
  }

  sort(vector_entries.begin(), vector_entries.end(), sort_by_date<EntryPerso*>); //oldest entry first

  // Load habits

  std::vector<QStringList> habits_of_the_day = get_daily_habits();//vector of habits and their parameters done today
  //Line of code below displays the question for each habit done on this day
  if (habits_of_the_day.size() > 0) {
    ui->generic_habit_label->setVisible(false);
    for (unsigned long i = 0; i < habits_of_the_day.size(); i++) {
      Display_Daily_Habit *new_daily_habit = new Display_Daily_Habit(
          habits_of_the_day[i][0], habits_of_the_day[i][2], this);
      ui->verticalLayout_daily_habits->addWidget(new_daily_habit);
    }
  } else {
    ui->habits_scrollArea->setVisible(false);
  }


  
  std::string f = "Filters:   ";
  std::stringstream stream;
  std::string s = stream.str();
    f +=
        "last_n_entries = 30; ";
  findChild<QLabel *>("existing_filters")->setText(QString::fromStdString(f));

  size_t n = 30;
  if (vector_entries.size() < n) {
    n = vector_entries.size();
  }
  std::vector<EntryPerso *> entries_to_display;
  for (size_t i = vector_entries.size() - n; i < vector_entries.size();
       i++) {
    entries_to_display.push_back(vector_entries[i]);
  }

  displayed_entries = entries_to_display;

  struct Filter_param filt;
  filt.is_value_compare = true;
  filt.keyword = "last_n_entries";
  filt.opt = "=";
  filt.value = 30;
  filt.display_num = 30;
  filter_params.push_back(filt);



  // displayed_entries = vector_entries;

  // save the card corresponding to the current day in case it has to be
  // modified
  today_card = nullptr;
  if (!vector_entries.empty() &&
      vector_entries.back()->get_qdate() == QDate::currentDate()) {
    EntryPerso *newest_entry = vector_entries.back();
    if (newest_entry->get_qdate() == QDate::currentDate()) {
      today_card =
          new EntryCard(20, 300, 300, "white", newest_entry, true, this); //entry for today has already been recorded
    }
  }

  // Load previous recaps dates
  std::vector<QString> last_recaps_dates = load_last_recaps_dates(); //dates of the last weekly, monthly and yearly recap

  // load previous recaps
  QDir dir_recaps(QDir::currentPath() + "/Recap_entries");
  for (const QString &filename : dir_recaps.entryList(QDir::Files)) {
    vector_recaps.push_back(
        load_entryrecap(filename.toStdString(), vector_activities));
  }
  // sort them by the date
  sort(vector_recaps.begin(), vector_recaps.end(), sort_by_date<EntryRecap *>); // oldest recaps first
  //// frontend that needs data to be rendered
  display_entries(false); // display with recaps

  // Chatbox
  chat = MascotChat(ui->scrollArea);
  welcome();

  // Settings
  auto settings = findChild<QWidget *>("settings_frame");
  settings->hide(); // hide the settings menu on launch
  // setting the icon for the setting button
  QPixmap pix(":/pictures/rsc/checklist icon.png");
  int w = ui->settingsButton->width();
  int h = ui->settingsButton->height();
  ui->settingsButton->setIcon(QIcon(pix.scaled(w, h, Qt::KeepAspectRatio)));

  update_graphs();

  // style the application
  QApplication::setStyle(QStyleFactory::create("Fusion"));




}

MainWindow::~MainWindow() {
  delete ui;
  for (auto const &[key, graphptr] : dynamic_graphs) {
    delete graphptr;
  }
}

std::vector<Activity> MainWindow::get_activities() { return vector_activities; }

void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton answr_btn = QMessageBox::question(
      this, tr("Paper friend"), tr("Are you sure?\n"),
      QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
  if (answr_btn != QMessageBox::Yes) {
    event->ignore();
  } else {
    for (auto entry : vector_entries) {
      save_entryperso(*entry);
    }
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

void MainWindow::update_graphs() {
  ui->tabWidget->clear();
  display_graph("mood");
  display_graph("sleep");
  display_graph("eating healthy");
  display_graph("productivity");
  display_graph("communications");
  display_graph("physical activity");
}

void MainWindow::display_entries(bool dont_display_recaps) {

  while (!ui->EntriesScroll->widget()->layout()->isEmpty()) {
    QLayoutItem *item = ui->EntriesScroll->widget()->layout()->takeAt(0);
    // clear EntriesScroll
    delete item->widget();
    delete item;
  }
  displayed_cards.clear();
  // displaying in reversed order
  std::vector<EntryRecap *>::reverse_iterator rec = vector_recaps.rbegin();
  if (dont_display_recaps) {
    rec = vector_recaps.rend();
  }
  for (auto entry = displayed_entries.rbegin();
       entry != displayed_entries.rend(); ++entry) {
    if (rec != vector_recaps.rend() &&
        (*rec)->get_qdate().daysTo((*entry)->get_qdate()) <= 0) { //there is a recap that is newer that the entry
      if(((*rec)->get_type() == 0 && saved_week()) || ((*rec)->get_type() == 1 && saved_month()) || ((*rec)->get_type() == 2 && saved_year())){
      EntryCard *c = new EntryCard(20, 300, 300, "white", *rec, true, this);
      c->display(ui->EntriesScroll->widget()
                     ->layout()); // displays recap in the main_frame if said so in the settings
      }
      ++rec;
      entry--;
    } else if ((*entry)->get_qdate() == QDate::currentDate()) { // today entry
      if (today_card == nullptr) {
        today_card = new EntryCard(20, 300, 300, "white", *entry, false, this);
      } else {
        today_card = new EntryCard(20, 300, 300, "white", *entry, true, this);
      }
      today_card->display(ui->EntriesScroll->widget()->layout());
      displayed_cards.push_back(today_card);
    } else { // regular entryperso display
      EntryCard *c = new EntryCard(20, 300, 300, "white", *entry, true, this);
      c->display(ui->EntriesScroll->widget()
                     ->layout()); // displays the entry in the main_frame.
      displayed_cards.push_back(c);
    }
  } while(rec != vector_recaps.rend()){
      EntryCard *c = new EntryCard(20, 300, 300, "white", *rec, true, this);
      c->display(ui->EntriesScroll->widget()
                     ->layout()); // displays the remaining recaps in the main_frame, unnecessary unless we change our machine date...
      ++rec;
  }
}

void MainWindow::display_graph(QString tracked_parameter) {
  QWidget *tab = new QWidget();
  tab->setStyleSheet("QWidget{background-color: rgb(255,255,255);}");
  QHBoxLayout *graph = new QHBoxLayout(tab);
  ui->tabWidget->addTab(tab, tracked_parameter);

  if (dynamic_graphs.find(tracked_parameter) != dynamic_graphs.end()) {
    delete dynamic_graphs[tracked_parameter];
  }
  DynamicGraph *graphptr =
      new DynamicGraph(displayed_entries, tracked_parameter);
  dynamic_graphs[tracked_parameter] = graphptr;
  graphptr->display(graph);
  this->showMaximized();
}

void MainWindow::on_pushButton_clicked() {
  all_habits = new All_Habits(ui, this);
  all_habits->setModal(true);
  all_habits->exec();
}

void MainWindow::on_activitie_button_clicked() {
  all_activities *my_activities = new all_activities(this, vector_activities);
  my_activities->setModal(true);
  my_activities->exec();
}

void MainWindow::on_settingsButton_clicked() {
  findChild<QCheckBox *>("Weekly_recaps")->setChecked(saved_week());
  findChild<QCheckBox *>("Monthly_recaps")->setChecked(saved_month());
  findChild<QCheckBox *>("Yearly_recaps")->setChecked(saved_year());
  auto settings = findChild<QWidget *>("settings_frame");
  toggle_visibility(settings);
  auto chat = findChild<QWidget *>("scrollArea");
  toggle_visibility(chat);
}

void MainWindow::on_save_settings_clicked() {
  std::ofstream myfile;
  myfile.open("settings.txt");
  myfile << findChild<QCheckBox *>("Weekly_recaps")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("Monthly_recaps")->isChecked() << "\n";
  myfile << findChild<QCheckBox *>("Yearly_recaps")->isChecked() << "\n";
  myfile.close();
  auto settings = findChild<QWidget *>("settings_frame");
  settings->hide();
  auto chat = findChild<QWidget *>("scrollArea");
  chat->show();
  display_entries(false);
}

void MainWindow::on_filterButton_clicked() {
  if (vector_entries.size() == 0) {
    // error dialogue box
    QMessageBox::warning(this, "Error",
                         "No entries to filter. Please add an entry first.");
    return;
  }

  std::unordered_map<std::string, std::string> map_filter{
      {"mood", "mood"},
      {"sleep wellness", "sleep"},
      {"eating healthy", "eating_healthy"},
      {"productivity", "productivity"},
      {"socializing", "socializing"},
      {"physical activity", "physical_activity"},
      {"show last n entries", "last_n_entries"}};

  QString type_filter_value =
      findChild<QComboBox *>("type_filter")->currentText();
  std::string type_filter_str = type_filter_value.toStdString();
  type_filter_str = map_filter[type_filter_str];
  QString operator_filter_value =
      findChild<QComboBox *>("operation_filter")->currentText();
  std::string operator_filter_str = operator_filter_value.toStdString();
  // QString value_filter_value =
  // findChild<QDoubleSpinBox *>("value_filter")->text();
  double value = findChild<QDoubleSpinBox *>("value_filter")->value();
  size_t n = 30;

  // construct a filter_param object
  struct Filter_param filt;
  filt.is_value_compare = true;
  filt.keyword = type_filter_str;
  filt.opt = operator_filter_str;
  filt.value = value;
  filt.display_num = n;

  // handling duplicated filters
  bool is_insert = true;
  for (size_t i = 0; i < filter_params.size(); i++) {
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
    if (filter_params[i].keyword == filt.keyword &&
        filter_params[i].value == filt.value) {
      filter_params.erase(filter_params.begin() + i);
      i--;
    }
  }

  if (is_insert) {
    filter_params.push_back(filt);
  }

  for (size_t i = 0; i < filter_params.size(); i++) {
    if (filter_params[i].keyword == "last_n_entries") {
      n = filter_params[i].value;
      break;
    }
  }

  // filter the entries
  std::vector<EntryPerso *> filtered_entries = vector_entries;
  for (size_t i = 0; i < filter_params.size(); i++) {
    if (filter_params[i].keyword == "last_n_entries") {
      continue;
    }
    filtered_entries = filter(filtered_entries, filter_params[i]);
  }

  // error handling
  if (filtered_entries.size() == 0) {
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
  for (size_t i = 0; i < filter_params.size(); i++) {
    // value keeps 2 digits after the decimal point
    std::stringstream stream;

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
  for (size_t i = filtered_entries.size() - n; i < filtered_entries.size();
       i++) {
    entries_to_display.push_back(filtered_entries[i]);
  }

  displayed_entries = entries_to_display;
  display_entries(true);
  update_graphs();
}

void MainWindow::on_clear_button_clicked() {
  filter_params.clear();
  findChild<QLabel *>("existing_filters")->setText("Filters: ");
  // vector_entries = sample_entries(10); // this line should be changed to
  // aquire source of entries
  displayed_entries = vector_entries;
  display_entries(false);
  update_graphs();
}

// if type_filter is updated
void MainWindow::on_type_filter_currentTextChanged(const QString &arg1) {
  // update the operator_filter
  std::string type_filter_str = arg1.toStdString();

  if (type_filter_str == "show last n entries") {
    // change the operator_filter to "="
    findChild<QComboBox *>("operation_filter")->clear();
    findChild<QComboBox *>("operation_filter")->addItem("=");
    findChild<QComboBox *>("operation_filter")->setEnabled(false);
  } else {
    findChild<QComboBox *>("operation_filter")->clear();
    findChild<QComboBox *>("operation_filter")->addItem("=");
    findChild<QComboBox *>("operation_filter")->addItem(">");
    findChild<QComboBox *>("operation_filter")->addItem("<");
    findChild<QComboBox *>("operation_filter")->setEnabled(true);
  }
}

void MainWindow::on_newEntryButton_clicked() {
  if (vector_entries.empty() ||
      vector_entries.back()->get_qdate() != QDate::currentDate()) {
    // today entry doesn't exist
    EntryPerso *today_entry = new EntryPerso();
    for (Activity const &activity : vector_activities) {
      Activity *to_add =
          new Activity(activity.get_name(), activity.get_type(), 0);
      today_entry->add_activity(to_add);
    }
    vector_entries.push_back(today_entry);
    displayed_entries.push_back(today_entry);
    display_entries(false);
  } else {
    if (displayed_entries.empty() ||
        displayed_entries.back()->get_qdate() != QDate::currentDate()) {
      // today entry exists but is not in the displayed entries
      displayed_entries.push_back(vector_entries.back());
      display_entries(false);
    }
  }
  ui->EntriesScroll->verticalScrollBar()->setValue(0);
  // today_card->change(); this will mess up the program because we can end up
  // with two cards in modify mode
}
void MainWindow::on_suggestions_button_clicked() {
  DataAnalysis data_analysis = DataAnalysis(vector_entries);
  std::string suggestion = data_analysis.suggestion();
  chat << suggestion;
  chat.add_mascot(60);

}
void MainWindow::generate_recap() {
  // first check if we need to generate a weekly/monthly/yearly recap
  // last_recaps_dates is the vector containing the string of the dates of the
  // last [0]weekly, [1]monthly and [2]yearly recap.
  std::vector<QString> last_recaps_dates = load_last_recaps_dates();
  bool generated_recap = false;
  if (last_recaps_dates.empty()) {
    QDate date = QDate::currentDate().addDays(-1);
    last_recaps_dates.push_back(date.toString("yyyy.MM.dd"));
    last_recaps_dates.push_back(date.toString("yyyy.MM.dd"));
    last_recaps_dates.push_back(date.toString("yyyy.MM.dd"));
  }
  // weekly
  if (saved_week() and QDate::currentDate().dayOfWeek() == 7) // If it's Sunday
  {
    QString date_last_recap = last_recaps_dates[0];
    if (date_last_recap != QDate::currentDate().toString("yyyy.MM.dd")) {
      chat << QString("It's Sunday! Time for a weekly recap ");
      chat.add_mascot(89);
      last_recaps_dates[0] = QDate::currentDate().toString("yyyy.MM.dd");
      DataAnalysis analysis = DataAnalysis(vector_entries);
      EntryRecap *recap_w = analysis.weekly_recap();
      generated_recap = true;
      vector_recaps.push_back(recap_w);
      save_entryrecap(*recap_w);
    }
  }
  // monthly
  if (saved_month() and
      QDate::currentDate().daysInMonth() ==
          QDate::currentDate().day()) // If it's the last day of the month
  {
    QString date_last_recap = last_recaps_dates[1];
    if (date_last_recap != QDate::currentDate().toString("yyyy.MM.dd")) {
      chat << QString("Last day of the month means time for a montly recap!");
      chat.add_mascot(65);
      last_recaps_dates[1] = QDate::currentDate().toString("yyyy.MM.dd");
      DataAnalysis analysis = DataAnalysis(vector_entries);
      EntryRecap *recap_m = analysis.monthly_recap();
      generated_recap = true;
      vector_recaps.push_back(recap_m);
      save_entryrecap(*recap_m);
    }
  }
  // yearly
  if (saved_year() and QDate::currentDate().month() == 12 &&
      QDate::currentDate().day() == 31) // If it's December 31st
  {
    QString date_last_recap = last_recaps_dates[2];
    if (date_last_recap != QDate::currentDate().toString("yyyy.MM.dd")) {
      chat << QString("Before celebrating the new year, let's look back to ") +
                  QString::number(QDate::currentDate().year()) +
                  QString(" and ponder.");
      chat.add_mascot(66);
      last_recaps_dates[2] = QDate::currentDate().toString("yyyy.MM.dd");
      DataAnalysis analysis = DataAnalysis(vector_entries);
      EntryRecap *recap_y = analysis.yearly_recap();
      vector_recaps.push_back(recap_y);
      generated_recap = true;
      save_entryrecap(*recap_y);
    }
  }
    if(generated_recap){
  save_last_recaps_dates(last_recaps_dates);
  display_entries(false);
  ui->EntriesScroll->verticalScrollBar()->setValue(0);
    }


}

void MainWindow::react_to_last_entry() {
  if (!reacted_to_entry) {
    EntryPerso *last_entry =
        vector_entries[vector_entries.size() -
                       1]; // called before generate recap so we are sure it is
                           // an EntryPerso
    if (last_entry->get_mood() == 0) {
      std::vector<QString> msg_vect = {
          "Did you forget to put in your mood ?",
          "If not, I'm very sorry for the day you had. It's good that you put "
          "your thoughts on paper.",
          "Don't hesitate to seek the help of a relative or of a professional "
          "if you feel like you loose control.<br>Don't worry, everything "
          "eventually gets better."};
      chat.display(msg_vect, last_entry->get_mood());
    } else if (last_entry->get_mood() < 30) {
      std::vector<QString> msg_vect = {
          "Oh, I'm sorry for the day you had.",
          "Don't forget that you are never alone and talking to a relative or "
          "a professional can help you going through hard times."};
      chat.display(msg_vect, last_entry->get_mood());
    } else if (last_entry->get_mood() < 50) {
      std::vector<QString> msg_vect = {
          "Seems like you spent a pretty tough day...",
          "I hope it'll be better tomorrow."};
      chat.display(msg_vect, last_entry->get_mood());
    } else if (last_entry->get_mood() < 75) { // between 50 and 75
      std::vector<QString> msg_vect = {
          "Looks like a fine day.",
          "What could you improve to make it better?"};
      chat.display(msg_vect, last_entry->get_mood());
    } else if (last_entry->get_mood() < 85) {
      std::vector<QString> msg_vect = {"Someone had a happy day.",
                                       "It's awesome!!"};
      chat.display(msg_vect, last_entry->get_mood());
    } else if (last_entry->get_mood() < 95) { // between 85 and 90
      std::vector<QString> msg_vect = {"What a great day!",
                                       "Take the time to savor it."};
      chat.display(msg_vect, last_entry->get_mood());
    } else {
      std::vector<QString> msg_vect = {
          "Wow, you spent an amazing day!",
          "It hope it will stay anchored in your memory forever."};
      chat.display(msg_vect, last_entry->get_mood());
    }
    reacted_to_entry = true;
  }
}

void MainWindow::welcome() {
  //now the following if is superfluous since we add a demo entry if it's empty
  //but ut's still better to keep the if for robustness if we decide to remove that demo entry in the future.
  if (!vector_entries.empty()) {
    EntryPerso *last_entry = vector_entries[vector_entries.size() - 1];
    int daysago = (last_entry->get_qdate()).daysTo(QDate::currentDate());
    if (daysago == 0 and last_entry->get_title()!="Welcome in Paper Friend!") {
      chat << QString("Hello again!");
      chat.add_mascot(-1);
      chat << QString("I hope you enjoyed yourself today!!");
      chat.add_mascot(60);
    } else if (daysago == 1) {
      chat << QString("Hello!I would love to know how was your day!");
      chat.add_mascot(-1);
      chat << QString("Tell me through the entry.");
      chat.add_mascot(90);
    } else if (daysago > 365) {
      chat << QString("Welcome back");
      chat.add_mascot(-1);
      chat << QString("I though I would never see you again! How are you?");
      chat.add_mascot(60);
    } else if (daysago > 14) {
      chat << QString("It's been a while!");
      chat.add_mascot(-1);
      chat << QString("It's good to see you again!!");
      chat.add_mascot(90);
    } else if (daysago > 6) {
      chat << QString("Welcome back!");
      chat.add_mascot(-1);
      chat << QString("How has it been going?");
      chat.add_mascot(60);
    } else if (daysago > 1) {
      chat << QString("Hellooo!!");
      chat.add_mascot(-1);
      chat << QString("How did it go since last time?");
      chat.add_mascot(60);
    } else{//first time you use the app
      chat << QString("Hello, it seems like it's your first time here! I'm "
                      "Rooxie, your well-being assistant!");
      chat.add_mascot(-1);
      chat << QString("You can put on paper your feelings using entries like the one on the right");
      chat.add_mascot(60);
      chat << QString(
          "Go on and modify the example entry! I can't wait to hear about your day!");
      chat.add_mascot(90);
    }
  }
}

void MainWindow::on_Test_entries_clicked() {
  vector_entries = sample_entries(55);
  displayed_entries = vector_entries;
  display_entries(true);
  update_graphs();
}

void MainWindow::add_new_activities_to_old_enties() {

  for (EntryPerso *entry : vector_entries) {
    for (Activity const &activity : vector_activities) {
      Activity *to_add = new Activity();
      to_add->set_name(activity.get_name());
      to_add->set_type(activity.get_type());
      std::vector<Activity *> entry_activities =
          entry->get_activities(); // crashes here if static cast used
      if (std::find_if(entry_activities.begin(), entry_activities.end(),
                       [to_add](Activity *a) -> bool {
                         return *a == *to_add;
                       }) == entry_activities.end()) {
        // does not contain activity
        Activity *to_add = new Activity();
        to_add->set_name(activity.get_name());
        to_add->set_type(activity.get_type());
        to_add->set_value(0.0);
        entry->add_activity(to_add);
      }
    }
  }
}
void MainWindow::remove_activities_from_old_entries() {
  /* remove an activity after it has been deleted */
  if(vector_entries.empty()){return;}
  std::vector<Activity*> reference_for_entries = vector_entries.at(0)->get_activities(); // the activities currently in entries
  std::vector<unsigned long long> to_remove; //positions of activities that should be removed
  // find activities that are present in entries but not in the vector of all activities
  for(long long activity = reference_for_entries.size() -1; activity >= 0; --activity){ // remove in reversed order

      bool not_found = true;
       for(Activity act: vector_activities) {
           if(act == *reference_for_entries.at(activity)){// found it
               not_found = false;
              break;
           }

       }
       if(not_found){to_remove.push_back(activity);}
 }

 for(EntryPerso* entry: vector_entries){
     std::vector<Activity*> entry_activities = entry->get_activities();
     for(unsigned long long act_remove : to_remove){
         entry_activities.erase(entry_activities.begin()+act_remove);
     }
     entry->set_activities(entry_activities);
 }


}

void MainWindow::refresh_activities() { // refresh the display of entryCards after activities modificatons
  for (EntryCard *c : displayed_cards) {
    if (c->isReadOnly()) {
      c->remove_non_existent_act();
    } else {
      c->update_fr_act_select();
    }
    c->set_correct_style();
  }
}

std::vector<QStringList> MainWindow::habit_repeated_5() { //fucntion that gets habits which is repeated every 5 times in a row
  std::vector<QStringList> current_habits = load_habits();
  std::vector<QStringList> tmp;
  for (unsigned long i = 0; i < current_habits.size(); i++) {
    if (current_habits[i][2].toInt() % 5 == 0) {
      tmp.push_back(current_habits[i]);
    }
  }
  return tmp;
}

std::vector<QStringList> MainWindow::habit_repeated_66() { //fucntion that gets habits which is repeated 33 imes in a row, which becomes automatic
  std::vector<QStringList> current_habits = load_habits();
  std::vector<QStringList> tmp;
  for (unsigned long i = 0; i < current_habits.size(); i++) {
    if (current_habits[i][2].toInt() == 66) {
      tmp.push_back(current_habits[i]);
    }
  }
  return tmp;
}



#include "cardclasses.h"
#include "Analysis/textanalysis.h"
#include "mainwindow.h"
#include "text_analysis_window.h"
#include <QCalendar>
#include <QDate>
#include <QDialog>
#include <QMessageBox>
#include <QThread>
#include <QWheelEvent>
#include <chrono>

bool EntryCard::can_be_modified = true;

Card::Card(int border_radius, int width, int height, QString color)
    : border_radius(border_radius), background_color(color) {
  this->resize(width, height);
  this->rect().setHeight(height);
  this->rect().setWidth(width);
  this->setStyleSheet("background-color: " + color +
                      "; border: 1px solid black; border-radius: " +
                      QString::number(border_radius) + "px;");
  vb_layout = new QVBoxLayout(this);
  vb_layout->setContentsMargins(0, 0, 0, 0);
  vb_layout->setSpacing(0);
  this->setLayout(vb_layout);
}

Card::~Card() {
  // IMPORTANT: with Qt, if a Qt object has a parent, it will be automatically
  // deleted when the parent is destroyed.
  // Therefore, deleting vb_layout will delete all elements in this layout!
  delete vb_layout;
}

int Card::get_width() const { return this->width(); }

int Card::get_height() const { return this->height(); }

int Card::get_border_radius() const { return border_radius; }

QString Card::get_background_color() const { return background_color; }

void Card::set_width(int width) {
  this->resize(width, this->height());
  this->rect().setWidth(width);
}

void Card::set_height(int height) {
  this->resize(this->width(), height);
  this->rect().setHeight(height);
}

void Card::set_border_radius(int border_radius) {
  this->border_radius = border_radius;
}

void Card::set_background_color(QString color) {
  this->background_color = color;
}

void Card::display(QLayout *layout) {
  this->setStyleSheet("background-color: " + background_color +
                      "; border: 1px solid black; border-radius:" +
                      QString::number(border_radius) + "px;");
  layout->addWidget(this);
}

QString generate_date_string(QDate date) {
  /* Using the date of the entry generates the QString of the form
   * 'Day - dd days ago
   * date of the entry '
   */

  int day_int = date.dayOfWeek();
  QString day_string;
  switch (day_int) {
  case 1:
    day_string = "Mon";
    break;
  case 2:
    day_string = "Tue";
    break;
  case 3:
    day_string = "Wed";
    break;
  case 4:
    day_string = "Thu";
    break;
  case 5:
    day_string = "Fri";
    break;
  case 6:
    day_string = "Sat";
    break;
  case 7:
    day_string = "Sun";
    break;
  default:
    day_string = QString::number(day_int);
    break;
  }

  QDate today = QDate::currentDate();
  int days_ago = date.daysTo(today);
  QString days_ago_string;
  if (days_ago == 0) {
    return day_string + " - today \n" + date.toString("MM-dd-yyyy");
  } else if (days_ago % 100 == 1) {
    days_ago_string = " day ago \n";
  } else {
    days_ago_string = " days ago \n";
  }

  return day_string + " - " + QString::number(days_ago) + days_ago_string +
         date.toString("MM-dd-yyyy");
}

void generate_rgb(int &red, int &green, double m) {
  /* Associate a color on a scale from red to green
   * according to the mood parameter
   */
  if (m <= 0.5) {
    red = 255;
    green = 240 * m / (1 - m);
  } else if (m <= 0.85) {
    green = 240;
    red = 255 * (-67 * pow((m - 0.5), 4) +
                 1); // This parabola gives the most suitable gradient of green
                     // and transitions smoothly with the values of green for a
                     // mood greater than 0.75
  } else {
    green = 240 - (240 - 128) * (m - 0.85) *
                      (10 / 3); // At this point we just make the green darker
    red = 0;
  }
}

std::vector<QListWidgetItem *> EntryCard::fr_act_options;

EntryCard::EntryCard(int border_radius, int width, int height, QString color,
                     Entry *entry, bool readOnly, MainWindow *main_window)
    : Card(border_radius, width, height, color), entry(entry),
      main_window(main_window) {
  this->readOnly = true;
  if (!readOnly and can_be_modified) {
    this->readOnly = readOnly;
    can_be_modified = false;
  }
  text_analysis = new text_analysis_window(this);
  textA = new TextAnalysis("");
  tathread = new TextAnalysisThread();
  entry_perso = nullptr;
  entry_recap = nullptr;
  // entry_perso display
  date_display = new QLabel();
  text_title_w = new QWidget();
  edit_and_return = new QGroupBox();
  title = new QLabel(QString::fromStdString(entry->get_title()), text_title_w);
  text_field =
      new QTextEdit(QString::fromStdString(entry->get_text()), text_title_w);
  edit_vb = new QVBoxLayout(edit_and_return);
  top_menu = new QHBoxLayout(); // deleted by call to delete on parent
  fr_act_display = new QListWidget();
  fr_act_select = new QListWidget();
  habits_display = new QComboBox();
  habits_view = new QListView();
  mood_display = new QLabel();
  mood_slider_w = new QWidget();
  mood_slider_instr = new QLabel(mood_slider_w);
  mood_slider = new QSlider(Qt::Horizontal, mood_slider_w);
  mood_slider_vb = new QVBoxLayout(mood_slider_w);
  text_title_vb = new QVBoxLayout(text_title_w);
  edit_text_w = new QStackedWidget();
  edit_text = new TextEditor();
  modify = new QPushButton("Modify this entry", text_title_w);
  analize = new QPushButton("Analize text", text_title_w);
  back_to_display = new QPushButton("Exit editing mode", edit_and_return);

  sleep_slider_w = new QWidget();
  sleep_slider_instr = new QLabel(sleep_slider_w);
  sleep_slider = new QSlider(Qt::Horizontal, sleep_slider_w);
  sleep_slider_vb = new QVBoxLayout(sleep_slider_w);

  // eating healthy
  eating_slider_w = new QWidget();
  eating_slider_instr = new QLabel(eating_slider_w);
  eating_slider = new QSlider(Qt::Horizontal, eating_slider_w);
  eating_slider_vb = new QVBoxLayout(eating_slider_w);
  // productivity
  productivity_slider_w = new QWidget();
  productivity_slider_instr = new QLabel(productivity_slider_w);
  productivity_slider = new QSlider(Qt::Horizontal, productivity_slider_w);
  productivity_slider_vb = new QVBoxLayout(productivity_slider_w);
  // socializing
  socializing_slider_w = new QWidget();
  socializing_slider_instr = new QLabel(socializing_slider_w);
  socializing_slider = new QSlider(Qt::Horizontal, socializing_slider_w);
  socializing_slider_vb = new QVBoxLayout(socializing_slider_w);
  // physical activity
  physical_activity_slider_w = new QWidget();
  physical_activity_slider_instr = new QLabel(physical_activity_slider_w);
  physical_activity_slider =
      new QSlider(Qt::Horizontal, physical_activity_slider_w);
  physical_activity_slider_vb = new QVBoxLayout(physical_activity_slider_w);

  // entry_recap display
  recap_title = new QLabel();
  recap_text = new QTextEdit();
  best_day_hb = new QHBoxLayout();
  worst_day_hb = new QHBoxLayout();
  best_day = new QLabel();
  worst_day = new QLabel();
  best_date = new QLabel();
  worst_date = new QLabel();
  best_mood = new QLabel();
  worst_mood = new QLabel();

  // find the type of the entry
  switch (entry->entry_type()) {
  case 1:
    entry_perso = static_cast<EntryPerso *>(entry);
    break;
  case 2:
    entry_recap = static_cast<EntryRecap *>(entry);
    break;
  }

  // display specific for entryPerso
  if (entry_perso != nullptr) {
    // set structure
    text_title_w->setParent(this);
    edit_and_return->setParent(this);
    // top_menu->setParent(this);
    fr_act_display->setParent(this);
    fr_act_select->setParent(this);
    mood_slider_w->setParent(this);

    // display date
    date_display->setMaximumHeight(47);
    date_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    date_display->setText(generate_date_string(entry->get_qdate()));
    date_display->setAlignment(Qt::AlignCenter);

    if ((entry->get_title()) != "") {
      // use the edit_text line edit to edit the title
      edit_text->set_title(QString::fromStdString(entry->get_title()));
    }

    if ((entry->get_text()) != "") {
      // use the edit_text line edit to edit the text
      edit_text->set_text(QString::fromStdString(entry->get_text()));
    }

    // modify
    modify->setMinimumWidth(40);
    connect(modify, &QPushButton::released, this, &EntryCard::handleModify);

    // analize
    analize->setMinimumWidth(40);
    connect(analize, &QPushButton::released, this, &EntryCard::handleAnalize);

    // back_to_display
    back_to_display->setMinimumWidth(40);
    connect(back_to_display, &QPushButton::released, this,
            &EntryCard::handleBack);

    // entry text and title
    // Set the title on the top of the window
    // set get_title() as the title of the window, but only the text

    // Set the background color of the title, and the font
    title->setMinimumHeight(40);
    title->setStyleSheet(
        "background-color: rgb(205, 0, 0); border-radius: 5px;");
    title->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    text_field->setMinimumWidth(this->get_width());
    text_field->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    text_field->setAlignment(Qt::AlignLeft);
    text_field->setReadOnly(true);

    // handle layout
    title->setWordWrap(true);
    text_title_vb->addWidget(title);
    // text_title_vb->addWidget(title_container);
    text_title_vb->addWidget(text_field);
    text_title_vb->addWidget(modify);
    text_title_vb->addWidget(analize);
    text_title_w->setLayout(text_title_vb);

    // Here we embed the text editor
    edit_text_w->setMinimumWidth(this->get_width());
    edit_text_w->setMinimumHeight(this->get_height());
    edit_text_w->setMaximumWidth((this->get_width()) + 530);
    edit_text_w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    edit_text->setMinimumWidth(this->get_width());
    edit_text->set_max_width((this->get_width()) + 510);
    edit_text->set_max_height((this->get_height()) - 50);
    edit_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    edit_text_w->addWidget(edit_text);
    edit_text_w->setCurrentWidget(edit_text);

    // edit_text layout
    edit_text_w->setParent(edit_and_return);
    edit_vb->addWidget(edit_text_w);

    QVBoxLayout *sliders_left = new QVBoxLayout();
    QVBoxLayout *sliders_right = new QVBoxLayout();
    QHBoxLayout *sliders = new QHBoxLayout();
    sliders_left->addWidget(sleep_slider_w);
    sliders_left->addWidget(eating_slider_w);
    sliders_right->addWidget(productivity_slider_w);
    sliders_right->addWidget(socializing_slider_w);
    sliders->addLayout(sliders_left);
    sliders->addLayout(sliders_right);
    edit_vb->addLayout(sliders);
    edit_vb->addWidget(physical_activity_slider_w);
    edit_vb->addWidget(back_to_display);
    edit_and_return->setLayout(edit_vb);

    // top menu
    top_menu->setAlignment(Qt::AlignTop);
    top_menu->setSpacing(0);
    date_display->setParent(this);
    top_menu->addWidget(date_display);

    // display activities and friends
    fr_act_display->setMaximumHeight(47);
    fr_act_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    for (long long unsigned act = 0;
         act < (entry_perso->get_activities()).size(); act++) {
      if (entry_perso->get_activities().at(act)->get_value() != 0) {
        QString name = QString::fromStdString(
            (entry_perso->get_activities().at(act))->get_name());
        switch ((entry_perso->get_activities().at(act))->get_type()) {
        case 1: // friends
          name += QString::fromUtf8(
              "\xF0\x9F\x91\xAD\xF0\x9F\x91\xAB\xF0\x9F\x91\xAC");
          break;
        case 2: // sports
          name +=
              QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD");
          break;
        case 3: // spiritual
          name +=
              QString::fromUtf8("\xE2\x9B\xAA\xF0\x9F\xA7\x98\xF0\x9F\x95\x8C");
          break;
        case 4: // work
          name += QString::fromUtf8(
              "\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5");
          break;
        case 5: // study
          name += QString::fromUtf8(
              "\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D");
          break;
        case 6: // art
          name += QString::fromUtf8(
              "\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8");
          break;
        default:
          break;
        }
        fr_act_display->addItem(name);
      }
    }

    // choose friends and activities
    fr_act_select->setMaximumHeight(47);
    fr_act_select->setSpacing(5);
    fr_act_select->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    for (long long unsigned act = 0;
         act < (entry_perso->get_activities()).size(); act++) {
      QString name = QString::fromStdString(
          (entry_perso->get_activities().at(act))->get_name());
      switch ((MainWindow::get_activities().at(act)).get_type()) {
      case 1: // friends
        name += QString::fromUtf8(
            "\xF0\x9F\x91\xAC\xF0\x9F\x91\xAB\xF0\x9F\x91\xAD");
        break;
      case 2: // sports
        name +=
            QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD");
        break;
      case 3: // spiritual
        name +=
            QString::fromUtf8("\xE2\x9B\xAA\xF0\x9F\xA7\x98\xF0\x9F\x95\x8C");
        break;
      case 4: // work
        name += QString::fromUtf8(
            "\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5");
        break;
      case 5: // study
        name += QString::fromUtf8(
            "\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D");
        break;
      case 6: // art
        name += QString::fromUtf8(
            "\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8");
        break;
      default:
        break;
      }

      QListWidgetItem *cb = new QListWidgetItem(name);
      cb->setCheckState(Qt::Unchecked);
      if (entry_perso->get_activities().at(act)->get_value() != 0) {
        cb->setCheckState(Qt::Checked);
      }
      fr_act_options.push_back(cb);
      fr_act_select->addItem(cb);
    }

    // display habits
    // habits_display->setParent(this);
    habits_display->setEditable(false);
    habits_display->setView(habits_view);
    habits_display->setLayoutDirection(Qt::RightToLeft);
    habits_display->setItemData(0, QBrush(Qt::black), Qt::ForegroundRole);
    // display mood
    habits_display->addItem(
        "Mood: " + QString::number(std::round(entry_perso->get_mood())) + "%");
    habits_display->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);
    // display sleep
    habits_display->addItem(
        "Sleep: " + QString::number(std::round(entry_perso->get_sleep())) +
        "%");
    habits_display->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
    // display eating
    habits_display->addItem(
        "Eating healthy: " +
        QString::number(std::round(entry_perso->get_eating_healthy())) + "%");
    habits_display->setItemData(2, Qt::AlignCenter, Qt::TextAlignmentRole);
    // display productivity
    habits_display->addItem(
        "Productivity: " +
        QString::number(std::round(entry_perso->get_productivity())) + "%");
    habits_display->setItemData(3, Qt::AlignCenter, Qt::TextAlignmentRole);
    // display communications
    habits_display->addItem(
        "Socializing: " +
        QString::number(std::round(entry_perso->get_socializing())) + "%");
    habits_display->setItemData(4, Qt::AlignCenter, Qt::TextAlignmentRole);
    // display screen
    habits_display->addItem(
        "Physical activity: " +
        QString::number(std::round(entry_perso->get_physical_activity())) +
        "%");
    habits_display->setItemData(5, Qt::AlignCenter, Qt::TextAlignmentRole);

    // mood_display->setMaximumSize(47);
    habits_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // mood_display->setAlignment(Qt::AlignCenter);

    // get mood
    mood_slider->setMinimum(0);
    mood_slider->setMaximum(100);
    mood_slider->setValue(int(this->entry_perso->get_mood()));
    mood_slider->setTickInterval(50);
    mood_slider->setTickPosition(QSlider::TicksBelow);
    mood_slider_instr->setText("Slide the bar to enter your mood");
    mood_slider->setMinimumHeight(18);
    mood_slider_w->setMaximumHeight(47);
    mood_slider_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mood_slider_vb->setSpacing(5);
    mood_slider_instr->setAlignment(Qt::AlignCenter);
    mood_slider_vb->addWidget(mood_slider_instr);
    mood_slider_vb->addWidget(mood_slider);
    mood_slider_w->setLayout(mood_slider_vb);

    // get sleep
    sleep_slider->setMinimum(0);
    sleep_slider->setMaximum(100);
    sleep_slider->setValue(int(this->entry_perso->get_sleep()));
    sleep_slider->setTickInterval(50);
    sleep_slider->setTickPosition(QSlider::TicksBelow);
    sleep_slider_instr->setText("Slide the bar to enter how well you slept");
    sleep_slider->setMinimumHeight(18);
    sleep_slider_w->setMaximumHeight(47);
    sleep_slider_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sleep_slider_vb->setSpacing(5);
    sleep_slider_instr->setAlignment(Qt::AlignCenter);
    sleep_slider_vb->addWidget(sleep_slider_instr);
    sleep_slider_vb->addWidget(sleep_slider);
    sleep_slider_w->setLayout(sleep_slider_vb);

    // get eating
    eating_slider->setMinimum(0);
    eating_slider->setMaximum(100);
    eating_slider->setValue(int(this->entry_perso->get_eating_healthy()));
    eating_slider->setTickInterval(50);
    eating_slider->setTickPosition(QSlider::TicksBelow);
    eating_slider_instr->setText(
        "Slide the bar to enter how healthily you ate");
    eating_slider->setMinimumHeight(18);
    eating_slider_w->setMaximumHeight(47);
    eating_slider_w->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    eating_slider_vb->setSpacing(5);
    eating_slider_instr->setAlignment(Qt::AlignCenter);
    eating_slider_vb->addWidget(eating_slider_instr);
    eating_slider_vb->addWidget(eating_slider);
    eating_slider_w->setLayout(eating_slider_vb);

    // get productivity
    productivity_slider->setMinimum(0);
    productivity_slider->setMaximum(100);
    productivity_slider->setValue(int(this->entry_perso->get_productivity()));
    productivity_slider->setTickInterval(50);
    productivity_slider->setTickPosition(QSlider::TicksBelow);
    productivity_slider_instr->setText(
        "Slide the bar to enter how productive you were");
    productivity_slider->setMinimumHeight(18);
    productivity_slider_w->setMaximumHeight(47);
    productivity_slider_w->setSizePolicy(QSizePolicy::Minimum,
                                         QSizePolicy::Minimum);
    productivity_slider_vb->setSpacing(5);
    productivity_slider_instr->setAlignment(Qt::AlignCenter);
    productivity_slider_vb->addWidget(productivity_slider_instr);
    productivity_slider_vb->addWidget(productivity_slider);
    productivity_slider_w->setLayout(productivity_slider_vb);

    // get socializing
    socializing_slider->setMinimum(0);
    socializing_slider->setMaximum(100);
    socializing_slider->setValue(int(this->entry_perso->get_socializing()));
    socializing_slider->setTickInterval(50);
    socializing_slider->setTickPosition(QSlider::TicksBelow);
    socializing_slider_instr->setText(
        "Slide the bar to enter how social you were");

    socializing_slider->setMinimumHeight(18);
    socializing_slider_w->setMaximumHeight(47);
    socializing_slider_w->setSizePolicy(QSizePolicy::Minimum,
                                        QSizePolicy::Minimum);
    socializing_slider_vb->setSpacing(5);
    socializing_slider_instr->setAlignment(Qt::AlignCenter);
    socializing_slider_vb->addWidget(socializing_slider_instr);
    socializing_slider_vb->addWidget(socializing_slider);
    socializing_slider_w->setLayout(socializing_slider_vb);

    // get physical_activity
    physical_activity_slider->setMinimum(0);
    physical_activity_slider->setMaximum(100);
    physical_activity_slider->setValue(
        int(this->entry_perso->get_physical_activity()));
    physical_activity_slider->setTickInterval(50);
    physical_activity_slider->setTickPosition(QSlider::TicksBelow);

    physical_activity_slider_instr->setText(
        "Slide the bar to enter your physical activity");

    physical_activity_slider->setMinimumHeight(18);
    physical_activity_slider_w->setMaximumHeight(47);
    physical_activity_slider_w->setSizePolicy(QSizePolicy::Minimum,
                                              QSizePolicy::Minimum);
    physical_activity_slider_vb->setSpacing(5);
    physical_activity_slider_instr->setAlignment(Qt::AlignCenter);
    physical_activity_slider_vb->addWidget(physical_activity_slider_instr);
    physical_activity_slider_vb->addWidget(physical_activity_slider);
    physical_activity_slider_w->setLayout(physical_activity_slider_vb);

    // size adjustments

    date_display->setMinimumWidth(this->get_width() / 3);
    fr_act_display->setMinimumWidth(this->get_width() / 3);
    fr_act_select->setMinimumWidth(this->get_width() / 3);
    habits_display->setMinimumWidth(this->get_width() / 3);
    mood_slider->setMinimumWidth(this->get_width() / 3);

    // top menu
    fr_act_display->setParent(this);
    fr_act_select->setParent(this);
    top_menu->addWidget(fr_act_display);
    top_menu->addWidget(fr_act_select);
    // habits
    // mood_display->setParent(this);
    habits_display->setParent(this);
    top_menu->addWidget(habits_display);
    top_menu->addWidget(mood_slider_w);
    if (isReadOnly()) {
      habits_display->setVisible(true);
      mood_slider_w->setVisible(false);
    } else {
      mood_slider_w->setVisible(true);
      habits_display->setVisible(false);
    }

    set_correct_style();

    // add to the layout
    vb_layout->addItem(top_menu);
    vb_layout->addWidget(text_title_w);
    vb_layout->addWidget(edit_and_return);
    if (isReadOnly()) {
      text_title_w->setVisible(true); // for readOnly
      edit_and_return->setVisible(false);
    } else {
      edit_and_return->setVisible(true); // for editor
      text_title_w->setVisible(false);
    }
    this->setLayout(vb_layout);

  }

  else if (entry_recap != nullptr) {
    this->setContentsMargins(0, 0, 0, 0);
    QDate best_day_date = entry_recap->get_best_day_date();
    QDate worst_day_date = entry_recap->get_worst_day_date();
    double best_day_mood = entry_recap->get_best_day_mood();
    double worst_day_mood = entry_recap->get_worst_day_mood();
    // recap_layout->setParent(this);

    switch (entry_recap->get_type()) {
    case 0:
      recap_title->setText("Weekly recap");
      break;
    case 1:
      recap_title->setText("Monthly recap");
      break;
    case 2:
      recap_title->setText("Yearly recap");
      break;
    }

    // display date
    date_display->setMaximumHeight(47);
    date_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    date_display->setText(generate_date_string(entry->get_qdate()));
    date_display->setAlignment(Qt::AlignCenter);

    // recap title
    recap_title->setParent(this);
    recap_title->setMaximumHeight(47);
    recap_title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    recap_title->setAlignment(Qt::AlignCenter);

    // display mood
    mood_display->setText(
        "Mood: " +
        QString::number(std::round(entry_recap->get_average_mood())) + "%");
    mood_display->setMaximumHeight(47);
    mood_display->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mood_display->setAlignment(Qt::AlignCenter);

    // recap_text
    recap_text->setParent(this);
    recap_text->setText(QString::fromStdString(entry_recap->get_text()));
    recap_text->setReadOnly(true);

    // best day
    best_day->setParent(this);
    best_day->setText("Best Day:");
    best_date->setParent(this);
    best_date->setText(generate_date_string(entry_recap->get_best_day_date()));
    best_date->setAlignment(Qt::AlignCenter);
    best_mood->setParent(this);
    best_mood->setText(
        "Highest mood: " +
        QString::number(std::round(entry_recap->get_best_day_mood())) + "%");
    best_day_hb->addWidget(best_day);
    best_day_hb->addWidget(best_date);
    best_day_hb->addWidget(best_mood);

    // worst day
    worst_day->setParent(this);
    worst_day->setText("Worst Day:");
    worst_date->setParent(this);
    worst_date->setText(
        generate_date_string(entry_recap->get_worst_day_date()));
    worst_date->setAlignment(Qt::AlignCenter);
    worst_mood->setParent(this);
    worst_mood->setText(
        "Lowest mood: " +
        QString::number(std::round(entry_recap->get_worst_day_mood())) + "%");
    worst_day_hb->addWidget(worst_day);
    worst_day_hb->addWidget(worst_date);
    worst_day_hb->addWidget(worst_mood);

    // size adjustments
    date_display->setMinimumWidth(this->get_width() / 3);
    recap_title->setMinimumWidth(this->get_width() / 3);
    mood_display->setMinimumWidth(this->get_width() / 3);

    // top menu
    top_menu->setAlignment(Qt::AlignTop);
    top_menu->setSpacing(0);
    date_display->setParent(this);
    mood_display->setParent(this);
    top_menu->addWidget(date_display);
    top_menu->addWidget(recap_title);
    top_menu->addWidget(mood_display);

    // add to the layout
    vb_layout->addItem(top_menu);
    vb_layout->addWidget(recap_text);
    vb_layout->addItem(best_day_hb);
    vb_layout->addItem(worst_day_hb);
    this->setLayout(vb_layout);
    this->set_entryRecap_style();
  }
}

EntryCard::~EntryCard() {
  // ~Card is called, deleting vb_layout. As it is a Qt Layout, all its children
  // will be deleted? This includes:
  /*
  text_title_w
  edit_and_return
  top_menu
  recap_text
  best_day_hb
  worst_day_hb
  */

  if (!isReadOnly()) {      // this card was in modify mode
    can_be_modified = true; // now the other cards can be modified
  }
  delete text_analysis;
  delete textA;
  delete tathread;
}

void EntryCard::handleModify() {
  if (can_be_modified) {
    this->change();
    can_be_modified = false;
  } else {
    QMessageBox alert;
    alert.setWindowTitle("Error");
    alert.setText("One of the entries is already being modified, finish "
                  "editing to modify this entry.");
    alert.setStandardButtons(QMessageBox::Close);
    alert.setDefaultButton(QMessageBox::Close);
    alert.exec();
  }
}

void EntryCard::doneThreads() {
  text_analysis_window *text_analysis_w =
      dynamic_cast<text_analysis_window *>(text_analysis);
  text_analysis_w->set_mood(textA->get_text_mood() * 100);
  text_analysis_w->set_message();
}

void EntryCard::handleAnalize() {
  text_analysis_window *text_analysis_w =
      dynamic_cast<text_analysis_window *>(text_analysis);
  // WindowThread wt = WindowThread(&text_analysis);
  textA = new TextAnalysis(
      (edit_text->get_title() + " " + edit_text->get_plain_text())
          .toStdString());
  tathread = new TextAnalysisThread(textA);
  // wt.start();
  connect(tathread, SIGNAL(finished()), this, SLOT(doneThreads()));
  tathread->start();
  text_analysis_w->start();
  // connect(tathread, &TextAnalysisThread::finished, this,
  // &EntryCard::doneThreads);
  /*tathread->wait();
  text_analysis.set_mood(textA.get_text_mood());
  text_analysis.set_message();
  text_analysis.show();*/
}

void EntryCard::handleBack() {
  QMessageBox alert;
  alert.setText("Do you want to save the changes to your entry?");
  alert.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  alert.setDefaultButton(QMessageBox::Save);
  int choice = alert.exec();
  std::string retrieve_text = (edit_text->get_text()).toStdString();
  std::string new_title = (edit_text->get_title()).toStdString();
  std::string new_text = retrieve_text.substr(retrieve_text.find("\n") + 1);
  switch (choice) {
  case QMessageBox::Save:
    entry->set_title(new_title);
    entry->set_text(new_text);
    this->update();
    this->change();
    break;
  case QMessageBox::Discard:
    this->remove_non_existent_act();
    this->change();
    break;
  case QMessageBox::Cancel:
      break;
  }


  can_be_modified = true;
  // check if a weekly/monthly/yearly recap has to be created
  main_window->generate_recap();
}

void EntryCard::set_correct_style() {
  if (readOnly && fr_act_display->count() != 0) {
    set_entryPerso_style(3);
  } else if (!readOnly && !fr_act_options.empty()) {
    set_entryPerso_style(3);
  } else {
    set_entryPerso_style(2);
  }
}

void EntryCard::change() {
  readOnly = !readOnly;
  if (isReadOnly()) {
    text_title_w->setVisible(true);
    edit_and_return->setVisible(false); // for readOnly text
    if (entry_perso != nullptr) {
      mood_slider_w->setVisible(false);
      habits_display->setVisible(true);
    }
  } else {
    text_title_w->setVisible(false);
    edit_and_return->setVisible(true); // for editor
    if (entry_perso != nullptr) {
      update_fr_act_select();
      habits_display->setVisible(false);
      mood_slider_w->setVisible(true);
    }
  }
  set_correct_style();
}

void EntryCard::update() {
  // update values after user modifications
  date_display->setText(generate_date_string(entry->get_qdate()));
  title->setText(QString::fromStdString(entry->get_title()));
  text_field->setText(QString::fromStdString(entry->get_text()));
  if ((entry->get_title()) != "") {
    edit_text->set_title(QString::fromStdString(entry->get_title()));
  }
  edit_text->set_text(QString::fromStdString(entry->get_text()));
  if (entry_perso != nullptr) {
    this->entry_perso->set_mood(this->mood_slider->value());
    this->entry_perso->set_sleep(this->sleep_slider->value());
    this->entry_perso->set_eating_healthy(this->eating_slider->value());
    this->entry_perso->set_productivity(this->productivity_slider->value());
    this->entry_perso->set_socializing(this->socializing_slider->value());
    this->entry_perso->set_physical_activity(
        this->physical_activity_slider->value());

    habits_display->setItemText(
        0,
        "Mood: " + QString::number(std::round(entry_perso->get_mood())) + "%");
    habits_display->setItemText(
        1, "Sleep: " + QString::number(std::round(entry_perso->get_sleep())) +
               "%");
    habits_display->setItemText(
        2, "Eathing healthy: " +
               QString::number(std::round(entry_perso->get_eating_healthy())) +
               "%");
    habits_display->setItemText(
        3, "Productivity: " +
               QString::number(std::round(entry_perso->get_productivity())) +
               "%");
    habits_display->setItemText(
        4, "Socializing: " +
               QString::number(std::round(entry_perso->get_socializing())) +
               "%");
    habits_display->setItemText(
        5,
        "Physical activity: " +
            QString::number(std::round(entry_perso->get_physical_activity())) +
            "%");

    mood_slider->setValue(int(this->entry_perso->get_mood()));
    sleep_slider->setValue(int(this->entry_perso->get_sleep()));
    eating_slider->setValue(int(this->entry_perso->get_eating_healthy()));
    productivity_slider->setValue(int(this->entry_perso->get_productivity()));
    socializing_slider->setValue(int(this->entry_perso->get_socializing()));
    physical_activity_slider->setValue(
        int(this->entry_perso->get_physical_activity()));

    // friends and activities
    update_fr_act();
  }
  // update dynamic graph
  main_window->update_graphs();
  // react to the entry - Important to call it *before* generate_recap
  if (entry->get_qdate() == QDate::currentDate()) {
    main_window->react_to_last_entry();
  }
  // update style
  set_correct_style();
}

void EntryCard::update_fr_act_select() {
  // update checklist before switching into modify mode
  fr_act_select->clear();
  fr_act_options.clear();

  for (long long unsigned act = 0; act < entry_perso->get_activities().size();
       act++) {
    QString name = QString::fromStdString(
        (entry_perso->get_activities().at(act))->get_name());
    switch (entry_perso->get_activities().at(act)->get_type()) {
    case 1: // friends
      name +=
          QString::fromUtf8("\xF0\x9F\x91\xAD\xF0\x9F\x91\xAB\xF0\x9F\x91\xAC");
      break;
    case 2: // sports
      name += QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD");
      break;
    case 3: // spiritual
      name += QString::fromUtf8("\xE2\x9B\xAA\xF0\x9F\xA7\x98\xF0\x9F\x95\x8C");
      break;
    case 4: // work
      name +=
          QString::fromUtf8("\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5");
      break;
    case 5: // study
      name +=
          QString::fromUtf8("\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D");
      break;
    case 6: // art
      name +=
          QString::fromUtf8("\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8");
      break;
    default:
      break;
    }

    QListWidgetItem *cb = new QListWidgetItem(name);
    cb->setCheckState(Qt::Unchecked);
    if (entry_perso->get_activities().at(act)->get_value() != 0) {
      cb->setCheckState(Qt::Checked);
    }
    fr_act_options.push_back(cb);
    fr_act_select->addItem(cb);
  }
}

void EntryCard::remove_non_existent_act() {
  // when activities are deleted, the display shoud be adjusted accordingly
  // + auxiliary function when switching from modify to readOnly
  fr_act_display->clear();
  unsigned long long num_activities = entry_perso->get_activities().size();
  for (unsigned long long act = 0; act < num_activities; act++) {
    if (entry_perso->get_activities().at(act)->get_value() != 0) {
      QString name = QString::fromStdString(
          (entry_perso->get_activities()).at(act)->get_name());
      switch ((entry_perso->get_activities().at(act))->get_type()) {
      case 1: // friends
        name += QString::fromUtf8(
            "\xF0\x9F\x91\xAD\xF0\x9F\x91\xAB\xF0\x9F\x91\xAC");
        break;
      case 2: // sports
        name +=
            QString::fromUtf8("\xF0\x9F\x8F\x80\xF0\x9F\x8E\xBE\xE2\x9A\xBD");
        break;
      case 3: // spiritual
        name +=
            QString::fromUtf8("\xE2\x9B\xAA\xF0\x9F\xA7\x98\xF0\x9F\x95\x8C");
        break;
      case 4: // work
        name += QString::fromUtf8(
            "\xF0\x9F\x92\xBC\xF0\x9F\x92\xBB\xF0\x9F\x92\xB5");
        break;
      case 5: // study
        name += QString::fromUtf8(
            "\xF0\x9F\x93\x96\xF0\x9F\x93\x9A\xF0\x9F\x93\x9D");
        break;
      case 6: // art
        name += QString::fromUtf8(
            "\xF0\x9F\x8E\xBC\xF0\x9F\x8E\xBB\xF0\x9F\x8E\xA8");
        break;
      default:
        break;
      }
      fr_act_display->addItem(name);
    }
  }
}

void EntryCard::update_fr_act() {
  // update the display and values before going back to readOnly mode
  unsigned long long num_activities = (entry_perso->get_activities()).size();
  for (unsigned long long i = 0; i < num_activities; i++) {
    QListWidgetItem *option = fr_act_options.at(i);
    if (option->checkState() == Qt::Checked) {
      entry_perso->get_activities().at(i)->set_value(1);
    } else {
      entry_perso->get_activities().at(i)->set_value(0);
    }
  }

  fr_act_select->clear();
  fr_act_options.clear();

  this->remove_non_existent_act();
}

void EntryCard::set_habits_colors() {
  int red, green;
  generate_rgb(red, green, entry_perso->get_mood() / 100);
  habits_display->setItemData(0, QBrush(QColor(red, green, 0)),
                              Qt::ForegroundRole);
  generate_rgb(red, green, entry_perso->get_sleep() / 100);
  habits_display->setItemData(1, QBrush(QColor(red, green, 0)),
                              Qt::ForegroundRole);
  generate_rgb(red, green, entry_perso->get_eating_healthy() / 100);
  habits_display->setItemData(2, QBrush(QColor(red, green, 0)),
                              Qt::ForegroundRole);
  generate_rgb(red, green, entry_perso->get_productivity() / 100);
  habits_display->setItemData(3, QBrush(QColor(red, green, 0)),
                              Qt::ForegroundRole);
  generate_rgb(red, green, entry_perso->get_socializing() / 100);
  habits_display->setItemData(4, QBrush(QColor(red, green, 0)),
                              Qt::ForegroundRole);
  generate_rgb(red, green, entry_perso->get_physical_activity() / 100);
  habits_display->setItemData(5, QBrush(QColor(red, green, 0)),
                              Qt::ForegroundRole);
}

void EntryCard::set_entryPerso_style(int top_menu_num_items) {
  if (top_menu_num_items == 3 and readOnly) {
    fr_act_display->setVisible(true);
    fr_act_select->setVisible(false);
  } else if (top_menu_num_items == 3) {
    fr_act_display->setVisible(false);
    fr_act_select->setVisible(true);
  } else {
    fr_act_display->setVisible(false);
    fr_act_select->setVisible(false);
  }

  this->setStyleSheet("background-color: " + get_background_color() +
                      "; border: 1px solid black; border-radius: " +
                      QString::number(get_border_radius()) + "px;");
  date_display->setStyleSheet(
      "font-weight: bold; border-style: none; border-radius: 0px; "
      "border-top-left-radius: " +
      QString::number(this->get_border_radius()) +
      "px; border-right: 1px solid black; border-bottom: 1px solid black;");
  text_title_w->setStyleSheet(
      "border-style: none; border-radius: 0px; border-bottom-left-radius: " +
      QString::number(this->get_border_radius()) +
      "px; border-bottom-right-radius: " +
      QString::number(this->get_border_radius()) + "px;");
  title->setStyleSheet("font: 24px; font-weight: bold; border-style: none;");
  edit_text_w->setStyleSheet("border-style: none;");
  edit_and_return->setStyleSheet("border-style: none;");
  modify->setStyleSheet(
      "QPushButton{color: white; background-color: black; font-weight: bold; "
      "font: 15px; border: 2px solid black; border-radius: 5px;} "
      "QPushButton:hover{background-color:white; color:black;}");
  analize->setStyleSheet(
      "QPushButton{color: white; background-color: black; font-weight: bold; "
      "font: 15px; border: 2px solid black; border-radius: 5px;} "
      "QPushButton:hover{background-color:white; color:black;}");
  back_to_display->setStyleSheet(
      "QPushButton{color: white; background-color: black; font-weight: bold; "
      "font: 15px; border: 2px solid black; border-radius: 5px;} "
      "QPushButton:hover{background-color:white; color:black;}");
  fr_act_display->setStyleSheet(
      "font-weight: bold; border-style: none; border-radius: 0px; "
      "border-right: 1px solid black; border-bottom: 1px solid black;");
  fr_act_select->setStyleSheet(
      "font-weight: bold; border-style: none; border-radius: 0px; "
      "border-right: 1px solid black; border-bottom: 1px solid black;");
  int red, green;
  switch (habits_display->currentIndex()) {
  case 0:
    generate_rgb(red, green, entry_perso->get_mood() / 100);
    habits_display->setStyleSheet(
        "font-weight: bold; border-style: none; border-bottom: 1px solid "
        "black; "
        "border-radius: 0px; border-top-right-radius:" +
        QString::number(this->get_border_radius()) + "px; color: rgb(" +
        QString::number(red) + ", " + QString::number(green) + ", 0);");
    break;
  case 1:
    generate_rgb(red, green, entry_perso->get_sleep() / 100);
    habits_display->setStyleSheet(
        "font-weight: bold; border-style: none; border-bottom: 1px solid "
        "black; "
        "border-radius: 0px; border-top-right-radius:" +
        QString::number(this->get_border_radius()) + "px; color: rgb(" +
        QString::number(red) + ", " + QString::number(green) + ", 0);");
    break;
  case 2:
    generate_rgb(red, green, entry_perso->get_eating_healthy() / 100);
    habits_display->setStyleSheet(
        "font-weight: bold; border-style: none; border-bottom: 1px solid "
        "black; "
        "border-radius: 0px; border-top-right-radius:" +
        QString::number(this->get_border_radius()) + "px; color: rgb(" +
        QString::number(red) + ", " + QString::number(green) + ", 0);");
    break;
  case 3:
    generate_rgb(red, green, entry_perso->get_productivity() / 100);
    habits_display->setStyleSheet(
        "font-weight: bold; border-style: none; border-bottom: 1px solid "
        "black; "
        "border-radius: 0px; border-top-right-radius:" +
        QString::number(this->get_border_radius()) + "px; color: rgb(" +
        QString::number(red) + ", " + QString::number(green) + ", 0);");
    break;
  case 4:
    generate_rgb(red, green, entry_perso->get_socializing() / 100);
    habits_display->setStyleSheet(
        "font-weight: bold; border-style: none; border-bottom: 1px solid "
        "black; "
        "border-radius: 0px; border-top-right-radius:" +
        QString::number(this->get_border_radius()) + "px; color: rgb(" +
        QString::number(red) + ", " + QString::number(green) + ", 0);");
    break;
  case 5:
    generate_rgb(red, green, entry_perso->get_physical_activity() / 100);
    habits_display->setStyleSheet(
        "font-weight: bold; border-style: none; border-bottom: 1px solid "
        "black; "
        "border-radius: 0px; border-top-right-radius:" +
        QString::number(this->get_border_radius()) + "px; color: rgb(" +
        QString::number(red) + ", " + QString::number(green) + ", 0);");
    break;
  default:
    break;
  }
  set_habits_colors();
  connect(
      habits_display, QOverload<int>::of(&QComboBox::currentIndexChanged),
      [=](int index) {
        switch (index) {

          int red, green;
        case 0:
          generate_rgb(red, green, entry_perso->get_mood() / 100);
          habits_display->setStyleSheet(
              "font-weight: bold; border-style: none; border-bottom: 1px solid "
              "black; "
              "border-radius: 0px; border-top-right-radius:" +
              QString::number(this->get_border_radius()) + "px; color: rgb(" +
              QString::number(red) + ", " + QString::number(green) + ", 0);");
          set_habits_colors();
          break;
        case 1:
          generate_rgb(red, green, entry_perso->get_sleep() / 100);
          habits_display->setStyleSheet(
              "font-weight: bold; border-style: none; border-bottom: 1px solid "
              "black; "
              "border-radius: 0px; border-top-right-radius:" +
              QString::number(this->get_border_radius()) + "px; color: rgb(" +
              QString::number(red) + ", " + QString::number(green) + ", 0);");
          set_habits_colors();
          break;
        case 2:
          generate_rgb(red, green, entry_perso->get_eating_healthy() / 100);
          habits_display->setStyleSheet(
              "font-weight: bold; border-style: none; border-bottom: 1px solid "
              "black; "
              "border-radius: 0px; border-top-right-radius:" +
              QString::number(this->get_border_radius()) + "px; color: rgb(" +
              QString::number(red) + ", " + QString::number(green) + ", 0);");
          set_habits_colors();
          break;
        case 3:
          generate_rgb(red, green, entry_perso->get_productivity() / 100);
          habits_display->setStyleSheet(
              "font-weight: bold; border-style: none; border-bottom: 1px solid "
              "black; "
              "border-radius: 0px; border-top-right-radius:" +
              QString::number(this->get_border_radius()) + "px; color: rgb(" +
              QString::number(red) + ", " + QString::number(green) + ", 0);");
          set_habits_colors();
          break;
        case 4:
          generate_rgb(red, green, entry_perso->get_socializing() / 100);
          habits_display->setStyleSheet(
              "font-weight: bold; border-style: none; border-bottom: 1px solid "
              "black; "
              "border-radius: 0px; border-top-right-radius:" +
              QString::number(this->get_border_radius()) + "px; color: rgb(" +
              QString::number(red) + ", " + QString::number(green) + ", 0);");
          set_habits_colors();
          break;
        case 5:
          generate_rgb(red, green, entry_perso->get_physical_activity() / 100);
          habits_display->setStyleSheet(
              "font-weight: bold; border-style: none; border-bottom: 1px solid "
              "black; "
              "border-radius: 0px; border-top-right-radius:" +
              QString::number(this->get_border_radius()) + "px; color: rgb(" +
              QString::number(red) + ", " + QString::number(green) + ", 0);");
          set_habits_colors();
          break;
        default:
          break;
        }
      });
  mood_slider_w->setStyleSheet(
      "border-style: none; border-bottom: 1px solid black; border-radius: 0px; "
      "border-top-right-radius: " +
      QString::number(get_border_radius()) + "px;");
  mood_slider->setStyleSheet(
      "QSlider{border-style: none;} QSlider::groove:horizontal{border-style: "
      "none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 "
      "rgb(255, 0, 0), stop: 0.5 rgb(255, 255, 0), stop: 1 rgb(0, 255, 0)); "
      "height: 10px; border-radius: "
      "5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px "
      "solid grey;height: 10px;border-radius: 5px;} "
      "QSlider::add-page:horizontal {background: white; border: 1px solid "
      "grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal "
      "{background: grey; border: 1px solid dark-grey; width: 16px;margin-top: "
      "-3px;margin-bottom: -3px;border-radius: 5px;} "
      "QSlider::handle:horizontal:hover {background: dark-grey; border: 1px "
      "solid black; border-radius: 5px;}");
  mood_slider_instr->setStyleSheet("font-weight: bold; border-style: none;");
  sleep_slider_w->setStyleSheet(
      "border-style: none; border-bottom: 1px solid black; border-radius: 0px; "
      "border-top-right-radius: " +
      QString::number(get_border_radius()) + "px;");
  sleep_slider->setStyleSheet(
      "QSlider{border-style: none;} QSlider::groove:horizontal{border-style: "
      "none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 "
      "rgb(200,200, 200), stop: 0.5 rgb(100, 100, 100), stop: 1 rgb(0, 0, 0));"
      "height: 10px; border-radius: "
      "5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px "
      "solid grey;height: 10px;border-radius: 5px;} "
      "QSlider::add-page:horizontal {background: white; border: 1px solid "
      "grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal "
      "{background: grey; border: 1px solid dark-grey; width: 16px;margin-top: "
      "-3px;margin-bottom: -3px;border-radius: 5px;} "
      "QSlider::handle:horizontal:hover {background: dark-grey; border: 1px "
      "solid black; border-radius: 5px;}");
  sleep_slider_instr->setStyleSheet("font-weight: bold; border-style: none;");
  eating_slider_w->setStyleSheet(
      "border-style: none; border-bottom: 1px solid black; border-radius: 0px; "
      "border-top-right-radius: " +
      QString::number(get_border_radius()) + "px;");
  eating_slider->setStyleSheet(
      "QSlider{border-style: none;} QSlider::groove:horizontal{border-style: "
      "none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 "
      "rgb(200,200, 200), stop: 0.5 rgb(100, 100, 100), stop: 1 rgb(0, 0, 0)); "
      "height: 10px; border-radius: "
      "5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px "
      "solid grey;height: 10px;border-radius: 5px;} "
      "QSlider::add-page:horizontal {background: white; border: 1px solid "
      "grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal "
      "{background: grey; border: 1px solid dark-grey; width: 16px;margin-top: "
      "-3px;margin-bottom: -3px;border-radius: 5px;} "
      "QSlider::handle:horizontal:hover {background: dark-grey; border: 1px "
      "solid black; border-radius: 5px;}");
  eating_slider_instr->setStyleSheet("font-weight: bold; border-style: none;");
  productivity_slider_w->setStyleSheet(
      "border-style: none; border-bottom: 1px solid black; border-radius: 0px; "
      "border-top-right-radius: " +
      QString::number(get_border_radius()) + "px;");
  productivity_slider->setStyleSheet(
      "QSlider{border-style: none;} QSlider::groove:horizontal{border-style: "
      "none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 "
      "rgb(200,200, 200), stop: 0.5 rgb(100, 100, 100), stop: 1 rgb(0, 0, 0));"
      "height: 10px; border-radius: "
      "5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px "
      "solid grey;height: 10px;border-radius: 5px;} "
      "QSlider::add-page:horizontal {background: white; border: 1px solid "
      "grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal "
      "{background: grey; border: 1px solid dark-grey; width: 16px;margin-top: "
      "-3px;margin-bottom: -3px;border-radius: 5px;} "
      "QSlider::handle:horizontal:hover {background: dark-grey; border: 1px "
      "solid black; border-radius: 5px;}");
  productivity_slider_instr->setStyleSheet("font-weight: bold; border-style: "
                                           "none;");
  socializing_slider_w->setStyleSheet(
      "border-style: none; border-bottom: 1px solid black; border-radius: 0px; "
      "border-top-right-radius: " +
      QString::number(get_border_radius()) + "px;");
  socializing_slider->setStyleSheet(
      "QSlider{border-style: none;} QSlider::groove:horizontal{border-style: "
      "none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 "
      "rgb(200,200, 200), stop: 0.5 rgb(100, 100, 100), stop: 1 rgb(0, 0, 0));"
      "height: 10px; border-radius: "
      "5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px "
      "solid grey;height: 10px;border-radius: 5px;} "
      "QSlider::add-page:horizontal {background: white; border: 1px solid "
      "grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal "
      "{background: grey; border: 1px solid dark-grey; width: 16px;margin-top: "
      "-3px;margin-bottom: -3px;border-radius: 5px;} "
      "QSlider::handle:horizontal:hover {background: dark-grey; border: 1px "
      "solid black; border-radius: 5px;}");
  socializing_slider_instr->setStyleSheet("font-weight: bold; border-style: "
                                          "none;");
  physical_activity_slider_w->setStyleSheet(
      "border-style: none; border-bottom: 1px solid black; border-radius: 0px; "
      "border-top-right-radius: " +
      QString::number(get_border_radius()) + "px;");
  physical_activity_slider->setStyleSheet(
      "QSlider{border-style: none;} QSlider::groove:horizontal{border-style: "
      "none; background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 "
      "rgb(200,200, 200), stop: 0.5 rgb(100, 100, 100), stop: 1 rgb(0, 0, 0));"
      "height: 10px; border-radius: "
      "5px;}QSlider::sub-page:horizontal{background: transparent;border: 1px "
      "solid grey;height: 10px;border-radius: 5px;} "
      "QSlider::add-page:horizontal {background: white; border: 1px solid "
      "grey;height: 10px;border-radius: 5px;} QSlider::handle:horizontal "
      "{background: grey; border: 1px solid dark-grey; width: 16px;margin-top: "
      "-3px;margin-bottom: -3px;border-radius: 5px;} "
      "QSlider::handle:horizontal:hover {background: dark-grey; border: 1px "
      "solid black; border-radius: 5px;}");
  physical_activity_slider_instr->setStyleSheet(
      "font-weight: bold; border-style: "
      "none;");
}

void EntryCard::set_entryRecap_style() {
  this->setStyleSheet("background-color: " + get_background_color() +
                      "; border: 1px solid black; border-radius: " +
                      QString::number(get_border_radius()) + "px;");
  date_display->setStyleSheet(
      "font-weight: bold;border-style: none; border-radius: 0px; "
      "border-top-left-radius: " +
      QString::number(this->get_border_radius()) +
      "px; border-bottom: 1px solid black; border-left: 1px solid black; "
      "border-top: 1px solid black;");

  recap_title->setStyleSheet(
      "font-weight: bold; font-size: 15px; border-style: none; border-radius: "
      "0px; "
      "border-bottom: 1px solid black; border-left: 1px solid black;"
      "color: white; background-color: black;");

  int red, green;
  generate_rgb(red, green, entry_recap->get_average_mood() / 100);
  mood_display->setStyleSheet(
      "font-weight: bold; color: rgb(" + QString::number(red) + ", " +
      QString::number(green) +
      ", 0); border-style: none; border-bottom: 1px solid black; "
      "border-radius: 0px; border-top-right-radius:" +
      QString::number(this->get_border_radius()) +
      "px; border-top: 1px solid black; border-right: 1px solid black;");

  recap_text->setStyleSheet("border-top-style: none; border-radius: 0px;");

  best_day->setStyleSheet(
      "font-weight: bold; border-radius: 0px; border-top-style: none; "
      "border-right-style: none; color: white; background-color: black;"
      "border-bottom: 1px solid white;");
  best_date->setStyleSheet("font-weight: bold; border-radius: 0px; "
                           "border-right-style: none; border-top-style: none;");
  generate_rgb(red, green, entry_recap->get_best_day_mood() / 100);
  best_mood->setStyleSheet("font-weight: bold; color: rgb(" +
                           QString::number(red) + ", " +
                           QString::number(green) +
                           ", 0); "
                           "border-radius: 0px; border-top-style: none;");

  worst_day->setStyleSheet(
      "font-weight: bold; border-top-left-radius: 0px; "
      "border-top-right-radius: 0px; "
      "border-bottom-right-radius: 0px; border-style: none; color: white; "
      "background-color: black;"
      "border-left: 1px solid black; border-bottom: 1px solid black;");
  worst_date->setStyleSheet(
      "font-weight:bold; border-style: none; border-left: 1px solid black; "
      "border-radius: 0px; border-bottom: 1px solid black;");
  generate_rgb(red, green, entry_recap->get_worst_day_mood() / 100);
  worst_mood->setStyleSheet("font-weight: bold; color: rgb(" +
                            QString::number(red) + ", " +
                            QString::number(green) +
                            ", 0); border-top-style: none;"
                            "border-radius: 0px; border-bottom-right-radius: " +
                            QString::number(get_border_radius()) + "px;");
}

void EntryCard::display(QLayout *layout) { layout->addWidget(this); }

bool EntryCard::isReadOnly() { return readOnly; }

void EntryCard::setReadOnly(bool readOnly) { this->readOnly = readOnly; }

void EntryCard::set_main_window(MainWindow *mw) { main_window = mw; }

bool Card::eventFilter(QObject *target, QEvent *e) {
  if (qobject_cast<QComboBox *>(target) != NULL && e->type() == QEvent::Wheel) {
    return true;
  }
  return false;
}

void EntryCard::automatic_mood(double mood) {
  entry_perso->set_mood(mood);
  mood_slider->setValue(round(mood));
  habits_display->setItemText(0, "Mood: " + QString::number(round(mood)) + "%");
  this->set_correct_style();
}

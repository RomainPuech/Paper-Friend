#include "entryclasses.h"
#include "activityclasses.h"
#include "mainwindow.h"

#include <iostream>
#include <random>
#include <string>
#include <vector>

Entry::Entry(std::string text, std::string title) : title(title), text(text) {
  this->set_qdate(QDate::currentDate());
}

std::string Entry::get_text() const { return text; }

void Entry::set_text(std::string text) { this->text = text; }

std::string Entry::get_title() const { return title; }

void Entry::set_title(std::string title) { this->title = title; }

std::string Entry::get_date() const { return date; }

void Entry::set_date(std::string format_date) {
  const char *s = "MM.dd.yyyy";
  std::string str(s);
  QString format = QString::fromStdString(s);
  QDate new_date =
      QDate::fromString(QString::fromStdString(format_date), format);
  this->set_qdate(new_date);
}

QDate Entry::get_qdate() const { return qdate; }

void Entry::set_qdate(QDate qdate) {
  this->qdate = qdate;
  this->date = qdate.toString("MM.dd.yyyy").toStdString();
  this->weekday = qdate.toString("dddd")
                      .toStdString(); // Day name : "Monday", "Tuesday", ...
  this->absolute_day = qdate.toJulianDay();
}

std::string Entry::get_weekday() const { return weekday; }

std::string Entry::get_month_name() const {
  return qdate.toString("MMMM").toStdString();
}

int Entry::get_absolute_day() const { return absolute_day; }

int Entry::entry_type() const { return 0; }

EntryPerso::EntryPerso(std::string title, std::string text,
                       std::vector<Activity *> p_activities, double mood,
                       double sleep, double eating_healthy, double productivity,
                       double socializing, double physical_activity)
    : Entry(title, text), activities(p_activities), mood(mood),
      sleep(sleep), eating_healthy(eating_healthy),
      productivity(productivity), socializing(socializing),
      physical_activity(physical_activity) {

  all_activities.push_back(Activity("Mood", mood, mood));
  all_activities.push_back(Activity("Sleep", sleep, sleep));
  all_activities.push_back(
      Activity("Eating Healthy", eating_healthy, eating_healthy));
  all_activities.push_back(
      Activity("Productivity", productivity, productivity));
  all_activities.push_back(Activity("Socializing", socializing, socializing));
  all_activities.push_back(
      Activity("Physical Activity", physical_activity, physical_activity));

  for (auto &ptr : activities)
    all_activities.push_back(*ptr);

}
EntryPerso::~EntryPerso() {
  /*
  for (auto el : activities)
    delete el;*/
}

double EntryPerso::get_var_value(int index) const {
  return all_activities[index].get_value();
}

std::string EntryPerso::get_var_name(int index) const {
    std::string str;
    switch (index) {
        case 2:
            str = "Eating healthy";
            break;

        case 5:
            str = "Physical activity";
            break;

        default:
            str = all_activities[index].get_name();
    }
    return str;
}

std::vector<Activity *> EntryPerso::get_activities() const {
  return activities;
}

void EntryPerso::set_activities(std::vector<Activity *> activities) {
  this->activities = activities;
}
void EntryPerso::add_activity(Activity *activity) {
  activities.push_back(activity);
}

double EntryPerso::get_mood() const { return mood; }

void EntryPerso::set_mood(double mood) { this->mood = mood; }

double EntryPerso::get_sleep() const { return sleep; }

void EntryPerso::set_sleep(double sleep) { this->sleep = sleep; }

double EntryPerso::get_eating_healthy() const { return eating_healthy; }

void EntryPerso::set_eating_healthy(double eating_healthy) {
  this->eating_healthy = eating_healthy;
}

double EntryPerso::get_productivity() const { return productivity; }

void EntryPerso::set_productivity(double productivity) {
  this->productivity = productivity;
}

double EntryPerso::get_socializing() const { return socializing; }

void EntryPerso::set_socializing(double socializing) {
  this->socializing = socializing;
}

double EntryPerso::get_physical_activity() const { return physical_activity; }

void EntryPerso::set_physical_activity(double physical_activity) {
  this->physical_activity = physical_activity;
}

int EntryPerso::entry_type() const { return 1; }

std::vector<EntryPerso *> sample_entries(int n) {
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(65, 25);
  std::vector<EntryPerso *> res = std::vector<EntryPerso *>();
  std::vector<Activity> activities_main = MainWindow::get_activities();
  std::vector<Activity *> activities;
  for (int i = n; i > 0; --i) {
    activities.clear();
    for (Activity activity : activities_main) {
      Activity *to_add = new Activity();
      to_add->set_name(activity.get_name());
      to_add->set_type(activity.get_type());
      to_add->set_value(rand() % 2);
      activities.push_back(to_add);
    }
    double mood = distribution(generator);
    mood = std::llround(mood * 2) / 2.0;
    if (mood > 100) {
      mood = 100;
    }
    if (mood < 0) {
      mood = 0;
    }
    double sleep = rand() % 101;
    double eating_healthy = rand() % 101;
    double productivity = rand() % 101;
    double socializing = rand() % 101;
    double physical_activity = rand() % 101;
    EntryPerso *entry =
        new EntryPerso("sample entry text", "The title of the entry",
                       activities, mood, sleep, eating_healthy,
                       productivity, socializing, physical_activity);
    entry->set_qdate((QDate::currentDate()).addDays(-i));
    res.push_back(entry);
  }
  return res;
}

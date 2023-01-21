#ifndef ENTRYCLASSES_H
#define ENTRYCLASSES_H

#pragma once

#include <QDate>
#include <iostream>
#include <string>

#include "activityclasses.h"

class Entry {
public:
  Entry(std::string text = "", std::string title = "");

  std::string get_text() const;
  void set_text(std::string text);

  std::string get_title() const;
  void set_title(std::string text);

  std::string get_date() const; // "MM.DD.YYYY"
  void set_date(std::string format_date);

  QDate get_qdate() const;
  void set_qdate(QDate qdate);

  std::string get_weekday() const; // 1 = Monday, 2 = Tuesday", ...
  std::string get_month_name() const;

  int get_absolute_day() const; // Day in Julian calendar

  virtual int entry_type() const;

protected:
  std::string title;
  std::string text;
  QDate qdate;
  std::string date;
  std::string weekday;
  int absolute_day;
};

class EntryPerso : public Entry {
public:
  EntryPerso(std::string text = "", std::string title = "",
             std::vector<Activity *> activities = std::vector<Activity *>(),
             double mood = 0, double sleep = 0, double eating_healthy = 0,
             double productivity = 0, double socializing = 0,
             double physical_activity = 0);
  ~EntryPerso();

  std::vector<Activity *> get_activities() const;
  void set_activities(std::vector<Activity *> activities);
  void add_activity(Activity *activity);

  double get_var_value(int index) const;
  std::string get_var_name(int index) const;

  double get_mood() const;
  void set_mood(double mood);

  double get_sleep() const;
  void set_sleep(double sleep);

  double get_eating_healthy() const;
  void set_eating_healthy(double eating_healthy);

  double get_productivity() const;
  void set_productivity(double productivity);

  double get_socializing() const;
  void set_socializing(double socializing);

  double get_physical_activity() const;
  void set_physical_activity(double physical_activity);

  int get_num_activities() { return all_activities.size(); }
  virtual int entry_type() const;

private:
  std::vector<Activity> all_activities;
  std::vector<Activity *> activities;
  double mood;
  double sleep;
  double eating_healthy;
  double productivity;
  double socializing;
  double physical_activity;
};

std::vector<EntryPerso *>
sample_entries(int n); // gives n randomly generated sample entries

#endif // ENTRYCLASSES_H

#ifndef ACTIVITYCLASSES_H
#define ACTIVITYCLASSES_H
#pragma once

#include <QString>
#include <iostream>
#include <string>

struct Activity {

  Activity(std::string name = "", int type = 0, double value = 0);

  std::string get_name() const;
  void set_name(std::string name);

  double get_value() const;
  void set_value(double value);

  int get_type() const;
  void set_type(int type);

  bool operator==(
      Activity other) const; // used when trying to find an activity in a vector

protected:
  std::string name;
  int type;
  double value;
};

bool operator==(Activity &a, Activity &b);

#endif // ACTIVITYCLASSES_H

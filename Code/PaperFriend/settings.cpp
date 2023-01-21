#include "settings.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<bool> saved_settings() {
  std::string state;
  std::vector<bool> current_settings;
  std::ifstream myfile;
  myfile.open("settings.txt");
  while (getline(myfile, state)) {
    current_settings.push_back(state == "1");
  }
  myfile.close();
  while (current_settings.size() < NUMBER_OF_SETTINGS) {
    current_settings.push_back(
        true); // the default value of every setting is true
  }
  return current_settings;
}

bool saved_week() {
  std::vector<bool> current_settings = saved_settings();
  return current_settings[0];
}

bool saved_month() {
  std::vector<bool> current_settings = saved_settings();
  return current_settings[1];
}

bool saved_year() {
  std::vector<bool> current_settings = saved_settings();
  return current_settings[2];
}


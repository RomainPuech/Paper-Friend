#include "settings.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::vector<bool> saved_settings() {
    std::string state;
    std::vector<bool> current_settings;
    std::ifstream myfile;
    myfile.open("settings.txt");
    while (getline (myfile, state)) {
      current_settings.push_back(state == "0");
    }
    myfile.close();
    return current_settings;
}

bool saved_mood() {
    std::vector<bool> current_settings = saved_settings();
    return current_settings[0];
}

bool saved_sleep() {
    std::vector<bool> current_settings = saved_settings();
    return current_settings[1];
}

bool saved_eating_healthy() {
    std::vector<bool> current_settings = saved_settings();
    return current_settings[2];
}

bool saved_productivity() {
    std::vector<bool> current_settings = saved_settings();
    return current_settings[3];
}

bool saved_communications() {
    std::vector<bool> current_settings = saved_settings();
    return current_settings[4];
}

bool saved_screen_time() {
    std::vector<bool> current_settings = saved_settings();
    return current_settings[5];
}

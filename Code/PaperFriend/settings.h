#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <vector>

std::vector<bool> saved_settings();

bool saved_mood();

bool saved_sleep();

bool saved_eating_healthy();

bool saved_productivity();

bool saved_communications();

bool saved_screen_time();

const int NUMBER_OF_SETTINGS = 6;

#endif // SETTINGS_H

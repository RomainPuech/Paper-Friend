#ifndef SETTINGS_H
#define SETTINGS_H
#pragma once

#include <iostream>
#include <vector>

std::vector<bool> saved_settings();

bool saved_week();

bool saved_month();

bool saved_year();

const int NUMBER_OF_SETTINGS = 3;

#endif // SETTINGS_H

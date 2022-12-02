#ifndef FILE_SAVE_AND_LOAD_H
#define FILE_SAVE_AND_LOAD_H
#include <string>
#include <QJsonDocument>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include "entryclasses.h"

void save_entry(Entry entry);

Entry load_entry(Entry entry);

#endif

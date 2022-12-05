#ifndef FILE_SAVE_AND_LOAD_H
#define FILE_SAVE_AND_LOAD_H
#include <string>
#include <QJsonDocument>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include "entryclasses.h"

bool save_entry(Entry entry);

bool save_entry_encrypt(Entry entry, std::string path, std::string key);


Entry load_entry(std::string filename);

Entry load_entry_decrypt(std::string filename, std::string key);

#endif

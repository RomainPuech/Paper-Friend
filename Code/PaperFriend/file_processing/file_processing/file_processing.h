#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H
#include <string>
#include "file_processing_global.h"
#include <QJsonDocument>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include "C:/Qt/TDs/PaperFriend-desktop-app/Code/PaperFriend/entryclasses.h"


class FILE_PROCESSING_EXPORT File_processing
{
public:
    File_processing();
};


#endif // FILE_PROCESSING_H



void save_entry(Entry entry);

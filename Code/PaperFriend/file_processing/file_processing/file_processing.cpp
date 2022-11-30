#include "file_processing.h"
#include <QJsonDocument>
#include <string>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include "C:/Qt/TDs/PaperFriend-desktop-app/Code/PaperFriend/entryclasses.h"

using json = nlohmann::json;


File_processing::File_processing()
{
};

void save_Entry(Entry entry){ // I create and save the entry file, title format MM-YY-JJ
    json j = {
        {"mood", 1.2},
        {"sleep", 2.2},
        {"eating_healthy", 1.5},
        {"productivity", 1.5},
        {"communications", 2.1},
        {"screen_time", 10.2},
        {"activities", {
            "act1",
            "act2",
            "act3"
        }},
        {"friends", {
            "friend1",
            "friend2",
            "friend3",
            "friend4"
        }}
    };


    std::ofstream o("output.json");
    o << j << std::endl;
    o.close();
};


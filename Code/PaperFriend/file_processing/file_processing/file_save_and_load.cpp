#include "file_save_and_load.h"



void save_Entry(Entry entry){ // I create and save the entry file, title format MM-YY-JJ
    nlohmann::json  j = {
        {"text", entry.get_text()},
        {"title", entry.get_title()},
        {"date", entry.get_date()}};
    std::string filename = entry.get_qdate().toString("MM.dd.yyyy").toStdString()+".json";
    std::ofstream o(filename);

    o << j << std::endl;
    o.close();
};

Entry load_entry(std::string filename){
    std::ifstream i(filename);
    nlohmann::json j;
    i >> j;
    Entry res = Entry(j["text"], j["title"]);
    res.set_date(j["date"]);
    return res;
}

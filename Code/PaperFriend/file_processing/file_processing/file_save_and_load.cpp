#include "file_save_and_load.h"
#include "cipher/cipher.h"
#include "qdir.h"
#include <QFile>




bool save_entry(Entry entry){ // I create and save the entry file, title format MM.YY.JJ

    nlohmann::json  j = {
        {"text", entry.get_text()},
        {"title", entry.get_title()},
        {"date", entry.get_date()}};
    std::string filename = entry.get_qdate().toString("MM.dd.yyyy").toStdString()+".json";

    std::ofstream o("./" + filename);


    if(!o.is_open()){
        std::cout << "Error opening file" << std::endl;
        return false;
    }
    o << j << std::endl;

    o.close();
    return true;
};

bool save_entry_encrypt(Entry entry, std::string path, std::string key){ 
    nlohmann::json  j = {
        {"text", encode_string(entry.get_text(), key)},
        {"title", encode_string(entry.get_title(), key)},
        {"date", encode_string(entry.get_date(), key)}};

    std::string filename = entry.get_qdate().toString("MM.dd.yyyy").toStdString()+".json";
    if (path.back() != '/'){
        path += "/";
    }// add a slash if there is none

    QDir dir(QString::fromStdString(path));
    if (!dir.exists()){
        dir.mkpath(".");
    } // create the directory if it does not exist

    QFile file(QString::fromStdString(path + filename));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        file.write(j.dump().c_str());
        file.close();
        return true;
    }
    return false;
};






Entry load_entry(std::string filename){//retrieve the data of a Json file and return an initialized Entry object with this data
    std::ifstream i(filename);
    nlohmann::json j;
    i >> j;
    Entry res = Entry(j["text"], j["title"]);
    res.set_date(j["date"]);
    return res;
}

Entry load_entry_decrypt(std::string filename, std::string key){
    if(!QFile::exists(QString::fromStdString(filename))){
        std::cout << "File does not exist" << std::endl;
        return Entry();
    }
    std::ifstream i(filename);
    nlohmann::json j;
    i >> j;
    Entry res = Entry(decode_string(j["text"], key), decode_string(j["title"], key));
    res.set_date(decode_string(j["date"], key));
    return res;
}

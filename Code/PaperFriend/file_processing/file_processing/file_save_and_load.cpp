#include "file_save_and_load.h"
#include "cipher/cipher.h"
#include "qdir.h"
#include <QFile>




bool save_entry(Entry entry){ //  create and save the entry file, title format MM.YY.JJ

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




std::string activity_to_string(Activity act){//function that return a string that resume the activities to be saved
    std::string name = act.get_name();
    std::string value = std::to_string(act.get_value());
    std::string type = std::to_string(act.get_type());
    std::string delimiter = "$*$";
    std::string delimiter2 = "*$*";
    return (name+delimiter + value + delimiter+type + delimiter2);
};

Activity string_to_activity(std::string act){//function that takes a 'string resume' of an activity and return an initialized and corresponding Activity object
    std::string delimiter = "$*$";
    std::string temp = act.substr(0, act.find(delimiter));//extract the name
    std::string name = temp;
    act.erase(0, act.find(delimiter) + delimiter.length());
    temp = act.substr(0, act.find(delimiter));//extract the value
    double value = std::stod(temp);
    act.erase(0, act.find(delimiter) + delimiter.length());
    temp = act.substr(0, act.find(delimiter));//extract the type
    int type= std::stoi(temp);
    Activity res = Activity(name, value); //initialize the result
    res.set_type(type);
    return res;
};


std::string activities_vec_to_str (std::vector<Activity*> acts){//takes a vector of pointers to activities and return a string resuming all the vector (to be saved)
    std::string res;
    for(int i=0; i < acts.size(); i++){
       res += activity_to_string(*acts[i]);
    }
    return res;
}


std::vector<Activity*> str_to_vec_activities (std::string act){//activity vec from a string
    std::vector <Activity*> res;
    std::string delimiter = "*$*";

    size_t pos = 0;
    std::string temp;
    while ((pos = act.find(delimiter)) != std::string::npos) {
        temp = act.substr(0, pos);
        Activity* activity = new Activity(string_to_activity(temp));
        res.push_back(activity);
        act.erase(0, pos + delimiter.length());
    }
    return res;

}



std::string friend_to_string(Friend act){//function that return a string that resume the friend to be saved
    std::string name = act.get_name();
    std::string duration = std::to_string(act.get_duration());
    std::string delimiter = "$*$";
    std::string delimiter2 = "*$*";
    return (name+delimiter +duration + delimiter2);
};

Friend string_to_frend(std::string act){//function that takes a 'string resume' of a friend and return an initialized and corresponding friend object
    std::string delimiter = "$*$";
    std::string temp = act.substr(0, act.find(delimiter));//extract the name
    std::string name = temp;
    act.erase(0, act.find(delimiter) + delimiter.length());
    temp = act.substr(0, act.find(delimiter));//extract the type
    int duration = std::stoi(temp);
    Friend res = Friend(name, duration); //initialize the result
    return res;
};


std::string friend_vec_to_str (std::vector<Friend*> acts){//takes a vector of pointers to Friend and return a string resuming all the vector (to be saved)
    std::string res;
    for(int i=0; i < acts.size(); i++){
       res += friend_to_string(*acts[i]);
    }
    return res;
}

std::vector<Friend*> str_to_vec_friends (std::string act){//activity vec from a string
    std::vector <Friend*> res;
    std::string delimiter = "*$*";

    size_t pos = 0;
    std::string temp;
    while ((pos = act.find(delimiter)) != std::string::npos) {
        temp = act.substr(0, pos);
        Friend* activity = new Friend(string_to_frend(temp));
        res.push_back(activity);
        act.erase(0, pos + delimiter.length());
    }
    return res;

}




bool save_entryperso(EntryPerso entry){ // I create and save the entry file, title format MM.YY.JJ

    std::string activities = activities_vec_to_str(entry.get_activities());
    std::string friends = friend_vec_to_str(entry.get_friends());
    std::cout<<activities<<"\n";
    std::cout<<friends<<"\n";


    nlohmann::json  j = {
        {"text", entry.get_text()},
        {"title", entry.get_title()},
        {"date", entry.get_date()},

        {"mood", entry.get_mood()},
        {"sleep", entry.get_sleep()},
        {"eating_healthy",entry.get_eating_healthy()},
        {"productivity", entry.get_productivity()},
        {"communications", entry.get_communications()},
        {"screen_time", entry.get_screen_time()},
        {"activities",activities},

        {"friends", friends}
    };
    std::string filename = entry.get_qdate().toString("MM.dd.yyyy").toStdString()+".json";

    std::ofstream o("./" + filename);


    if(!o.is_open()){
        std::cout << "Error opening file" << std::endl;
        return false;
    }
    o << j << std::endl;
    std::cout<<"ouii";
    o.close();
    std::cout<<"nonnn";
    return true;
};






EntryPerso load_entryperso(std::string filename){//retrieve the data of a Json file and return an initialized Entry object with this data
    std::ifstream i(filename);
    nlohmann::json j;
    i >> j;
    EntryPerso res = EntryPerso(j["text"], j["title"], str_to_vec_activities(j["activities"]), str_to_vec_friends(j["friends"]), j["mood"], j["sleep"], j["eating_healthy"], j["productivity"],j["communications"], j["screen_time"] );
    res.set_date(j["date"]);
    return res;
}






bool save_activities (std::vector<Activity> acts){//save the std::vector of activities in a file to keep track of all possible types of activities
    std::string res;
    for(int i=0; i < acts.size(); i++){
       res += activity_to_string(acts[i]);
    }
    nlohmann::json  j = {
        {"activities", res},
        };

    std::string filename = "activities.json";


    std::ofstream o("./" + filename);


    if(!o.is_open()){
        std::cout << "Error opening file" << std::endl;
        return false;
    }
    o << j << std::endl;

    o.close();
    return true;
}

std::vector<Activity> load_activities (){//activity vec from a string
    std::string filename = "activities.json";
    std::ifstream i(filename);
    nlohmann::json j;
    i >> j;

    std::string act = j["activities"];

    std::vector <Activity> res;
    std::string delimiter = "*$*";

    size_t pos = 0;
    std::string temp;
    while ((pos = act.find(delimiter)) != std::string::npos) {
        temp = act.substr(0, pos);
        Activity activity = string_to_activity(temp);
        res.push_back(activity);
        act.erase(0, pos + delimiter.length());
    }
    return res;

}

bool save_friends (std::vector<Friend> acts){//save the std::vector of activities in a file to keep track of all possible types of activities
    std::string res;
    for(int i=0; i < acts.size(); i++){
       res += friend_to_string(acts[i]);
    }
    nlohmann::json  j = {
        {"friends", res},
        };

    std::string filename = "friends.json";


    std::ofstream o("./" + filename);


    if(!o.is_open()){
        std::cout << "Error opening file" << std::endl;
        return false;
    }
    o << j << std::endl;

    o.close();
    return true;
}

std::vector<Friend> load_friends (){//Friend vec from a string
    std::string filename = "friends.json";
    std::ifstream i(filename);
    nlohmann::json j;
    i >> j;

    std::string act = j["friends"];

    std::vector <Friend> res;
    std::string delimiter = "*$*";

    size_t pos = 0;
    std::string temp;
    while ((pos = act.find(delimiter)) != std::string::npos) {
        temp = act.substr(0, pos);
        Friend activity = string_to_frend(temp);
        res.push_back(activity);
        act.erase(0, pos + delimiter.length());
    }
    return res;

}

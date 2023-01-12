#ifndef FILE_SAVE_AND_LOAD_H
#define FILE_SAVE_AND_LOAD_H
#include <string>
#include <QJsonDocument>
#include "json-develop/single_include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include "entryclasses.h"
#include "activityclasses.h"
#include "friendclasses.h"
#include "entryrecap.h"

bool save_entry(Entry entry);

bool save_entry_encrypt(Entry entry, std::string path, std::string key);

Entry load_entry(std::string filename);

Entry load_entry_decrypt(std::string filename, std::string key);

std::string activity_to_string(Activity act);

Activity string_to_activity(std::string act);

std::string activities_vec_to_str (std::vector<Activity*> acts);



std::vector<Activity*> str_to_vec_activities (std::vector<Activity*> possible_activities,std::string act);


std::string friend_to_string(Friend act);

Friend string_to_frend(std::string act);

std::string friend_vec_to_str (std::vector<Friend*> acts);

std::vector<Friend*> str_to_vec_friends (std::string act);

bool save_entryperso(EntryPerso entry);

EntryPerso* load_entryperso(std::string filename,std::vector<Activity> possible_activities);

bool save_activities (std::vector<Activity> act);

bool save_friends (std::vector<Friend> fr);

bool save_entryrecap (EntryRecap entry);

EntryRecap* load_entryrecap (std::string filename, std::vector<Activity> possible_activities);

std::vector<Activity> load_activities();

std::vector<Friend> load_friends();

std::vector<QStringList> load_habits();

std::vector<QString> load_last_recaps_dates();

void save_last_recaps_dates(std::vector<QString> last_recaps_dates);


#endif

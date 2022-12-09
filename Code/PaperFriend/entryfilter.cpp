#include "entryfilter.h"


// a function takes a vector of Entries and a function as input.
// output a vector of pointers to entries that satisfy the function.
// for more information of the function, please refer to wiki: https://github.com/CSE201-project/PaperFriend-desktop-app/wiki/Entry-filter-function

std::vector<Entry*> filter(
    std::vector<Entry>& entries,
    bool (*filterFn)(const Entry&)) {
    
    std::vector<Entry*> filteredEntries;
    for(int i=0;i<entries.size();i++){
        if (filterFn(entries[i])) {
            filteredEntries.push_back(&entries[i]);
        }
    }
    return filteredEntries;
}

std::vector<EntryPerso*> filter(
    std::vector<EntryPerso>& entries,
    bool (*filterFn)(const EntryPerso&, std::string keyword, std::string opt, int value),
    std::string keyword,
    std::string opt,
    int value) {
    
    std::vector<EntryPerso*> filteredEntries;
    for(int i=0;i<entries.size();i++){
        if (filterFn(entries[i], keyword , opt, value)) {
            filteredEntries.push_back(&entries[i]);
        }
    }
    return filteredEntries;
}

bool compare_long_text(Entry& e) {
    return e.get_text().length() < 15;
}

// simple value comparison function for EntryPerso
bool compare_value(const EntryPerso& e, std::string keyword, std::string opt, int value) {
    if (keyword == "mood") {
        if (opt == ">") {
            return e.get_mood() > value;
        } else if (opt == "<") {
            return e.get_mood() < value;
        } else if (opt == "=") {
            return e.get_mood() == value;
        }
    } else if (keyword == "sleep") {
        if (opt == ">") {
            return e.get_sleep() > value;
        } else if (opt == "<") {
            return e.get_sleep() < value;
        } else if (opt == "=") {
            return e.get_sleep() == value;
        }
    } else if (keyword == "eating_healthy") {
        if (opt == ">") {
            return e.get_eating_healthy() > value;
        } else if (opt == "<") {
            return e.get_eating_healthy() < value;
        } else if (opt == "=") {
            return e.get_eating_healthy() == value;
        }
    } else if (keyword == "productivity") {
        if (opt == ">") {
            return e.get_productivity() > value;
        } else if (opt == "<") {
            return e.get_productivity() < value;
        } else if (opt == "=") {
            return e.get_productivity() == value;
        }
    } else if (keyword == "communications") {
        if (opt == ">") {
            return e.get_communications() > value;
        } else if (opt == "<") {
            return e.get_communications() < value;
        } else if (opt == "=") {
            return e.get_communications() == value;
        }
    } else if (keyword == "screen_time") {
        if (opt == ">") {
            return e.get_screen_time() > value;
        } else if (opt == "<") {
            return e.get_screen_time() < value;
        } else if (opt == "=") {
            return e.get_screen_time() == value;
        }
    }
}


std::vector<EntryPerso> random_entryperso(int num){
    std::vector<EntryPerso> entries;
    for(int i=0;i<num;i++){
        EntryPerso e;
        e.set_mood(rand()%10);
        e.set_sleep(rand()%10);
        e.set_eating_healthy(rand()%10);
        e.set_productivity(rand()%10);
        e.set_communications(rand()%10);
        e.set_screen_time(rand()%10);
        entries.push_back(e);
    }
    return entries;
}










#include "entryfilter.h"


// a function takes a vector of Entries and a function as input.
// output a vector of pointers to entries that satisfy the function.

std::vector<Entry*> filter (std::vector<Entry>& entries, bool (*f)(Entry&)) {
    std::vector<Entry*> filtered = {};
    for (int i = 0; i < entries.size(); i++) {
        if (f(entries[i])) {
            filtered.push_back(&(entries[i])); 
        }
    }
    return filtered;
}

std::vector<EntryPerso*> filter (std::vector<EntryPerso>& entries, bool (*f)(EntryPerso&)) {
    std::vector<EntryPerso*> filtered = {};
    for (int i = 0; i < entries.size(); i++) {
        if (f(entries[i])) {
            filtered.push_back(&(entries[i])); 
        }
    }
    return filtered;
}

bool compare_long_text(Entry& e) {
    return e.get_text().length() < 15;
}

bool compare_long_text(EntryPerso& e) {
    return e.get_text().length() < 15;
}

bool compare_mood(EntryPerso& e) {
    return e.get_mood() > 2;
}









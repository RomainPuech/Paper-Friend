#include "entryfilter.h"


// a function takes a vector of Entries and a function as input.
// output a vector of pointers to entries that satisfy the function.

std::vector<std::unique_ptr<Entry>> filter(
    const std::vector<Entry>& entries,
    bool (*filterFn)(const Entry&)) {

    std::vector<std::unique_ptr<Entry>> filteredEntries;

    for (const Entry& entry : entries) {
        if (filterFn(entry)) {
        filteredEntries.push_back(std::make_unique<Entry>(entry));
        }
    }

    return filteredEntries;
}

std::vector<EntryPerso*> filter(
    std::vector<EntryPerso>& entries,
    bool (*filterFn)(const EntryPerso&)) {
    
    std::vector<EntryPerso*> filteredEntries;
    for(int i=0;i<entries.size();i++){
        if (filterFn(entries[i])) {
            filteredEntries.push_back(&entries[i]);
        }
    }
    return filteredEntries;
}

bool compare_long_text(Entry& e) {
    return e.get_text().length() < 15;
}

bool compare_long_text(EntryPerso& e) {
    return e.get_text().length() < 15;
}

bool compare_mood(const EntryPerso& e) {
    return e.get_mood() > 2;
}









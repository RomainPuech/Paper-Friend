#ifndef ENTRYFILTER_H
#define ENTRYFILTER_H
#include "entryclasses.h"
#include <iostream>
#include <functional>
#include <memory>

// a function takes a vector of Entries and a function as input.
// output a vector of pointers to entries that satisfy the function.
// for more information of the function, please refer to wiki: https://github.com/CSE201-project/PaperFriend-desktop-app/wiki/Entry-filter-function

std::vector<Entry*> filter(
    std::vector<Entry>& entries,
    bool (*filterFn)(const Entry&));

std::vector<EntryPerso*> filter(
    std::vector<EntryPerso>& entries,
    bool (*filterFn)(const EntryPerso&));

bool compare_long_text(const Entry& e);

bool compare_long_text(const EntryPerso& e);

bool compare_mood(const EntryPerso& e);

#endif // ENTRYFILTER_H

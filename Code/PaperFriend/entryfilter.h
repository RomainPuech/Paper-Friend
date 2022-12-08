#ifndef ENTRYFILTER_H
#define ENTRYFILTER_H
#include "entryclasses.h"
#include <iostream>
#include <functional>
#include <memory>

// a function takes a function and a vector of entries as input.
// output a vector of  pointers to entries that satisfy the function.


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

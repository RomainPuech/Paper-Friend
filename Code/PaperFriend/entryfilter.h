#ifndef ENTRYFILTER_H
#define ENTRYFILTER_H
#include "entryclasses.h"
#include <iostream>

// a function takes a function and a vector of entries as input.
// output a vector of  pointers to entries that satisfy the function.


std::vector<Entry*> filter (std::vector<Entry>& entries, bool (*f)(Entry&));

std::vector<EntryPerso*> filter (std::vector<EntryPerso>& entries, bool (*f)(EntryPerso&));

bool compare_long_text(Entry& e);

bool compare_long_text(EntryPerso& e);

bool compare_mood(EntryPerso& e);

#endif // ENTRYFILTER_H

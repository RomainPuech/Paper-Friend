#ifndef ENTRYFILTER_H
#define ENTRYFILTER_H

#pragma once

#include "entryclasses.h"
#include <functional>
#include <iostream>
#include <memory>

// a function takes a vector of Entries and a function as input.
// output a vector of pointers to entries that satisfy the function.
// for more information of the function, please refer to wiki:
// https://github.com/CSE201-project/PaperFriend-desktop-app/wiki/Entry-filter-function

struct Filter_param {
  bool is_value_compare;
  std::string keyword;
  std::string opt;
  double value;
  int display_num;
};

std::vector<Entry *> filter(std::vector<Entry> &entries,
                            bool (*filterFn)(const Entry &));

std::vector<EntryPerso *>
filter(std::vector<EntryPerso> &entries,
       bool (*filterFn)(const EntryPerso &, std::string keyword,
                        std::string opt, int value),
       std::string keyword, std::string opt, int value);

std::vector<EntryPerso *>
filter(std::vector<EntryPerso *> entries,
       bool (*filterFn)(const EntryPerso &, std::string keyword,
                        std::string opt, int value),
       std::string keyword, std::string opt, int value);

std::vector<EntryPerso *> filter(std::vector<EntryPerso *> entries,
                                 Filter_param param);

bool compare_long_text(const Entry &e);

// simple value comparison function for EntryPerso
bool compare_value(const EntryPerso &e, std::string keyword, std::string opt,
                   int value);

std::vector<EntryPerso> random_entryperso(int num);

#endif // ENTRYFILTER_H

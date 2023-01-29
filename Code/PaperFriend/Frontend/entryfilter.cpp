#include "entryfilter.h"

// a function takes a vector of Entries and a function as input.
// output a vector of pointers to entries that satisfy the function.
// for more information of the function, please refer to wiki:
// https://github.com/CSE201-project/PaperFriend-desktop-app/wiki/Entry-filter-function

std::vector<Entry *> filter(std::vector<Entry> &entries,
                            bool (*filterFn)(const Entry &)) {

  std::vector<Entry *> filteredEntries;
  for (std::string::size_type i = 0; i < entries.size(); i++) {
    if (filterFn(entries[i])) {
      filteredEntries.push_back(&entries[i]);
    }
  }
  return filteredEntries;
}

std::vector<EntryPerso *>
filter(std::vector<EntryPerso> &entries,
       bool (*filterFn)(const EntryPerso &, std::string keyword,
                        std::string opt, int value),
       std::string keyword, std::string opt, int value) {

  std::vector<EntryPerso *> filteredEntries;
  for (std::string::size_type i = 0; i < entries.size(); i++) {
    if (filterFn(entries[i], keyword, opt, value)) {
      filteredEntries.push_back(&entries[i]);
    }
  }
  return filteredEntries;
}

std::vector<EntryPerso *>
filter(std::vector<EntryPerso *> entries,
       bool (*filterFn)(const EntryPerso &, std::string keyword,
                        std::string opt, int value),
       std::string keyword, std::string opt, int value) {

  std::vector<EntryPerso *> filteredEntries;
  for (std::string::size_type i = 0; i < entries.size(); i++) {
    if (filterFn(*(entries[i]), keyword, opt, value)) {
      filteredEntries.push_back(entries[i]);
    }
  }
  return filteredEntries;
}

std::vector<EntryPerso *> filter(std::vector<EntryPerso *> entries,
                                 Filter_param param) {

  std::vector<EntryPerso *> filteredEntries;
  for (std::string::size_type i = 0; i < entries.size(); i++) {
    if (param.is_value_compare) {
      if (compare_value(*(entries[i]), param.keyword, param.opt, param.value)) {
        filteredEntries.push_back(entries[i]);
      }
    }
  }
  return filteredEntries;
}

bool compare_long_text(Entry &e) { return e.get_text().length() < 15; }

// simple value comparison function for EntryPerso
bool compare_value(const EntryPerso &e, std::string keyword, std::string opt,
                   int value) {
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
  } else if (keyword == "socializing") {
    if (opt == ">") {
      return e.get_socializing() > value;
    } else if (opt == "<") {
      return e.get_socializing() < value;
    } else if (opt == "=") {
      return e.get_socializing() == value;
    }
  } else if (keyword == "physical_activity") {
    if (opt == ">") {
      return e.get_physical_activity() > value;
    } else if (opt == "<") {
      return e.get_physical_activity() < value;
    } else if (opt == "=") {
      return e.get_physical_activity() == value;
    }
  }
  return false;
}



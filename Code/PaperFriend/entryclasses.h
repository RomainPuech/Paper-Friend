#ifndef ENTRYCLASSES_H
#define ENTRYCLASSES_H

#include <iostream>
#include <string>


class Entry {
public:
    Entry();
    Entry(std::string text, std::string title);
    ~Entry() {}

    std::string get_text();
    void set_text(std::string text);

    std::string get_title();
    void set_title(std::string text);

    std::string get_date();

protected:
    std::string text;
    std::string title;
    std::string date;
};


class EntryPerso : public Entry {
public:
    EntryPerso();
    EntryPerso(std::string text, std::string title, std::string* activities, std::string* friends, double mood);
    ~EntryPerso();

    std::string* get_activities();
    void set_activities(std::string* activities);

    std::string* get_friends();
    void set_friends(std::string* friends);

    double get_mood();
    void set_mood(double mood);

private:
    std::string* activities;
    std::string* friends;
    double mood;
};

#endif // ENTRYCLASSES_H

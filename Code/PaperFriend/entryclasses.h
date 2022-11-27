#ifndef ENTRYCLASSES_H
#define ENTRYCLASSES_H

#include <iostream>
#include <string>

class Entry {
public:
    Entry();
    Entry(std::string text, std::string title);
    ~Entry();

    std::string get_text() const;
    void set_text(std::string text);

    std::string get_title() const;
    void set_title(std::string text);

    std::string get_date() const;

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

    std::string* get_activities() const;
    void set_activities(std::string* activities);

    std::string* get_friends() const;
    void set_friends(std::string* friends);

    double get_mood() const;
    void set_mood(double mood);

    double get_sleep() const;
    void set_sleep(double sleep);

    double get_eating_healthy() const;
    void set_eating_healthy(double eating_healthy);

    double get_productivity() const;
    void set_productivity(double productivity);

    double get_communications() const;
    void set_communications(double communications);

    double get_screen_time() const;
    void set_screen_time(double screen_time);

private:
    std::string* activities;
    std::string* friends;
    double mood;
    double sleep;
    double eating_healthy;
    double productivity;
    double communications;
    double screen_time;
};

#endif // ENTRYCLASSES_H

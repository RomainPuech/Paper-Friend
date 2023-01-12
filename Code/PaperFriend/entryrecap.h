#ifndef ENTRYRECAP_H
#define ENTRYRECAP_H
#include "entryclasses.h"

class EntryRecap : public Entry{ // creation of en EntryRecap class, more information abt this class can be found in the wiki
public:
    EntryRecap();
    EntryRecap( std::string best_day, std::string worst_day, std::string text, double average_mood, int type);
    //~EntryRecap();

    std::string get_best_day();
    std::string get_worst_day();
    double get_average_mood();
    int get_type();
    std::string get_text();
    std::string get_date();

    void set_best_day(std::string best_day);
    void set_worst_day(std::string worst_day);
    void set_average_mood(double average_mood);
    void set_type(int type);
    void set_text(std::string text);
    void set_date (std::string date);
    virtual int entry_type() const;




private:
    std::string best_day;
    std::string worst_day;
    std::string text;
    double average_mood;
    int type;
    std::string date;


};

#endif // ENTRYRECAP_H

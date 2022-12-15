#ifndef ENTRYRECAP_H
#define ENTRYRECAP_H
#include "entryclasses.h"

class EntryRecap : public Entry{ // creation of en EntryRecap class, more information abt this class can be found in the wiki
public:
    EntryRecap();
    EntryRecap(EntryPerso best_day, EntryPerso worst_day, std::string text,double average_mood, int type);
    //~EntryRecap();

    EntryPerso get_best_day();
    EntryPerso get_worst_day();
    double get_average_mood();
    int get_type();
    std::string get_text();

    void set_best_day(EntryPerso best_day);
    void set_worst_day(EntryPerso worst_day);
    void set_average_mood(double average_mood);
    void set_type(int type);
    void set_text(std::string text);





private:
    EntryPerso best_day;
    EntryPerso worst_day;
    std::string text;
    double average_mood;
    int type;


};

#endif // ENTRYRECAP_H

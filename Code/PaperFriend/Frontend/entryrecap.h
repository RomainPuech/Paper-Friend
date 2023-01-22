#ifndef ENTRYRECAP_H
#define ENTRYRECAP_H
#pragma once
#include "entryclasses.h"

class EntryRecap
    : public Entry { // creation of en EntryRecap class, more information abt
                     // this class can be found in the wiki
public:

    EntryRecap();
    EntryRecap( QDate best_day_date, QDate worst_day_date, double best_day_mood, double worst_day_mood,std::string text, double average_mood, int type);
    //~EntryRecap();

    QDate get_best_day_date();
    QDate get_worst_day_date();
    double get_best_day_mood();
    double get_worst_day_mood();
    double get_average_mood();
    int get_type();
    std::string get_text();


    void set_best_day_date(QDate best_day);
    void set_worst_day_date(QDate worst_day);
    void set_best_day_mood(double best_day_mood);
    void set_worst_day_mood(double best_day_mood);
    void set_average_mood(double average_mood);
    void set_type(int type);
    void set_text(std::string text);
    QDate get_qdate() const;

    virtual int entry_type() const;


private:
    QDate best_day_date;
    QDate worst_day_date;
    double best_day_mood;
    double worst_day_mood;
    std::string text;
    double average_mood;
    int type;


};

#endif // ENTRYRECAP_H

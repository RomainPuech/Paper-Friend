#include "entryrecap.h"
#include "entryclasses.h"


EntryRecap::EntryRecap(){
    EntryPerso temp =EntryPerso();
    this->best_day = temp;
    this->worst_day = temp;
    this->type= 0;
    this->average_mood = 0;
    this->text = "";



};

EntryRecap::EntryRecap(EntryPerso best_day, EntryPerso worst_day, std::string text,double average_mood, int type){
    this->best_day = best_day;
    this->worst_day = worst_day;
    this->type= type;
    this->average_mood = average_mood;
    this->text = text;
}

int EntryRecap::entry_type() const{
    return 2;
}
//EntryRecap::~EntryRecap(){ // useless as there's no destructor implmented for the EntryPerso class
//    ~best_day();
//    ~worst_day();
//}

EntryPerso EntryRecap::get_best_day(){
    return this->best_day;
}
EntryPerso EntryRecap::get_worst_day(){
    return this->worst_day;
}

double EntryRecap::get_average_mood(){
    return this->average_mood;
}

int EntryRecap::get_type(){
    return this->type;
}
std::string EntryRecap::get_text(){
    return this->text;
}

void EntryRecap::set_best_day(EntryPerso best_day){
    this->best_day = best_day;
}

void EntryRecap::set_worst_day(EntryPerso worst_day){
    this->worst_day = worst_day;
}

void EntryRecap::set_average_mood(double average_mood){
    this->average_mood = average_mood;
}
void EntryRecap::set_type(int type){
    this->type = type;
}

void EntryRecap::set_text(std::string text){
    this->text = text;
}



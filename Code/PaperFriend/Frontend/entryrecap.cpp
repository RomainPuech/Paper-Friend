#include "entryrecap.h"
#include "entryclasses.h"


EntryRecap::EntryRecap() : Entry() {// Initialize with default values
  this->best_day_date = QDate::currentDate();
  this->worst_day_date = QDate::currentDate();
  this->best_day_mood = 0.0;
  this->worst_day_mood = 0.0;
  this->type = 0;
  this->average_mood = 0;
};

EntryRecap::EntryRecap(QDate best_day_date,QDate worst_day_date,double best_day_mood, double worst_day_mood,
                       std::string text, double average_mood, int type)// Initialize with given values
    : Entry(text, ""),best_day_date(best_day_date),worst_day_date(worst_day_date),best_day_mood(best_day_mood),worst_day_mood(worst_day_mood),text(text),type(type),average_mood(average_mood)
{}

int EntryRecap::entry_type() const { return 2; }
// EntryRecap::~EntryRecap(){ // useless as there's no destructor implmented for
// the EntryPerso class
//     ~best_day();
//     ~worst_day();
// }


// Getters and setters:
QDate EntryRecap::get_best_day_date() { return best_day_date; }
QDate EntryRecap::get_worst_day_date() { return worst_day_date; }
double EntryRecap::get_best_day_mood() { return best_day_mood; }
double EntryRecap::get_worst_day_mood() { return worst_day_mood; }

double EntryRecap::get_average_mood() { return average_mood; }

int EntryRecap::get_type() { return type; }

std::string EntryRecap::get_text() { return text; }

void EntryRecap::set_best_day_date(QDate best_day_date) {
  this->best_day_date = best_day_date;
}

void EntryRecap::set_worst_day_date(QDate worst_day_date) {
  this->worst_day_date = worst_day_date;
}

void EntryRecap::set_best_day_mood(double best_day_mood) {
  this->best_day_mood = best_day_mood;
}

void EntryRecap::set_worst_day_mood(double worst_day_mood) {
  this->worst_day_mood = worst_day_mood;
}


void EntryRecap::set_average_mood(double average_mood) {
  this->average_mood = average_mood;
}

void EntryRecap::set_type(int type) { this->type = type; }

void EntryRecap::set_text(std::string text) { this->text = text; }

QDate EntryRecap::get_qdate() const { return this->qdate; }

#include "entryclasses.h"

#include <iostream>
#include <string>



Entry::Entry() {
    this->text = "";
    this->title = "";
    this->set_qdate(QDate::currentDate());
}

Entry::Entry(std::string text, std::string title){
    this->text = text;
    this->title = title;
    this->set_qdate(QDate::currentDate());
}

Entry::~Entry() {}

std::string Entry::get_text() const {
    return text;
}

void Entry::set_text(std::string text) {
    this->text=text;
}

std::string Entry::get_title() const {
    return title;
}

void Entry::set_title(std::string title) {
    this->title=title;
}

std::string Entry::get_date() const {
    return date;
}

void Entry::set_date(std::string format_date){
    const char *s = "MM/dd/yyyy";
    std::string str(s);
    QString format = QString::fromStdString(s);
    QDate new_date = QDate::fromString(QString::fromStdString(format_date), format);
    this->set_qdate(new_date);
}

QDate Entry::get_qdate() const {
    return qdate;
}

void Entry::set_qdate(QDate qdate) {
    this->qdate=qdate;
    this->date = qdate.toString("MM/dd/yyyy").toStdString();
    this->weekday = qdate.toString("dddd").toStdString(); // Day name : "Monday", "Tuesday", ...
    this->absolute_day = qdate.toJulianDay();
}

std::string Entry::get_weekday() const{
    return weekday;
}

int Entry::get_absolute_day() const{
    return absolute_day;
}


EntryPerso::EntryPerso() : Entry(), activities(NULL), friends(NULL), mood(0) {}

EntryPerso::EntryPerso(std::string text, std::string title, Activity* activities, Friend* friends, double mood,
                                                                                                   double sleep,
                                                                                                   double eating_healthy,
                                                                                                   double productivity,
                                                                                                   double communications,
                                                                                                   double screen_time) :
    Entry(text, title), activities(activities), friends(friends), mood(mood),
                                                                  sleep(sleep),
                                                                  eating_healthy(eating_healthy),
                                                                  productivity(productivity),
                                                                  communications(communications),
                                                                  screen_time(screen_time) {}

EntryPerso::~EntryPerso() {
    delete activities;
    delete friends;
}

Activity* EntryPerso::get_activities() const {
    return activities;
}

void EntryPerso::set_activities(Activity* activities) {
    this->activities = activities;
}

Friend* EntryPerso::get_friends() const {
    return friends;
}

void EntryPerso::set_friends(Friend* friends) {
    this->friends = friends;
}

double EntryPerso::get_mood() const {
    return mood;
}

void EntryPerso::set_mood(double mood) {
    this->mood = mood;
}

double EntryPerso::get_sleep() const {
    return sleep;
}

void EntryPerso::set_sleep(double sleep) {
    this->sleep = sleep;
}

double EntryPerso::get_eating_healthy() const {
    return eating_healthy;
}

void EntryPerso::set_eating_healthy(double eating_healthy) {
    this->eating_healthy = eating_healthy;
}

double EntryPerso::get_productivity() const {
    return productivity;
}

void EntryPerso::set_productivity(double productivity) {
    this->productivity = productivity;
}

double EntryPerso::get_communications() const {
    return communications;
}

void EntryPerso::set_communications(double communications) {
    this->communications = communications;
}

double EntryPerso::get_screen_time() const {
    return screen_time;
}

void EntryPerso::set_screen_time(double screen_time) {
    this->screen_time = screen_time;
}

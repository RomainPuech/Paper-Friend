#include "entryclasses.h"

#include <iostream>


std::string current_date() {
    const int maxlen = 80;
    char s[maxlen];
    time_t t = time(0);
    strftime(s, maxlen, "%m/%d/%Y", localtime(&t));
    return s;
}

Entry::Entry() {
    text = "";
    title = "";
    date = current_date();
}

Entry::Entry(std::string text, std::string title) {
    this->text = text;
    this->title = title;
    date = current_date();
}

std::string Entry::get_text() {
    return text;
}

void Entry::set_text(std::string text) {
    this->text=text;
}

std::string Entry::get_title() {
    return title;
}

void Entry::set_title(std::string title) {
    this->title=title;
}

std::string Entry::get_date() {
    return date;
}


EntryPerso::EntryPerso() {
    Entry();
    activities = NULL;
    friends = NULL;
    mood = 0;
}

EntryPerso::EntryPerso(std::string text, std::string title, std::string* activities, std::string* friends, double mood) {
    Entry(text, title);
    this->activities = activities;
    this->friends = friends;
    this->mood = mood;
}

EntryPerso::~EntryPerso() {
    delete activities;
    delete friends;
}

std::string* EntryPerso::get_activities() {
    return activities;
}

void EntryPerso::set_activities(std::string* activities) {
    this->activities = activities;
}

std::string* EntryPerso::get_friends() {
    return friends;
}

void EntryPerso::set_friends(std::string* friends) {
    this->friends = friends;
}

double EntryPerso::get_mood() {
    return mood;
}

void EntryPerso::set_mood(double mood) {
    this->mood = mood;
}

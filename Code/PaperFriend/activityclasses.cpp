#include "activityclasses.h"

#include <iostream>
#include <string>


Activity::Activity() : name(""), value(0) {}

Activity::Activity(std::string name, int value) : name(name), value(value) {}

Activity::~Activity() {}

std::string Activity::get_name() const {
    return name;
}

void Activity::set_name(std::string name) {
    this->name=name;
}

double Activity::get_value() const {
    return value;
}

void Activity::set_value(double value) {
    this->value=value;
}

int Activity::get_type() const{
    return type;
}

void Activity::set_type(int type){
    this->type = type;
}

/*
ActivitySport::ActivitySport() : Activity() {}

ActivitySport::ActivitySport(std::string name, int duration) : Activity(name, duration) {}

ActivitySport::~ActivitySport() {}


ActivitySpiritual::ActivitySpiritual() : Activity() {}

ActivitySpiritual::ActivitySpiritual(std::string name, int duration) : Activity(name, duration) {}

ActivitySpiritual::~ActivitySpiritual() {}


ActivityWork::ActivityWork() : Activity() {}

ActivityWork::ActivityWork(std::string name, int duration) : Activity(name, duration) {}

ActivityWork::~ActivityWork() {}


ActivityStudy::ActivityStudy() : Activity() {}

ActivityStudy::ActivityStudy(std::string name, int duration) : Activity(name, duration) {}

ActivityStudy::~ActivityStudy() {}


ActivityArt::ActivityArt() : Activity() {}

ActivityArt::ActivityArt(std::string name, int duration) : Activity(name, duration) {}

ActivityArt::~ActivityArt() {}
*/

#include "activityclasses.h"

#include <iostream>
#include <string>


Activity::Activity() : name(""), duration(0) {}

Activity::Activity(std::string name, int duration) : name(name), duration(duration) {}

Activity::~Activity() {}

std::string Activity::get_name() const {
    return name;
}

void Activity::set_name(std::string name) {
    this->name=name;
}

int Activity::get_duration() const {
    return duration;
}

void Activity::set_duration(int duration) {
    this->duration=duration;
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

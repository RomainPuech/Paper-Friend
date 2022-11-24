#include "activityclasses.h"

#include <iostream>


Activity::Activity() {
    name = "";
    duration = 0;
}

Activity::Activity(std::string name, int duration) {
    this->name = name;
    this->duration = duration;
}

std::string Activity::get_name() {
    return name;
}

void Activity::set_name(std::string name) {
    this->name=name;
}

int Activity::get_duration() {
    return duration;
}

void Activity::set_duration(int duration) {
    this->duration=duration;
}


ActivitySport::ActivitySport() {
    Activity();
}

ActivitySport::ActivitySport(std::string name, int duration) {
    ActivitySport(name, duration);
}


ActivitySpiritual::ActivitySpiritual() {
    Activity();
}

ActivitySpiritual::ActivitySpiritual(std::string name, int duration) {
    ActivitySpiritual(name, duration);
}


ActivityWork::ActivityWork() {
    Activity();
}

ActivityWork::ActivityWork(std::string name, int duration) {
    ActivityWork(name, duration);
}


ActivityStudy::ActivityStudy() {
    Activity();
}

ActivityStudy::ActivityStudy(std::string name, int duration) {
    ActivityStudy(name, duration);
}


ActivityArt::ActivityArt() {
    Activity();
}

ActivityArt::ActivityArt(std::string name, int duration) {
    ActivityArt(name, duration);
}

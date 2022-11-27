#include "friendclasses.h"

#include <iostream>
#include <string>


Friend::Friend() : name(""), duration(0) {}

Friend::Friend(std::string name, int duration) : name(name), duration(duration) {}

Friend::~Friend() {}

std::string Friend::get_name() const {
    return name;
}

void Friend::set_name(std::string name) {
    this->name=name;
}

int Friend::get_duration() const {
    return duration;
}

void Friend::set_duration(int duration) {
    this->duration=duration;
}

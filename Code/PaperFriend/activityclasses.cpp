#include "activityclasses.h"

#include <iostream>
#include <string>
#include<QString>
#include<QDebug>

Activity::Activity(std::string name, int type, double value) : name(name), type(type),value(value) {}
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

bool Activity::equal(Activity other){
    return this->name == other.name && this->type == other.type;
}

bool Activity::operator==(Activity const&other)const{
    qDebug()<<QString("== for act called,")<<QString::fromStdString(other.get_name());
    return (name == other.get_name());
}


bool operator==(const Activity& a, const Activity& b)
{
    qDebug()<<QString("outside == for act called,")<<QString::fromStdString(a.get_name());
    return (a.get_name() == b.get_name());
}

#include "cardclasses.h"

Card::Card(){
    length = 100;
    width = 100;
    border_radius = 5;
}

Card::Card(int length, int width, int border_radius){
    this->length = length;
    this->width = width;
    this->border_radius = border_radius;
}

int Card::get_length(){
    return length;
}

int Card::get_width(){
    return width;
}

int Card::get_border_radius(){
    return border_radius;
}

void Card::set_length(int length){
    this->length = length;
}

void Card::set_width(int width){
    this->width = width;
}

void Card::set_border_radius(int border_radius){
    this->border_radius = border_radius;
}

void Card::display(QPainter *painter, double x, double y){
    painter->drawRoundedRect(x, y, width, length, border_radius, border_radius);
}

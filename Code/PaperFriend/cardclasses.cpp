#include "cardclasses.h"

#include <QDate>
#include <QCalendar>

Card::Card(int border_radius, int width, int height, QString color){
    this->border_radius = border_radius;
    this->resize(width, height);
    this->rect().setHeight(height);
    this->rect().setWidth(width);
    this->background_color = color;
    this->setStyleSheet("background-color: " + color + ";");
}

int Card::get_width(){
    return this->width();
}

int Card::get_height(){
    return this->height();
}

int Card::get_border_radius(){
    return border_radius;
}

QString Card::get_background_color(){
    return background_color;
}

void Card::set_width(int width){
    this->resize(width, this->height());
    this->rect().setWidth(width);
}

void Card::set_height(int height){
    this->resize(this->width(), height);
    this->rect().setHeight(height);
}

void Card::set_border_radius(int border_radius){
    this->border_radius = border_radius;
}

void Card::set_background_color(QString color){
    this->background_color = color;
}

void Card::display(QWidget *parent){
    QPainterPath path;
    path.addRoundedRect(this->rect(), border_radius, border_radius);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    this->setMask(mask);
    this->setParent(parent);
}

EntryCard::EntryCard(Entry *entry){
    this->entry = entry;
    QDate today = QDate::currentDate();
    int day_int = entry->get_date().dayOfWeek();
    QString day_string;
    switch(day_int){
    case 1:
        day_string = "Mon"; break;
    case 2:
        day_string = "Tue"; break;
    case 3:
        day_string = "Wed"; break;
    case 4:
        day_string = "Thu"; break;
    case 5:
        day_string = "Fri"; break;
    case 6:
        day_string = "Sat"; break;
    case 7:
        day_string = "Sun"; break;
    }
    int days_ago = entry->get_date().daysTo(today);
    date_display = new QLabel(this);
    date_display->setText(day_string + " - " + QString::number(days_ago) + " days ago");
}

EntryCard::~EntryCard(){
    delete entry;
}

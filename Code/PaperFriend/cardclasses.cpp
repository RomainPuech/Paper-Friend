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

QString generate_date_string(QDate date){
    /* Using the date of the entry generates the QString of the form
     * 'Day - dd days ago
     * date of the entry '
     */
    QDate today = QDate::currentDate();
    int day_int = date.dayOfWeek();
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

    int days_ago = date.daysTo(today);
    QString days_ago_string;
    if(days_ago % 100 == 1){
        days_ago_string = " day ago \n";
    }
    else{
        days_ago_string = " days ago \n";
    }

    return day_string + " - " + QString::number(days_ago) + days_ago_string + date.toString("MM-dd-yyyy");
}

void generate_rgb(QString &red, QString &green, double m){
    if(m <= 0.5){
        red = QString::number(255);
        green = QString::number(255 * m / (1-m));
    }
    else{
        green = QString::number(255);
        red = QString::number(255 * (1-m) / m);
    }
}

EntryCard::EntryCard(int border_radius, int width, int height, QString color, EntryPerso *entry) : Card(border_radius, width, height, color){
    this->entry = entry;

    // display date
    date_display = new QLabel();
    date_display->setFixedWidth(this->get_width() / 2); // to be changed depending on the number of widgets
    date_display->setFixedHeight(50);
    date_display->setText(generate_date_string(entry->get_date()));
    date_display->setAlignment(Qt::AlignCenter);
    date_display->setStyleSheet("font: 12px; font-weight: bold; background-color: aqua;");

    // display activities and friends
    // te be implemented

    //display mood
    mood_display = new QLabel();
    mood_display->setText("Mood: " + QString::number(entry->get_mood() * 100) + "%");
    mood_display->setFixedWidth(this->get_width() / 2); // to be changed depending on the number of widgets
    mood_display->setFixedHeight(50);
    mood_display->setAlignment(Qt::AlignCenter);
    QString red, green;
    generate_rgb(red, green, entry->get_mood());
    mood_display->setStyleSheet("font: 12px; font-weight: bold; background-color: rgb(" + red + ", " + green + ", 0);");


    //top menu
    top_menu = new QHBoxLayout(this);
    top_menu->setAlignment(Qt::AlignTop);
    top_menu->setSpacing(0);
    top_menu->addWidget(date_display);
    top_menu->addWidget(mood_display);

}

EntryCard::~EntryCard(){
    delete entry;
    delete date_display;
    delete mood_display;
    delete top_menu;
}

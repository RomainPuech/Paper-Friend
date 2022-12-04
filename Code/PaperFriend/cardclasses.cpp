#include "cardclasses.h"

#include <QDate>
#include <QCalendar>

Card::Card(int border_radius, int width, int height, QString color) : border_radius(border_radius), background_color(color){
    this->resize(width, height);
    this->rect().setHeight(height);
    this->rect().setWidth(width);
    this->setStyleSheet("background-color: " + color + ";");
    vb_layout = new QVBoxLayout(this);
    vb_layout->setContentsMargins(0, 0, 0, 0);
    vb_layout->setSpacing(0);
    this->setLayout(vb_layout);
}

Card::~Card(){
    delete vb_layout;
}

int Card::get_width() const{
    return this->width();
}

int Card::get_height() const{
    return this->height();
}

int Card::get_border_radius() const{
    return border_radius;
}

QString Card::get_background_color() const{
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

void Card::display(QLayout *layout){
    /*QPainterPath path;
    path.addRoundedRect(this->rect(), border_radius, border_radius);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    this->setMask(mask);
    //QGraphicsView *gv = new QGraphicsView();
    //this->setParent(gv);
    //layout->addWidget(gv);*/

    layout->addWidget(this);

}

QString generate_date_string(std::string date_string){
    /* Using the date of the entry generates the QString of the form
     * 'Day - dd days ago
     * date of the entry '
     */

    //convert date_string to QDate object date
    int month = std::stoi(date_string.substr(0, 2));
    int day = std::stoi(date_string.substr(3, 2));
    int year = std::stoi(date_string.substr(6, 4));
    QDate date = QDate(year, month, day);

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
    default:
        day_string = QString::number(day_int); break;
    }

    QDate today = QDate::currentDate();
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
    /* Associate a color on a scale from red to green
     * according to the mood parameter
     */
    if(m <= 0.5){
        red = QString::number(255);
        green = QString::number(255 * m / (1-m));
    }
    else{
        green = QString::number(255);
        red = QString::number(255 * (1-m) / m);
    }
}

EntryCard::EntryCard(int border_radius, int width, int height, QString color, Entry *entry) : Card(border_radius, width, height, color), entry(entry){
    entry_perso = nullptr;
    if(static_cast<EntryPerso*>(entry) != nullptr){
        entry_perso = static_cast<EntryPerso*>(entry);
    }
    // display date
    date_display = new QLabel();
    date_display->setMinimumWidth(this->get_width() / 3); // to be changed depending on the number of widgets
    date_display->setMaximumHeight(40);
    date_display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    date_display->setText(generate_date_string(entry->get_date()));
    date_display->setAlignment(Qt::AlignCenter);
    date_display->setStyleSheet("font-weight: bold; border: 1px solid;");

    //entry text and title
    text_title_vb = new QVBoxLayout(this);
    text_title_w = new QWidget(this);
    text_title_w->setStyleSheet("border: 1px solid black;");

    title = new QLabel(QString::fromStdString(entry->get_title()), text_title_w);
    title->setMinimumHeight(40);
    title->setMinimumWidth(this->get_width());
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    title->setAlignment(Qt::AlignLeft);
    title->setStyleSheet("font: 18px; font-weight: bold; border-style: none;");
    title->setContentsMargins(5, 10, 5, 0);

    text_field = new QTextEdit(QString::fromStdString(entry->get_text()), text_title_w);
    text_field->setMinimumWidth(this->get_width());
    text_field->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    text_field->setAlignment(Qt::AlignLeft);
    text_field->setStyleSheet("font: 14px; border-style: none;");
    text_field->setReadOnly(true);
    text_field->setContentsMargins(10, 0, 10, 5);

    text_title_vb->addWidget(title);
    text_title_vb->addWidget(text_field);
    text_title_w->setLayout(text_title_vb);


    //top menu
    top_menu = new QHBoxLayout(this);
    top_menu->setAlignment(Qt::AlignTop);
    top_menu->setSpacing(0);
    date_display->setParent(this);
    top_menu->addWidget(date_display);

    //display specific for entryPerso
    if(entry_perso != nullptr){

        // display activities and friends
        fr_act_display = new QListWidget(this);
        fr_act_display->setMinimumWidth(this->get_width() / 3); // to be changed depending on the number of widgets
        fr_act_display->setMaximumHeight(40);
        fr_act_display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        fr_act_display->setStyleSheet("font-weight: bold; border: 1px solid;");
        fr_act_labels = new QLabel[15]; // to be adjusted to store all friends and activities
        fr_act_display->addItem(QString::fromStdString(entry_perso->get_friends()->get_name()));
        fr_act_display->addItem(QString::fromStdString(entry_perso->get_activities()->get_name()));

        //display mood
        mood_display = new QLabel();
        mood_display->setText("Mood: " + QString::number(std::round(entry_perso->get_mood() * 100)) + "%");
        mood_display->setMinimumWidth(this->get_width() / 3); // to be changed depending on the number of widgets
        mood_display->setMaximumHeight(40);
        mood_display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        mood_display->setAlignment(Qt::AlignCenter);
        QString red, green;
        generate_rgb(red, green, entry_perso->get_mood());
        mood_display->setStyleSheet("font-weight: bold; color: rgb(" + red + ", " + green + ", 0); border: 1px solid;");


        // top menu
        fr_act_display->setParent(this);
        top_menu->addWidget(fr_act_display);
        mood_display->setParent(this);
        top_menu->addWidget(mood_display);

    }

    //add to the layout
    vb_layout->addItem(top_menu);
    vb_layout->addWidget(text_title_w);
    this->setLayout(vb_layout);
}

EntryCard::~EntryCard(){
    delete entry;
    delete date_display;
    delete mood_display;
    delete fr_act_display;
    delete fr_act_labels;
    delete top_menu;
    delete title;
    delete text_field;
    delete text_title_vb;
    delete text_title_w;
    delete entry_perso;
}

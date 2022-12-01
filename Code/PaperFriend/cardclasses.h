#ifndef CARDCLASSES_H
#define CARDCLASSES_H

#include "entryclasses.h"

#include <QWidget>
#include <QPainterPath>
#include <QRegion>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsView>

class Card : public QWidget{
public:
    Card(int border_radius = 15, int width = 200, int height = 200, QString color = "beige");
    ~Card(){};

    int get_border_radius() const;
    int get_width() const;
    int get_height() const;
    QString get_background_color() const;

    void set_border_radius(int border_radius);
    void set_width(int width);
    void set_height(int height);
    void set_background_color(QString color);

    virtual void display(QLayout *layout)
    /*
    * A funtion for displaying the Card object on the screen
    * provided a parent widget
    */;

private:
    int border_radius; // the radius of the rounded borders, default value: 15
    QString background_color; // default color: beige
};

class EntryCard : public Card{
public:
    EntryCard(int border_radius = 15, int width = 200, int height = 200, QString color = "beige", EntryPerso *entry = nullptr);
    ~EntryCard();

private:
    EntryPerso *entry;
    QHBoxLayout *top_menu;
    QLabel *date_display;
    QLabel *mood_display;
    QGraphicsView *fr_act_display;
    QLabel *fr_act_labels;
    QFrame *v_line, *v_line1;
};

#endif // CARDCLASSES_H

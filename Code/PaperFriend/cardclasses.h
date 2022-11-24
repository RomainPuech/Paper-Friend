#ifndef CARDCLASSES_H
#define CARDCLASSES_H

#include <QGraphicsItem>
#include <QWidget>
#include <QPainter>

class Card : public QGraphicsItem{
public:
    Card();
    Card(int length, int width, int border_radius);
    ~Card(){};

    int get_length();
    int get_width();
    int get_border_radius();

    void set_length(int length);
    void set_width(int width);
    void set_border_radius(int border_radius);

    virtual void display(QPainter *painter, double x, double y)
    /*
    * A funtion for displaying the Card object on the screen
    * at position (x, y), using a provided QPainter object
    */;

private:
    int length, width; // default values: 100 and 100
    int border_radius; // the radius of the rounded borders, default value: 5
};

class EntryCard : public Card{
public:
    EntryCard(){};
    ~EntryCard(){};



};

#endif // CARDCLASSES_H

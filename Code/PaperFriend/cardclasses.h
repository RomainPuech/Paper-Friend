#ifndef CARDCLASSES_H
#define CARDCLASSES_H

#include <QGraphicsItem>
#include <QWidget>

class Card : public QGraphicsItem{
public:
    Card();
    ~Card(){};

    int get_length();
    int get_width();
    int get_border_radius();

    void set_length(int length);
    void set_width(int width);
    void set_border_radius(int border_radius);

    virtual void display(){};

private:
    int length, width;
    int border_radius; // the radius of the rounded borders
};

#endif // CARDCLASSES_H

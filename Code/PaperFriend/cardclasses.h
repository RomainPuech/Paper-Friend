#ifndef CARDCLASSES_H
#define CARDCLASSES_H
#include <QWidget>
#include <QPainterPath>
#include <QRegion>
#include <QString>

class Card : public QWidget{
public:
    Card(int border_radius = 15, int width = 200, int height = 200, QString color = "beige");
    ~Card(){};

    int get_border_radius();
    int get_width();
    int get_height();
    QString get_background_color();

    void set_border_radius(int border_radius);
    void set_width(int width);
    void set_height(int height);
    void set_background_color(QString color);

    virtual void display(QWidget *parent)
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
    EntryCard(){};
    ~EntryCard(){};



};

#endif // CARDCLASSES_H

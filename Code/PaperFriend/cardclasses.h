#ifndef CARDCLASSES_H
#define CARDCLASSES_H

#include "entryclasses.h"

#include <QWidget>
#include <QPainterPath>
#include <QRegion>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>

class Card : public QWidget{
public:
    Card(int border_radius = 15, int width = 200, int height = 200, QString color = "white");
    ~Card();

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

protected:
    QVBoxLayout *vb_layout;

private:
    int border_radius; // the radius of the rounded borders, default value: 15
    QString background_color; // default color: white
};

class EntryCard : public Card{
public:
    EntryCard(int border_radius = 15, int width = 200, int height = 200, QString color = "white", Entry *entry = nullptr);
    ~EntryCard();

private:
    Entry *entry;
    EntryPerso *entry_perso;
    QHBoxLayout *top_menu;
    QLabel *date_display;
    QLabel *mood_display;
    QListWidget *fr_act_display;
    QLabel *fr_act_labels;
    QLabel *title;
    QTextEdit *text_field;
    QWidget *text_title_w;
    QVBoxLayout *text_title_vb;
};

#endif // CARDCLASSES_H

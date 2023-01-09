#ifndef CARDCLASSES_H
#define CARDCLASSES_H

#include "entryclasses.h"
#include "entryrecap.h"
#include "texteditor.h"
#include "file_processing/file_processing/file_save_and_load.h"

#include <QWidget>
#include <QPainterPath>
#include <QRegion>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QSlider>
#include <QCheckBox>
#include <QScrollArea>

class Card : public QFrame{
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
    EntryCard(int border_radius = 15, int width = 200, int height = 200, QString color = "white", Entry *entry = nullptr, bool readOnly = true, MainWindow *main_window = nullptr);
    ~EntryCard();

    void change();

    void display(QLayout *layout = nullptr);

    bool isReadOnly();
    void setReadOnly(bool readOnly);
    void set_main_window(MainWindow *mw);
    void update();
    void set_entryPerso_style(int top_menu_num_items = 3);
    void update_fr_act_select();
    void update_fr_act();

private slots:
  void handleModify();
  void handleBack();

private:
    bool readOnly;
    MainWindow *main_window;
    Entry *entry;
    EntryPerso *entry_perso;
    EntryRecap *entry_recap;
    // display of entry_perso
    QHBoxLayout *top_menu;
    QLabel *date_display;
    QLabel *mood_display;
    QListWidget *fr_act_display;
    QLabel *title;
    QTextEdit *text_field;
    QWidget *text_title_w; // widget for title, text_field and modify
    QVBoxLayout *text_title_vb; // handles the layout of text_title_w
    TextEditor *edit_text;
    QStackedWidget *edit_text_w; // contains only the text editor
    QGroupBox *edit_and_return; // contains text editor and back_to_display
    QVBoxLayout *edit_vb; // layout for edit_and_return
    QPushButton *modify;
    QPushButton *back_to_display;
    QLayout *display_layout; // parent layout of the card
    QWidget *mood_slider_w; // widget for displaying mood slider
    QLabel *mood_slider_instr; // label for the mood slider
    QSlider *mood_slider;
    QVBoxLayout *mood_slider_vb; // layout of mood_slider_w;
    QListWidget *fr_act_select;
    static std::vector<QListWidgetItem*> fr_act_options;

    QWidget *sleep_slider_w; 
    QLabel *sleep_slider_instr; 
    QSlider *sleep_slider;
    QVBoxLayout *sleep_slider_vb; 
    QWidget *eating_slider_w; 
    QLabel *eating_slider_instr;
    QSlider *eating_slider;
    QVBoxLayout *eating_slider_vb;
    //productivity_slider_w
    QWidget *productivity_slider_w;
    QLabel *productivity_slider_instr;
    QSlider *productivity_slider;
    QVBoxLayout *productivity_slider_vb;
    //communications_slider_w
    QWidget *communications_slider_w;
    QLabel *communications_slider_instr;
    QSlider *communications_slider;
    QVBoxLayout *communications_slider_vb;
    //screen time
    QWidget *screen_slider_w;
    QLabel *screen_slider_instr;
    QSlider *screen_slider;
    QVBoxLayout *screen_slider_vb;


    //display of entry_recap
    QLabel *recap_title;
    QTextEdit *message;
    QLabel *avg_mood;
    QWidget *mood_msg;
    QHBoxLayout *mood_msg_hb;
    QLabel *best_title;
    QLabel *worst_title;
    QLabel *best_date;
    QLabel *worst_date;
    QLabel *best_mood;
    QLabel *worst_mood;
    QHBoxLayout *recap_days_hb;
    QVBoxLayout *best_day_vb;
    QVBoxLayout *worst_day_vb;
    QVBoxLayout *recap_layout;
};

#endif // CARDCLASSES_H

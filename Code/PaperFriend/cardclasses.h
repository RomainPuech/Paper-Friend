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
#include <QComboBox>

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

    bool eventFilter(QObject* target, QEvent *e); // to prevent mouse scrolling

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
    void set_entryRecap_style();
    void update_fr_act_select();
    void update_fr_act();
    void remove_non_existent_act();
    void update_settings();
    void set_correct_style();

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
    QWidget *title_container;
    QHBoxLayout *title_layout;
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
    QWidget *productivity_slider_w;
    QLabel *productivity_slider_instr;
    QSlider *productivity_slider;
    QVBoxLayout *productivity_slider_vb;
    QWidget *socializing_slider_w;
    QLabel *socializing_slider_instr;
    QSlider *socializing_slider;
    QVBoxLayout *socializing_slider_vb;
    QWidget *physical_activity_slider_w;
    QLabel *physical_activity_slider_instr;
    QSlider *physical_activity_slider;
    QVBoxLayout *physical_activity_slider_vb;
    QVBoxLayout *sliders_left;
    QVBoxLayout *sliders_right;
    QHBoxLayout *sliders;
    QComboBox *habits_display;
    QListView *habits_view;

    //display of entry_recap
    QLabel *recap_title;
    QTextEdit *recap_text;
    QHBoxLayout *best_day_hb;
    QHBoxLayout *worst_day_hb;
    QLabel *best_day;
    QLabel *worst_day;
    QLabel *best_date;
    QLabel *worst_date;
    QLabel *best_mood;
    QLabel *worst_mood;
};

#endif // CARDCLASSES_H

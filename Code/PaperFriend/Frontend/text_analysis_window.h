#ifndef TEXT_ANALYSIS_WINDOW_H
#define TEXT_ANALYSIS_WINDOW_H
#pragma once
#include "cardclasses.h"
#include "Analysis/textanalysis.h"

#include <QTextEdit>
#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QThread>


namespace Ui {
class text_analysis_window;
}

class text_analysis_window : public QMainWindow {

  Q_OBJECT

public:
    text_analysis_window(EntryCard *card);
    ~text_analysis_window();
    void set_message();
    void set_mood(double mood){this->mood = mood;}
    void start();

private slots:
    void on_apply_mood_clicked();

private:
    QString text_to_analize;
    QTextEdit* message;
    EntryCard *card;
    Ui::text_analysis_window *ui;
    QLabel* load_container;
    QMovie* movie;
    double mood;

};

class WindowThread : public QThread{

public:
    WindowThread(text_analysis_window* window) : QThread(), window(window){};

    void run();
private:
    text_analysis_window* window;
};

#endif // TEXT_ANALYSIS_WINDOW_H

#ifndef TEXT_ANALYSIS_WINDOW_H
#define TEXT_ANALYSIS_WINDOW_H
#pragma once
#include "cardclasses.h"
#include "Analysis/textanalysis.h"

#include <QTextEdit>
#include <QMainWindow>
#include <QMovie>
#include <QLabel>


namespace Ui {
class text_analysis_window;
}

class text_analysis_window : public QMainWindow {

  Q_OBJECT

public:
    text_analysis_window(QString text_to_analize = "", double mood = 0, EntryCard *card = nullptr);
    ~text_analysis_window();
    void set_message(QString message);
    void analize();
    double get_mood(){return mood;}
    void set(QString text);

private slots:
    void on_apply_mood_clicked();

private:
    QString text_to_analize;
    QTextEdit* message;
    EntryCard *card;
    Ui::text_analysis_window *ui;
    TextAnalysis* analize_text;
    QLabel* load_container;
    QMovie* movie;
    double mood;
    bool open;

};

#endif // TEXT_ANALYSIS_WINDOW_H

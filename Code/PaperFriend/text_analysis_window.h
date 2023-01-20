#ifndef TEXT_ANALYSIS_WINDOW_H
#define TEXT_ANALYSIS_WINDOW_H
#include "entryclasses.h"
#include "cardclasses.h"

#include <QTextEdit>
#include <QDialog>


namespace Ui {
class text_analysis_window;
}

class text_analysis_window : public QDialog {

  Q_OBJECT

public:
    text_analysis_window(double mood, EntryCard* card, QWidget* parent = nullptr);
    ~text_analysis_window();
    void set_message(QString message);
private slots:
    void on_apply_mood_clicked(bool checked);

private:
    double mood;
    EntryCard* card;
    QTextEdit* message;
    Ui::text_analysis_window *ui;

};

#endif // TEXT_ANALYSIS_WINDOW_H

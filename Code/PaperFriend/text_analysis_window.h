#ifndef TEXT_ANALYSIS_WINDOW_H
#define TEXT_ANALYSIS_WINDOW_H

#include <QTextEdit>
#include <QDialog>


namespace Ui {
class text_analysis_window;
}

class text_analysis_window : public QDialog {

  Q_OBJECT

public:
    text_analysis_window(QWidget* parent = nullptr);
    ~text_analysis_window();
    void set_message(QString message);
private:
    QTextEdit* message;
    Ui::text_analysis_window *ui;

};

#endif // TEXT_ANALYSIS_WINDOW_H

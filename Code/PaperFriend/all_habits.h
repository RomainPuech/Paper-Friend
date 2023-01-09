#ifndef ALL_HABITS_H
#define ALL_HABITS_H

#include <QDialog>

namespace Ui {
class All_Habits;
}

class All_Habits : public QDialog
{
    Q_OBJECT

public:
    explicit All_Habits(QWidget *parent = nullptr);
    ~All_Habits();

private:
    Ui::All_Habits *ui;
};

#endif // ALL_HABITS_H

#ifndef ALL_ACTIVITIES_H
#define ALL_ACTIVITIES_H

#include <QDialog>

namespace Ui {
class all_activities;
}

class all_activities : public QDialog
{
    Q_OBJECT

public:
    explicit all_activities(QWidget *parent = nullptr);
    ~all_activities();

private:
    Ui::all_activities *ui;
};

#endif // ALL_ACTIVITIES_H

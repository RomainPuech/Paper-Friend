#include "all_habits.h"
#include "qevent.h"
#include "ui_all_habits.h"
#include <QLabel>
#include <QVBoxLayout>

#include "file_processing/file_processing/file_save_and_load.h"

All_Habits::All_Habits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::All_Habits)
{
    ui->setupUi(this);
    std::vector<QStringList> current_habits = load_habits();
    for (int i = 0; i < current_habits.size(); i++) {
        ui->all_habits_label->setText(ui->all_habits_label->text() + "\n" + current_habits[i][0] + ", " + current_habits[i][1]);
    }
    ui->all_habits_label->adjustSize();
}

All_Habits::~All_Habits()
{
    delete ui;
}
void All_Habits::closeEvent (QCloseEvent *event){
    event -> accept();
    QWidget *parent = this->parentWidget();
    parent->showMaximized();
}

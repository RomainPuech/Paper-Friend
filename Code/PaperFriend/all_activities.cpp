#include "all_activities.h"
#include "ui_all_activities.h"

all_activities::all_activities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::all_activities)
{
    ui->setupUi(this);
}

all_activities::~all_activities()
{
    delete ui;
}

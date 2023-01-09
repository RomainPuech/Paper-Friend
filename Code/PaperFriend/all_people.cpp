#include "all_people.h"
#include "ui_all_people.h"
#include "friendclasses.h"
#include "mainwindow.h"
#include<QFile>
#include <QMessageBox>

all_people::all_people(std::vector<Friend>vector_friends,
                       QWidget *parent) :
    vector_friends(vector_friends),
    QDialog(parent),
    ui(new Ui::all_people)
{
    ui->setupUi(this);
}

all_people::~all_people()
{
    delete ui;
}

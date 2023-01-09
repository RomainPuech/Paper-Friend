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

void all_people::on_add_people_button_clicked()
{
    addNewCell();
}

void all_people::addNewCell(QString cellText, QString cellName, int type){
    people_cell *new_person_cell = new people_cell(this); // Create a new people_cell.
    ui->people_cell_layout->addWidget(new_person_cell); // add a widget in the people_cell_layout.
    connect(new_person_cell, SIGNAL(closeThisCell(int)),this,SLOT(closeCell(int)));
    new_person_cell->setAttribute(Qt::WA_DeleteOnClose, true); // here we set an attribute so whenever we close the cell it is indeed deleted.
    new_person_cell->PersonCellNumber = PersonCellNumberTotal; // here in the new_person_cell I defined the person cell number to be equal to the total person cell number.
    new_person_cell->set_person_cell_name(cellName);
    PersonallCellPtr.append(new_person_cell); // here I append this new persson cell to the data vector.
    new_person_cell->set_person_type(type);
    vector_friends.push_back(Friend(cellName.toStdString(), type, 0));
    PersonCellNumberTotal++; // the total number of person is incremented by 1.
}

void all_people::on_save_people_button_clicked()
{

}


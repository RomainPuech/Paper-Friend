#include "all_people.h"
#include "ui_all_people.h"
#include "friendclasses.h"
#include "people_cell.h"
#include "mainwindow.h"
#include<QFile>
#include <QMessageBox>

all_people::all_people(std::vector<Friend>
                       &vector_friend, QWidget *parent) :
    vector_friends(vector_friend),
    QDialog(parent),
    ui(new Ui::all_people)
{
    ui->setupUi(this);
    int PersonCellNumberTotal = 0;
    this->add_previous_cells();
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

void all_people::add_previous_cells(){
    for(long long unsigned i = 0; i< vector_friends.size(); i++){
        addNewCell("", QString::fromStdString(vector_friends.at(i).get_name()), vector_friends.at(i).get_type());
        vector_friends.pop_back();
    }

}

void all_people::closeCell(int PersonCellNumber){
    PersonallCellPtr[PersonCellNumber]->close();
    for(int i=PersonCellNumber+1; i<PersonallCellPtr.length(); i++){
        PersonallCellPtr[i]->PersonCellNumber--;
    }
    PersonCellNumberTotal--;
    PersonallCellPtr.remove(PersonCellNumber);
}

void all_people::on_save_people_button_clicked()
{
    QFile activities_file("./people.txt");
    activities_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QApplication::processEvents();
    QString name_person;
    int type_person;
    vector_friends.clear();
    for(int i=0;i<PersonallCellPtr.size();++i){
        name_person = PersonallCellPtr[i]->get_person_name();
        type_person = PersonallCellPtr[i]->get_person_type();
        qDebug()<< name_person<<type_person;
        QTextStream out(&activities_file);
        vector_friends.push_back(Friend(name_person.toStdString(),type_person,0));
        out << name_person << " , " << type_person << "⧵n";
    }
    save_friends(vector_friends);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, "Save Confirmation", "All your people are saved.",QMessageBox::Ok);
    if (reply == QMessageBox::Ok){
        this->close();
        }
}

void all_people::closeEvent (QCloseEvent *event){
    if(PersonallCellPtr.size() != vector_friends.size()){
        QMessageBox::StandardButton answr_btn = QMessageBox::warning( this, tr("Paper friend"), tr("Have you saved your people ?"),
                                                                      QMessageBox::Yes | QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

        if (answr_btn != QMessageBox::Yes) {
            event->ignore();
        } else {
            this->close();
        }
    }else{
        for(int i=0; i<PersonallCellPtr.size();++i){
            QString name_person_acp;
            name_person_acp = PersonallCellPtr[i]->get_person_name();
            std::string name_person_vec;
            name_person_vec = vector_friends[i].get_name();
            int type_person_acp;
            type_person_acp = PersonallCellPtr[i]->get_person_type();
            int type_person_vec;
            type_person_vec = vector_friends[i].get_type();
            if(name_person_acp.toStdString() != name_person_vec || type_person_acp != type_person_vec ){
                QMessageBox::StandardButton answr_btn = QMessageBox::warning( this, tr("Paper friend"), tr("Have you saved your people ?"),
                                                                              QMessageBox::Yes | QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

                if (answr_btn != QMessageBox::Yes) {
                    event->ignore();
                } else {
                    event->ignore();
                }
            }if(type_person_acp == 0){
                QMessageBox::StandardButton answr_btn = QMessageBox::warning( this, tr("Paper friend"), tr("Please enter a person category."),
                                                                              QMessageBox::Yes | QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

                if (answr_btn != QMessageBox::Yes) {
                    event->ignore();
                } else {
                    event->ignore();
                }
            }if(name_person_acp.toStdString() == "Person name"){
                QMessageBox::StandardButton answr_btn = QMessageBox::warning( this, tr("Paper friend"), tr("Please enter the person's name."),
                                                                              QMessageBox::Yes | QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

                if (answr_btn != QMessageBox::Yes) {
                    event->ignore();
                } else {
                    event->ignore();
                }
            }
        }
    }
}



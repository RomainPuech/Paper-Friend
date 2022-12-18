#include "all_activities.h"
#include"activity_cell.h"
#include "ui_all_activities.h"
#include<QFile>
#include"activityclasses.h"

int all_activities::ActivitiesCellNumberTotal = 0;
QVector<activity_cell *> all_activities::allCellPtr;

all_activities::all_activities(std::vector<Activity> &vector_activity,QWidget *parent) :
    vector_activities(vector_activity),
    QDialog(parent),
    ui(new Ui::all_activities)
{
    ui->setupUi(this);
    //ActivitiesCellNumberTotal=0;
}

all_activities::~all_activities()
{
    delete ui;
}

void all_activities::on_add_activity_button_clicked()
{
    addNewCell();
}

void all_activities::addNewCell(QString cellText, QString cellName)
{
    activity_cell *new_activity_cell = new activity_cell(this); // Create a new activity_cell.
    ui->activities_cell_layout->addWidget(new_activity_cell); // add a widget in the activities_cell_layout.
    connect(new_activity_cell, SIGNAL(closeThisCell(int)),this,SLOT(closeCell(int)));
    new_activity_cell->setAttribute(Qt::WA_DeleteOnClose, true); // here we set an attribute so whenever we close the cell it is indeed deleted.
    new_activity_cell->ActivitiesCellNumber = ActivitiesCellNumberTotal; // here in the new_activity_cell I defined the activity cell number to be equal to the total activities cell number.
    //new_activity_cell->setTextData(cellText); // this line set the text.
    new_activity_cell->set_activity_cell_name(cellName);
    allCellPtr.append(new_activity_cell); // here I append this new activity cell to the data vector.
    ActivitiesCellNumberTotal++; // the total number of activities is incremented by 1.
}

void all_activities::add_previous_cells(){
    for(int i=0; i < allCellPtr.size(); i++){
        allCellPtr.at(i)->setParent(this); // set the new window to be the parent
        ui->activities_cell_layout->addWidget(allCellPtr.at(i));
    }
}

void all_activities::closeCell(int ActivitiesCellNumber){
    allCellPtr[ActivitiesCellNumber]->close();
    for(int i=ActivitiesCellNumber+1; i<allCellPtr.length(); i++){
        allCellPtr[i]->ActivitiesCellNumber--;
    }
    ActivitiesCellNumberTotal--;
    allCellPtr.remove(ActivitiesCellNumber);
}

void all_activities::on_save_activity_button_clicked()
{
    QFile activities_file("./activities.txt");
    activities_file.open(QIODevice::WriteOnly | QIODevice::Text); //Opens activities_file and allow to write in the text file.
    QApplication::processEvents();
    QString name_activity;
    int type_activity;
    for(int i=0;i<allCellPtr.size();++i){
        name_activity = allCellPtr[i]->get_activity_name();
        type_activity = allCellPtr[i]->get_activity_type();
        qDebug()<< name_activity<<type_activity;
        QTextStream out(&activities_file);
        vector_activities.push_back(Activity(name_activity.toStdString(),type_activity,0));
        out << name_activity << " , " << type_activity << "⧵n";
    }
}



#include "people_cell.h"
#include "ui_people_cell.h"

people_cell::people_cell(QWidget *parent)
    : QWidget(parent), ui(new Ui::people_cell) {
  ui->setupUi(this);
  ui->person_type->addItem("Enter person category");
  ui->person_type->addItem("Mother");
  ui->person_type->addItem("Father");
  ui->person_type->addItem("Sister");
  ui->person_type->addItem("Brother");
  ui->person_type->addItem("Cousin");
  ui->person_type->addItem("Best Friend");
  ui->person_type->addItem("Friend");
  ui->person_type->addItem("Colleague");
  ui->person_type->addItem("enemy");
}

people_cell::~people_cell() { delete ui; }

void people_cell::set_person_cell_name(QString cellName) {
  ui->person_name->setText(cellName);
  ui->person_name->setMaxLength(30);
}

void people_cell::set_person_type(int type) {
  ui->person_type->setCurrentIndex(type);
}

QString people_cell::get_person_name() { return ui->person_name->text(); }

int people_cell::get_person_type() { return ui->person_type->currentIndex(); }

void people_cell::on_delete_person_button_clicked() {
  QMessageBox::StandardButton reply;
  reply =
      QMessageBox::question(this, "Delete Confirmation", "Delete this person ?",
                            QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    emit closeThisCell(PersonCellNumber);
    this->close();
  }
}

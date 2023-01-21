#include "activity_cell.h"
#include "ui_activity_cell.h"

activity_cell::activity_cell(QWidget *parent)
    : QWidget(parent), ui(new Ui::activity_cell) {
  ui->setupUi(this);
  QRegularExpression regular_expression("[A-Za-z ]{0,30}");
  QRegularExpressionValidator *validator =
      new QRegularExpressionValidator(regular_expression, this);
  ui->activity_name->setValidator(validator);
  ui->activity_name->setPlaceholderText("Activity name");
  ui->activity_type->addItem("Enter type");
  ui->activity_type->addItem("Friend");
  ui->activity_type->addItem("Sport");
  ui->activity_type->addItem("Spiritual");
  ui->activity_type->addItem("Work");
  ui->activity_type->addItem("Study");
  ui->activity_type->addItem("Art");
}

activity_cell::~activity_cell() { delete ui; }

// void activity_cell::setTextData(QString cellText){
//     ui->textEdit->clear();
//     ui->textEdit->insertPlainText(cellText);  // the textEdit window will be
//     adding the text as an input.
// }

void activity_cell::set_activity_cell_name(QString cellName) {
  ui->activity_name->setText(cellName);
  ui->activity_name->setMaxLength(30);
}

void activity_cell::set_activity_type(int type) {
  ui->activity_type->setCurrentIndex(type);
}

void activity_cell::disable_change() {
  QString act_name = ui->activity_name->text();
  if (act_name != "") {
    ui->activity_name->setReadOnly(true);
  }
}

void activity_cell::on_delete_activity_button_clicked() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Delete Confirmation",
                                "Delete this activity ?",
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    nb_clicked += 1;
    emit closeThisCell(ActivitiesCellNumber);
    this->close();
  }
}

QString activity_cell::get_activity_name() { return ui->activity_name->text(); }

int activity_cell::get_activity_type() {
  return ui->activity_type->currentIndex();
}

int activity_cell::number_clicked() { return nb_clicked; }

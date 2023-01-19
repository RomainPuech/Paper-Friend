#include "error_dlg.h"
#include "ui_error_dlg.h"

error_dlg::error_dlg(QWidget *parent) : QDialog(parent), ui(new Ui::error_dlg) {
  ui->setupUi(this);
}

error_dlg::~error_dlg() { delete ui; }

// Ok button then done
void error_dlg::on_pushButton_clicked() { this->close(); }

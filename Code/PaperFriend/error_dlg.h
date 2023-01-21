#ifndef ERROR_DLG_H
#define ERROR_DLG_H

#include <QDialog>

namespace Ui {
class error_dlg;
}

class error_dlg : public QDialog {
  Q_OBJECT

public:
  explicit error_dlg(QWidget *parent = nullptr);
  ~error_dlg();
  // Ok button
  void on_pushButton_clicked();

private:
  Ui::error_dlg *ui;
};

#endif // ERROR_DLG_H

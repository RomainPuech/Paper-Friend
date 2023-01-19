#ifndef PEOPLE_CELL_H
#define PEOPLE_CELL_H

#include <QMessageBox>
#include <QString>
#include <QWidget>

namespace Ui {
class people_cell;
}

class people_cell : public QWidget {
  Q_OBJECT

public:
  explicit people_cell(QWidget *parent = nullptr);
  ~people_cell();
  int PersonCellNumber;
  QString getTextData();
  QString getCellName();
  QString get_person_name();
  int get_person_type();

  void setTextData(QString cellText);
  void set_person_cell_name(QString CellName);
  void set_person_type(int type);

private slots:
  void on_delete_person_button_clicked();

private:
  Ui::people_cell *ui;

signals:
  void closeThisCell(int);
};

#endif // PEOPLE_CELL_H

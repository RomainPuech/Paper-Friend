#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtCharts>
#include <QChartView>
#include<QLineSeries>
// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>
// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>
// Used to create a line chart
#include <QtCharts/QLineSeries>
// Used to change names on axis
#include <QtCharts/QCategoryAxis>
#include "all_habits.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    friend class TextEditor;
    class TextEditor *textEditor;
    void closeEvent (QCloseEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_settingsButton_clicked();
    void on_save_settings_clicked();
    void on_activitie_button_clicked();


private:
    void toggle_visibility(QWidget *component);
    Ui::MainWindow *ui;
    All_Habits *all_habits;
};

#endif // MAINWINDOW_H

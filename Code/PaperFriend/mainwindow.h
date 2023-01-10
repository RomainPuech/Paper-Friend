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
#include "entryclasses.h"
#include "cardclasses.h"
#include "mascotchat.h"

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
    static std::vector<Activity> get_activities();
    static Activity* get_activity_at_i(long long unsigned i);
    static std::vector<Friend> get_friends();
    static Friend* get_friend_at_i(long long unsigned i);
    static void update_activities(std::vector<Activity> activities);
    static void update_friends(std::vector<Friend> friends);
    void update_graphs();
    void remove_non_existent_activities_and_friends(EntryPerso* entry);
    void generate_recap();
    void react_to_last_entry();
    void welcome();

private slots:
    void on_pushButton_clicked();
    void on_settingsButton_clicked();
    void on_save_settings_clicked();
    void on_activitie_button_clicked();
    void on_filterButton_clicked();
    void on_newEntryButton_clicked();
    void on_clear_button_clicked();
    void on_helpFilterBox_clicked();
    void on_type_filter_currentTextChanged(const QString &);

    void on_Test_entries_clicked();

    void on_ppl_button_clicked();

private:
    MascotChat chat;
    void toggle_visibility(QWidget *component);
    void display_entries();
    void display_graph(QString tracked_parameter);
    Ui::MainWindow *ui;
    All_Habits *all_habits;
    static std::vector<EntryPerso*>vector_entries;
    static std::vector<Activity>vector_activities;
    static std::vector<Friend>vector_friends;

    std::vector<EntryPerso*> displayed_entries;
    EntryCard* today_card;

    bool reacted_to_entry; //Has the mascot reacted yet to the user's daily entry?
};

#endif // MAINWINDOW_H

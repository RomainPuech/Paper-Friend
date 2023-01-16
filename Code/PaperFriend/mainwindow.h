#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "dynamicgraph.h"
#include "all_habits.h"
#include "entryclasses.h"
#include "cardclasses.h"
#include "mascotchat.h"
#include "entryrecap.h"
#include <unordered_map>


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
    static std::vector<Friend> get_friends();
    static void update_activities(std::vector<Activity> activities);
    static void update_friends(std::vector<Friend> friends);
    static void settings_refresh(); // update display according to the settings
    void change_editability();
    void update_graphs();
    void generate_recap();
    void react_to_last_entry();
    void welcome();
    void add_new_activities_to_old_enties();
    static void remove_activities_from_old_entries(int position);

private slots:
    void on_pushButton_clicked();
    void on_settingsButton_clicked();
    void on_save_settings_clicked();
    void on_activitie_button_clicked();
    void on_filterButton_clicked();
    void on_newEntryButton_clicked();
    void on_clear_button_clicked();
    void on_type_filter_currentTextChanged(const QString &);

    void on_Test_entries_clicked();

    void on_ppl_button_clicked();

private:
    MascotChat chat;
    std::map<QString, DynamicGraph*> dynamic_graphs;
    void toggle_visibility(QWidget *component);
    void display_entries();
    void display_graph(QString tracked_parameter);
    Ui::MainWindow *ui;
    All_Habits *all_habits;
    static std::vector<EntryPerso*>vector_entries;
    static std::vector<Activity>vector_activities;
    static std::vector<Friend>vector_friends;
    static std::vector<EntryRecap*>vector_recaps;


    std::vector<EntryPerso*> displayed_entries;
    static std::vector<EntryCard*> displayed_cards; // entry perso cards that are currently on display
    EntryCard* today_card;

    bool reacted_to_entry; //Has the mascot reacted yet to the user's daily entry?

};

#endif // MAINWINDOW_H

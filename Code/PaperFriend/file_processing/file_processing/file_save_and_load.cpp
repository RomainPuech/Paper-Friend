#include "file_save_and_load.h"
#include "qdir.h"
#include <QDebug>
#include <QFile>
#include <cstdio>
#include <QApplication>
#include <QFile>
#include <QLabel>
#include <QTextStream>
#include <set>

//  create and save the entry file, title format MM.YY.JJ

bool save_entry(Entry entry) {
  nlohmann::json j = {{"text", entry.get_text()},
                      {"title", entry.get_title()},
                      {"date", entry.get_date()}};
  std::string filename =
      entry.get_qdate().toString("MM.dd.yyyy").toStdString() + ".json";

  std::ofstream o("Entries/" + filename);

  if (!o.is_open()) {
    std::cout << "Error opening file" << std::endl;
    return false;
  }
  o << j << std::endl;

  o.close();
  return true;
};

// retrieve the data of a Json file and return an
// initialized Entry object with this data
Entry load_entry(std::string filename) {
  std::ifstream i(filename);
  nlohmann::json j;
  i >> j;
  Entry res = Entry(j["text"], j["title"]);
  res.set_date(j["date"]);
  return res;
}

std::string
activity_to_string(Activity act) { // function that return a string that resume
                                   // the activities to be saved
  std::string name = act.get_name();
  std::string value = std::to_string(act.get_value());
  std::string type = std::to_string(act.get_type());
  std::string delimiter = "$*$";
  std::string delimiter2 = "*$*";
  return (name + delimiter + value + delimiter + type + delimiter2);
};

Activity string_to_activity(
    std::string
        act) { // function that takes a 'string resume' of an activity and
               // return an initialized and corresponding Activity object
  std::string delimiter = "$*$";
  std::string temp = act.substr(0, act.find(delimiter)); // extract the name
  std::string name = temp;
  act.erase(0, act.find(delimiter) + delimiter.length());
  temp = act.substr(0, act.find(delimiter)); // extract the value
  double value = std::stod(temp);
  act.erase(0, act.find(delimiter) + delimiter.length());
  temp = act.substr(0, act.find(delimiter)); // extract the type
  int type = std::stoi(temp);
  Activity res = Activity(name, value); // initialize the result
  res.set_type(type);
  return res;
};

std::string activities_vec_to_str(
    std::vector<Activity *>
        acts) { // takes a vector of pointers to activities and return a string
                // resuming all the vector (to be saved)
  std::string res;
  for (int i = 0; i < acts.size(); i++) {
    if ((*acts[i]).get_value() != 0) {
      res += activity_to_string(*acts[i]);
    }
  }
  return res;
}

std::vector<Activity *>
str_to_vec_activities(std::vector<Activity> possible_activities,
                      std::string act) { // activity vec from a string
  std::vector<Activity *> res;
  std::string delimiter = "*$*";
  size_t pos = 0;
  std::string temp;
  std::set<std::string> activities_done;
  while ((pos = act.find(delimiter)) != std::string::npos) {
    temp = act.substr(0, pos);
    Activity to_add = string_to_activity(temp);
    activities_done.insert(to_add.get_name());
    act.erase(0, pos + delimiter.length());
  }
  for (Activity const &activity : possible_activities) {
    if (activities_done.find(activity.get_name()) != activities_done.end()) {
      Activity *to_add = new Activity(activity);
      to_add->set_value(1);
      res.push_back(to_add);
    } else {
      Activity *to_add = new Activity();
      to_add->set_name(activity.get_name());
      to_add->set_type(activity.get_type());
      to_add->set_value(0.0);
      res.push_back(to_add);
    }
  }

  return res;
}

bool save_entryperso(EntryPerso entry) { //  create and save the entry file,
                                         //  title format MM.YY.JJ

  std::string activities = activities_vec_to_str(entry.get_activities());

  nlohmann::json j = {{"text", entry.get_text()},
                      {"title", entry.get_title()},
                      {"date", entry.get_date()},

                      {"mood", entry.get_mood()},
                      {"sleep", entry.get_sleep()},
                      {"eating_healthy", entry.get_eating_healthy()},
                      {"productivity", entry.get_productivity()},
                      {"socializing", entry.get_socializing()},
                      {"physical_activity", entry.get_physical_activity()},
                      {"activities", activities}};
  std::string filename =
      entry.get_qdate().toString("MM.dd.yyyy").toStdString() + ".json";

  std::filesystem::path cwd = std::filesystem::current_path();

  std::filesystem::create_directory("Entries");

  cwd /= "Entries";

  std::filesystem::path filePath = cwd / filename;

  std::ofstream o(filePath);

  if (!o.is_open()) {
    std::cout << "Error opening file" << std::endl;
    return false;
  }
  o << j << std::endl;
  o.close();
  return true;
};

EntryPerso *load_entryperso(
    std::string filename,
    std::vector<Activity>
        possible_activities) { // retrieve the data of a Json file and return an
                               // initialized Entry object with this data
  std::ifstream i("Entries/" + filename);
  nlohmann::json j;
  i >> j;
  EntryPerso *res = new EntryPerso(
      j["text"], j["title"],
      str_to_vec_activities(possible_activities, j["activities"]),
      j["mood"], j["sleep"],j["eating_healthy"], j["productivity"],
      j["socializing"], j["physical_activity"]);

  res->set_date(j["date"]);
  return res;
}

bool save_activities(
    std::vector<Activity>
        acts) { // save the std::vector of activities in a file to keep track of
                // all possible types of activities
  std::string res;
  for (int i = 0; i < acts.size(); i++) {
    res += activity_to_string(acts[i]);
  }
  nlohmann::json j = {
      {"activities", res},
  };

  std::string filename = "activities.json";

  std::ofstream o("./" + filename);

  if (!o.is_open()) {
    std::cout << "Error opening file" << std::endl;
    return false;
  }
  o << j << std::endl;

  o.close();
  return true;
}

std::vector<Activity> load_activities() { // activity vec from a string
  std::string filename = "activities.json";
  std::ifstream i(filename);
  nlohmann::json j;
  i >> j;

  std::string act = j["activities"];

  std::vector<Activity> res;
  std::string delimiter = "*$*";

  size_t pos = 0;
  std::string temp;
  while ((pos = act.find(delimiter)) != std::string::npos) {
    temp = act.substr(0, pos);
    Activity activity = string_to_activity(temp);
    res.push_back(activity);
    act.erase(0, pos + delimiter.length());
  }
  return res;
}


std::vector<QStringList> load_habits() {
  std::string habit;
  std::vector<QStringList> current_habits;
  std::ifstream myfile;
  myfile.open("habits.txt"); //We try to open our .txt file
  if (myfile.is_open()) { //If successful we continue
    std::cout << "Reading habits file" << std::endl;
    while (myfile.good()) { //iterate over each line
      QString tmp1;
      std::getline(myfile, habit);
      tmp1 = QString::fromUtf8(habit.c_str());
      QStringList tmp2 = tmp1.split('|'); //Split the line with respect to "|" (saved format is "habit_name|habit_frequency|streak|last date modified")
      current_habits.push_back(tmp2);
    }
    myfile.close();
    std::cout << "Finished reading habits file" << std::endl;
  } else {
    std::cout << "Couldn't open habits file" << std::endl;
  }
  return current_habits;  //Format is [['habit_name'],['habit_frequency'],['streak'],['last date modified]]
}

std::vector<QString> load_last_recaps_dates() {
  std::string stringdate;
  std::vector<QString> last_recaps_dates;
  std::ifstream myfile;
  myfile.open("last_recaps_dates.txt");
  if (myfile.is_open()) {
    while (myfile.good()) {
      std::getline(myfile, stringdate);
      if (stringdate == std::string("")) {
        qDebug() << QString("no recap yet");
      }
      last_recaps_dates.push_back(QString::fromStdString(stringdate));
    }
  } else {
    std::cout << "Couldn't open recap file\n";
  }
  while (last_recaps_dates.size() < 3) {
    last_recaps_dates.push_back(QString(""));
  }
  return last_recaps_dates;
}

void save_last_recaps_dates(std::vector<QString> last_recaps_dates) {
  std::ofstream myfile("last_recaps_dates.txt");
  myfile << last_recaps_dates[0].toStdString() << std::endl;
  myfile << last_recaps_dates[1].toStdString() << std::endl;
  myfile << last_recaps_dates[2].toStdString() << std::endl;
  myfile.close();
}

void save_habits_to_file(std::vector<QStringList> new_habits) {
  QFile file("habits.txt");
  if (file.exists()) { //Check if file already exists in directory.
    std::cout << "File Exists" << std::endl;
    std::ofstream myfile;
    myfile.open("habits.txt", std::ios::app); //Open the file in append mode (to add at the end of it and not overwrite the file).
    myfile << "" << std::endl; //Add std::endl to the previous line which doesnt have it.
    for (unsigned long i = 0; i < new_habits.size() - 1; i++) { //Iterate over vector of Qstring vectors, without the last one (explanation below).
      std::cout << new_habits[i][0].toStdString() << std::endl;
      myfile << new_habits[i][0].toStdString() + "|" +     //Add habit to the file.
                    new_habits[i][1].toStdString() + "|" + //Add which day repeated to the file.
                    new_habits[i][2].toStdString() + "|" + //Add number of streak (initially 0) to the file.
                    new_habits[i][3].toStdString()         //Add last day modified (initially yesterday's date) to the file.
             << std::endl;
    }
    myfile << new_habits[new_habits.size() - 1][0].toStdString() + "|" +     //Same as above but for last line.
                  new_habits[new_habits.size() - 1][1].toStdString() + "|" +
                  new_habits[new_habits.size() - 1][2].toStdString() + "|" +
                  new_habits[new_habits.size() - 1][3].toStdString();
    //I excluded the last line from the loop in order not to have std::endl in it, which would create some bugs in loading/saving other habits (empty strings!).
    myfile.close(); //Close the file.
  } else { //Create new file.
    std::cout << "Creating new habits file" << std::endl;
    std::ofstream myfile;
    myfile.open("habits.txt");
    for (unsigned long i = 0; i < new_habits.size() - 1; i++) { //Same explanation as above.
      myfile << new_habits[i][0].toStdString() + "|" +
                    new_habits[i][1].toStdString() + "|" +
                    new_habits[i][2].toStdString() + "|" +
                    new_habits[i][3].toStdString()
             << std::endl;
    }
    myfile << new_habits[new_habits.size() - 1][0].toStdString() + "|" +     //Same explanation as above.
                  new_habits[new_habits.size() - 1][1].toStdString() + "|" +
                  new_habits[new_habits.size() - 1][2].toStdString() + "|" +
                  new_habits[new_habits.size() - 1][3].toStdString();
    myfile.close(); //Close file.
  }
  file.close(); //Close file we used to check if file exists or not.
}

void resave_habits_in_new_file(std::vector<QStringList> new_habits) { //Resave function for all habits (used to save incrementation/reset of streak and the deletion of habits).
  std::ofstream myfile;
  myfile.open("habits.txt", std::ios::out); //The only main difference between this function and the previous one is that we open the file in out mode in order to over write
                                            //everything.
  for (unsigned long i = 0; i < new_habits.size() - 1; i++) {
    myfile << new_habits[i][0].toStdString() + "|" +
                  new_habits[i][1].toStdString() + "|" +
                  new_habits[i][2].toStdString() + "|" +
                  new_habits[i][3].toStdString()
           << std::endl;
  }
  myfile << new_habits[new_habits.size() - 1][0].toStdString() + "|" +
                new_habits[new_habits.size() - 1][1].toStdString() + "|" +
                new_habits[new_habits.size() - 1][2].toStdString() + "|" +
                new_habits[new_habits.size() - 1][3].toStdString();
  myfile.close();
}

int save_incrementation_of_habits(QString to_increment) { //Functions that loads previously saved habits, finds the habit to icrement its streak and uses function resave
                                                           //(in order to save the incrementation).
  std::vector<QStringList> old_habits = load_habits();
  int j;
  for (unsigned long i = 0; i < old_habits.size(); i++) {
    if (old_habits[i][0] == to_increment) {
      j = old_habits[i][2].toInt();
      j += 1;
      old_habits[i][2] = QString::number(j);
      old_habits[i][3] = QDate::currentDate().toString();
      break;
    }
  }
  resave_habits_in_new_file(old_habits);
  return j;
}

void save_reset_of_habits(QString to_reset) {//Functions that loads previously saved habits, finds the habit to reset its streak and uses function resave
                                             //(in order to save the reset).
  std::vector<QStringList> old_habits = load_habits();
  for (unsigned long i = 0; i < old_habits.size(); i++) {
    if (old_habits[i][0] == to_reset) {
      old_habits[i][2] = "0";
      old_habits[i][3] = QDate::currentDate().toString();
      break;
    }
  }
  resave_habits_in_new_file(old_habits);
}

void save_delete_of_habits(QString to_delete) { //Functions that loads previously saved habits, finds the habit to completely delete and uses function resave
                                                //(in order to completely delete it).
  std::vector<QStringList> old_habits = load_habits();
  if (old_habits.size() == 1) { //If there's only one previously saved habit, then it is for sure the one to delete, so we simply over write it empty.
    remove("habits.txt");
  } else { //Find and delete habit from vector of previously saved habits, then resave the new vector.
    for (unsigned long i = 0; i < old_habits.size(); i++) {
      if (old_habits[i][0] == to_delete) {
        old_habits.erase(old_habits.begin() + i);
        break;
      }
    }
    resave_habits_in_new_file(old_habits);
  }
}




bool save_entryrecap(EntryRecap entry){ //  create and save the entry file, title format MM.YY.JJ





    nlohmann::json  j = {
        {"date", entry.get_date()},
        {"best_day_date", entry.get_best_day_date().toString("MM.dd.yyyy").toStdString()},
        {"worst_day_date", entry.get_worst_day_date().toString("MM.dd.yyyy").toStdString()},
        {"best_day_mood", entry.get_best_day_mood()},
        {"worst_day_mood", entry.get_worst_day_mood()},
        {"text", entry.get_text()},
        {"type", entry.get_type()},
        {"average_mood", entry.get_average_mood()},

    };
    std::string filename =  entry.get_qdate().toString("MM.dd.yyyy").toStdString()+"."+std::to_string(entry.get_type())+".json";

    std::filesystem::path cwd = std::filesystem::current_path();

    std::filesystem::create_directory("Recap_entries");

    cwd /= "Recap_entries";



    std::filesystem::path filePath = cwd / filename;

    std::ofstream o( filePath);


    if(!o.is_open()){
        std::cout << "Error opening file" << std::endl;
        return false;
    }
    o << j << std::endl;
    o.close();
    return true;
}



EntryRecap* load_entryrecap(std::string filename, std::vector<Activity> possible_activities){//retrieve the data of a Json file and return a pointer to an initialized EntryRecap object with this data
    std::ifstream i("Recap_entries/" + filename);
    nlohmann::json j;
    i >> j;
    QDate best_day_date = QDate::fromString(QString::fromStdString(j["best_day_date"]), "MM.dd.yyyy");
    QDate worst_day_date = QDate::fromString(QString::fromStdString(j["worst_day_date"]), "MM.dd.yyyy");
    double best_day_mood = j["best_day_mood"];
    double worst_day_mood = j["worst_day_mood"];
    EntryRecap* res = new EntryRecap(best_day_date,worst_day_date,best_day_mood,worst_day_mood, j["text"],j["average_mood"], j["type"]);
    res->set_date(j["date"]);
    return res;
}

std::vector<QStringList> get_daily_habits() {

    QDate date = date.currentDate();
    int tmp = date.dayOfWeek(); //day of week in int format, 1 corrresponds to Monday ...
    std::string day_of_week;
    switch (tmp) { //Get the corresponding day for each i
    case 1:
      day_of_week = "Every Monday";
      break;
    case 2:
      day_of_week = "Every Tuesday";
      break;
    case 3:
      day_of_week = "Every Wednesday";
      break;
    case 4:
      day_of_week = "Every Thursday";
      break;
    case 5:
      day_of_week = "Every Friday";
      break;
    case 6:
      day_of_week = "Every Saturday";
      break;
    case 7:
      day_of_week = "Every Sunday";
      break;
    }
    std::vector<QStringList> current_habits = load_habits();
    std::vector<QStringList> habits_of_the_day;
    for (unsigned long i = 0; i < current_habits.size(); i++) { //iterate over all habits and check the ones which are done on this day
      if (QDate::currentDate().toString() != current_habits[i][3]) {
        QStringList tmp;
        if (current_habits[i][1].toStdString() == "Every Day") { //if it's every day, we always add it to our vector
          tmp.push_back(current_habits[i][0]);
          tmp.push_back(current_habits[i][1]);
          tmp.push_back(current_habits[i][2]);
        }
        if ((current_habits[i][1].toStdString() == "Every Weekday" && //if it's every weekday, we check if today's a weekday
             day_of_week == "Every Monday") ||
            (current_habits[i][1].toStdString() == "Every Weekday" &&
             day_of_week == "Every Tuesday") ||
            (current_habits[i][1].toStdString() == "Every Weekday" &&
             day_of_week == "Every Wednesday") ||
            (current_habits[i][1].toStdString() == "Every Weekday" &&
             day_of_week == "Every Thursday") ||
            (current_habits[i][1].toStdString() == "Every Weekday" &&
             day_of_week == "Every Friday")) {
          tmp.push_back(current_habits[i][0]);
          tmp.push_back(current_habits[i][1]);
          tmp.push_back(current_habits[i][2]);
        }
        if ((current_habits[i][1].toStdString() == "Every Weekend" && //Same as above but for weekends
             day_of_week == "Every Saturday") ||
            (current_habits[i][1].toStdString() == "Every Weekend" &&
             day_of_week == "Every Sunday")) {
          tmp.push_back(current_habits[i][0]);
          tmp.push_back(current_habits[i][1]);
          tmp.push_back(current_habits[i][2]);
        }
        if (current_habits[i][1].toStdString() == day_of_week) { //If it's the same as today's date
          tmp.push_back(current_habits[i][0]);
          tmp.push_back(current_habits[i][1]);
          tmp.push_back(current_habits[i][2]);
        }
        if (tmp.size() > 0) {
          habits_of_the_day.push_back(tmp);
        }
      }
    }
    return habits_of_the_day;//return vecotr of QStringList of habits done today in the format [['habit_name'],['habit_frequency'],['streak'],['last date modified]]
}


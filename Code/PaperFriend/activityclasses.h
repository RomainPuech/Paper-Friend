#ifndef ACTIVITYCLASSES_H
#define ACTIVITYCLASSES_H

#include <iostream>
#include <string>


class Activity {
public:
    Activity();
    Activity(std::string name, int value);
    ~Activity();

    std::string get_name() const;
    void set_name(std::string name);

    double get_value() const;
    void set_value(double value);

    int get_type() const;
    void set_type(int type);

protected:
    std::string name;
    double value;
    int type;
    enum activity_types {Sport, Spiritual, Work, Study, Art};
};

/*
class ActivitySport : public Activity {
public:
    ActivitySport();
    ActivitySport(std::string name, int duration);
    ~ActivitySport();
private:
    activity_types type_of_activity = Sport;
};


class ActivitySpiritual : public Activity {
public:
    ActivitySpiritual();
    ActivitySpiritual(std::string name, int duration);
    ~ActivitySpiritual();
private:
    activity_types type_of_activity = Spiritual;
};


class ActivityWork : public Activity {
public:
    ActivityWork();
    ActivityWork(std::string name, int duration);
    ~ActivityWork();
private:
    activity_types type_of_activity = Work;
};


class ActivityStudy : public Activity {
public:
    ActivityStudy();
    ActivityStudy(std::string name, int duration);
    ~ActivityStudy();
private:
    activity_types type_of_activity = Study;
};


class ActivityArt : public Activity {
public:
    ActivityArt();
    ActivityArt(std::string name, int duration);
    ~ActivityArt();
private:
    activity_types type_of_activity = Art;
};
*/
#endif // ACTIVITYCLASSES_H

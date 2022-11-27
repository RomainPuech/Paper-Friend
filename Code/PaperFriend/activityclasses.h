#ifndef ACTIVITYCLASSES_H
#define ACTIVITYCLASSES_H

#include <iostream>
#include <string>


class Activity {
public:
    Activity();
    Activity(std::string name, int duration);
    ~Activity();

    std::string get_name() const;
    void set_name(std::string name);

    int get_duration() const;
    void set_duration(int duration);

protected:
    std::string name;
    int duration;
    enum activity_types {Sport, Spiritual, Work, Study, Art};
};


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

#endif // ACTIVITYCLASSES_H

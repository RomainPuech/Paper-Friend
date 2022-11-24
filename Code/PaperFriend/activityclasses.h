#ifndef ACTIVITYCLASSES_H
#define ACTIVITYCLASSES_H

#include <iostream>


class Activity {
public:
    Activity();
    Activity(std::string name, int duration);
    ~Activity() {}

    std::string get_name();
    void set_name(std::string name);

    int get_duration();
    void set_duration(int duration);

protected:
    std::string name;
    int duration;
};


class ActivitySport {
public:
    ActivitySport();
    ActivitySport(std::string name, int duration);
    ~ActivitySport() {}
};


class ActivitySpiritual {
public:
    ActivitySpiritual();
    ActivitySpiritual(std::string name, int duration);
    ~ActivitySpiritual() {}
};


class ActivityWork {
public:
    ActivityWork();
    ActivityWork(std::string name, int duration);
    ~ActivityWork() {}
};


class ActivityStudy {
public:
    ActivityStudy();
    ActivityStudy(std::string name, int duration);
    ~ActivityStudy() {}
};


class ActivityArt {
public:
    ActivityArt();
    ActivityArt(std::string name, int duration);
    ~ActivityArt() {}
};

#endif // ACTIVITYCLASSES_H

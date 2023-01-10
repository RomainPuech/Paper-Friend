#ifndef ACTIVITYCLASSES_H
#define ACTIVITYCLASSES_H

#include <iostream>
#include <string>
#include <QString>

/*
class Activity {
public:
    Activity(std::string name, int type, double value);
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
    enum activity_types {None,Sport, Spiritual, Work, Study, Art};
};
*/

struct Activity {

    Activity(std::string name = "", int type = 0, double value = 0);
    ~Activity();

    std::string get_name() const;
    void set_name(std::string name);

    double get_value() const;
    void set_value(double value);

    int get_type() const;
    void set_type(int type);

    bool equal(Activity other);

    bool operator ==(Activity &other);//used when trying to find an activity in a vector

protected:
    std::string name;
    int type;
    double value;
};

#endif // ACTIVITYCLASSES_H

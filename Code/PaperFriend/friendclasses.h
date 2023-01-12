#ifndef FRIENDCLASSES_H
#define FRIENDCLASSES_H

#include <iostream>
#include <string>
#include <QString>

/*
class Friend {
public:
    Friend(std::string name, int duration);
    ~Friend();

    std::string get_name() const;
    void set_name(std::string name);

    int get_duration() const;
    void set_duration(int duration);

private:
    std::string name;
    int duration;
};
*/

struct Friend {

    Friend(std::string name = "",int type = 0, int duration = 0);
    ~Friend();

    std::string get_name() const;
    void set_name(std::string name);

    int get_duration() const;
    void set_duration(int duration);

    int get_type() const;
    void set_type(int type);

    bool equal(Friend other);

private:
    std::string name;
    int type;
    int duration;
};

#endif // FRIENDCLASSES_H

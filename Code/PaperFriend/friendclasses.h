#ifndef FRIENDCLASSES_H
#define FRIENDCLASSES_H

#include <iostream>
#include <string>


class Friend {
public:
    Friend();
    Friend(std::string name, int duration);
    ~Friend() {}

    std::string get_name();
    void set_name(std::string name);

    int get_duration();
    void set_duration(int duration);

protected:
    std::string name;
    int duration;
};

#endif // FRIENDCLASSES_H

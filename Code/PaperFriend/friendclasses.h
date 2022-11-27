#ifndef FRIENDCLASSES_H
#define FRIENDCLASSES_H

#include <iostream>
#include <string>


class Friend {
public:
    Friend();
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

#endif // FRIENDCLASSES_H

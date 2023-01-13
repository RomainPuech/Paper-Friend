#ifndef MASCOT_H
#define MASCOT_H
#include <iostream>
#include <vector>
#include <string>
#include <Analysis/DataAnalysis.h>

class Mascot
{
public:
    Mascot();
    QString get_emotion(int num);//returns path string of a specific mascot image based on the num that should range from 0 to 100
private:
    std::vector<QString> imagepath_strings_vect; // vector of all the mascot images' paths
                                             //as strings
};

#endif // MASCOT_H

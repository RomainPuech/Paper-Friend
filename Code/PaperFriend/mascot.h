#ifndef MASCOT_H
#define MASCOT_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Mascot
{
public:
    Mascot();
private:
    vector<string> imagepath_strings_vect; // vector of all the mascot images' paths
                                             //as strings
    string mascot ; //default image path string
    string image_to_display(); // takes the message from the analysis function,
               //sets mascot to be the path string of the image to be displayed
};

#endif // MASCOT_H

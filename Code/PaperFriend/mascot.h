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
    QString get_mascot();
private:
    QString img_path; //it will store the path string of the image to be displayed
    std::vector<QString> imagepath_strings_vect; // vector of all the mascot images' paths
                                             //as strings
    QString mascot ; //default image path string
    void image_to_display(DataAnalysis* data_analysis); // takes the message from the analysis function,
               //sets img_path to be the path string of the image to be displayed
};

#endif // MASCOT_H

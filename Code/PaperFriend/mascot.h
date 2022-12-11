#ifndef MASCOT_H
#define MASCOT_H
#include <iostream>
#include <vector>
#include <string>
#include <Analysis/DataAnalysis.h>
#include <mascotchat.h>

class Mascot
{
public:
    Mascot();
    void add_image(MascotChat mascotchat); //adds the image to the scroll area
private:
    QString img_path; //it will store the path string of the image to be displayed
    std::vector<QString> imagepath_strings_vect; // vector of all the mascot images' paths
                                             //as strings
    QString mascot ; //default image path string
    void image_to_display(DataAnalysis* data_analysis); // takes the message from the analysis function,
               //sets img_path to be the path string of the image to be displayed
    //void add_image(MascotChat* mascotchat); //adds the image to the scroll area
};

#endif // MASCOT_H

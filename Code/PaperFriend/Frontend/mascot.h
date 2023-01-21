#ifndef MASCOT_H
#define MASCOT_H
#pragma once

#include <Analysis/DataAnalysis.h>
#include <iostream>
#include <string>
#include <vector>

class Mascot {
public:
  Mascot();
  QString get_emotion(int num); /*returns a string containing the image path of a
                         specific mascot image based on the num that should range
                         from 0 to 100 written in way such that it could be
                         displayed in the chat_layout */
private:
  std::vector<QString> imagepath_strings_vect; // vector of all the strings with
                                               // the mascot images' paths
};

#endif // MASCOT_H

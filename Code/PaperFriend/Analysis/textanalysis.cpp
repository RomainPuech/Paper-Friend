#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "TextAnalysis.h"


double TextAnalysis::get_text_mood(){
    return text_mood;
}


double TextAnalysis::str_to_double(std::string text){
/**
   * @param text: single row string
   * @return converted double number
*/
    bool negative = false;
    double res = 0;

    if(text.substr(0, 1) == "-"){
        negative = true;
        text.erase(0, 1);
    }

    int count = 0;
    bool flag = false;
    for(char c : text){
        if (flag)
            count++;

        if (c == '.')
        {
            flag = true;
        }
        else
        {
            res += (int(c) - 48) / (pow(10, count));
        }

    }

    if (negative)
        return -res;
    return res;
}


void TextAnalysis::analyze_text(){
    /**
     *  Analyzes text in "./nlp/input.txt" file and writes the resulting mood (from -1 to 1) in text_mood
     */

    system("./nlp/nlp_text_sentiment");  // runs the python exe file and writes the result in "output.txt"

    // Reading the result str and converting it to number:
    std::ifstream file;
    file.open("./nlp/output.txt");

    std::string text;
    file >> text;

    text_mood = str_to_double(text);

    file.close();
}

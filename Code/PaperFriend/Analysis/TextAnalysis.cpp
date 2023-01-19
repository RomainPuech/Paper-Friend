#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

#include "DataAnalysis.h"
#include "TextAnalysis.h"

double TextAnalysis::get_text_mood() { return text_mood; }

double TextAnalysis::str_to_double(std::string text) {
  /**
   * @param text: single row string
   * @return converted double number
   */
  bool negative = false;
  double res = 0;

  if (text.substr(0, 1) == "-") {
    negative = true;
    text.erase(0, 1);
  }

  int count = 0;
  bool flag = false;
  for (char c : text) {
    if (flag)
      count++;

    if (c == '.') {
      flag = true;
    } else {
      res += (int(c) - 48) / (pow(10, count));
    }
  }

  if (negative)
    return -res;
  return res;
}

void TextAnalysis::analyze_text() {
  /**
   *  Analyzes text in "./nlp/input.txt" file and writes the resulting mood
   * (from 0 to 1) in text_mood
   */
  std::ofstream f_write;
  f_write.open("./nlp/input.txt");

  std::string text_in = log.end()->get_text();
  f_write << text_in << std::endl;

  system("./nlp/nlp_text_sentiment"); // runs the python exe file and writes the
                                      // result in "output.txt"

  // Reading the result str and converting it to number:
  std::ifstream f_read;
  f_read.open("./nlp/output.txt");

  std::string text;
  f_read >> text;

  // rescaling mood to be from 0 to 1
  text_mood = (1 + str_to_double(text)) / 2;

  f_read.close();
  f_write.close();
}

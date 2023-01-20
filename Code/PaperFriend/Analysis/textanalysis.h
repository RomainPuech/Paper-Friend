#ifndef TEXTANALYSIS_H
#define TEXTANALYSIS_H


#include "DataAnalysis.h"


class TextAnalysis{

public:

    TextAnalysis(QString text): text_to_analize(text){text_mood=0;};

    void analyze_text();

    double str_to_double(std::string text);

    double get_text_mood();

private:

    double text_mood;  // mood predicted from the text from 0 to 1
    QString text_to_analize;
};

#endif // TEXTANALYSIS_H

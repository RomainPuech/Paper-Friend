#include "mascot.h"
#include <QLayout>

Mascot::Mascot(){
    QString peaceout = "<img src=:/pictures/rsc/peaceout-resized.png align=middle height=\"85\">";
        QString  excited = "<img src=:/pictures/rsc/excited-resized.png align=middle height=\"85\">";
        QString pleading = "<img src=:/pictures/rsc/pleading-resized.png align=middle height=\"85\">";
    /*QString peaceout = ":/pictures/rsc/peaceout-resized.png";
    QString  excited = ":/pictures/rsc/excited-resized.png";
    QString pleading = ":/pictures/rsc/pleading-resized.png";*/
    imagepath_strings_vect = {excited,pleading,peaceout};}

QString Mascot::get_emotion(int num){
    if(num >=0 and num < 50){
        return imagepath_strings_vect[1];
    }
    else if (num >=50 and num <70) {
        return imagepath_strings_vect[2];
    }
    else{
        return imagepath_strings_vect[0];
    }
}



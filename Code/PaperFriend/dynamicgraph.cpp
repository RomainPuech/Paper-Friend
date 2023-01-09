/*

  To implement: if there is a too large gap in the dates, leave an empty space in the graph
  x axis in absolute value

*/


#include "dynamicgraph.h"
#include <QApplication>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QLegend>
// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>
// Used to create a line chart
#include <QtCharts/QLineSeries>
// Used to change names on axis
#include <QtCharts/QCategoryAxis>
#include "entryclasses.h"
#include <QtDebug>

//////////////////
//private methods useful for display
DynamicGraph::parameterlevel DynamicGraph::associated_parameter_level(double parameter) const{
    /*
     returns the parameter level corresponding to the given parameter value
     */
    if(parameter>75){// strict inequality otherwise problems in the creation of the two dummy points for transition from bad parameter to good parameter when the point is exactly at 75
        return good;
    }else if(parameter>=35){
        return medium;
    }
    return bad;
}

void DynamicGraph::set_color(QLineSeries* series, parameterlevel level){ // can transform into a template to handle line/spline customization
    /*
     changes the color of the line corresponding to this series on the graph with the color corresponding to the level of parameter.
     If the parameter is bad, the color will be set to red, etc...
     */
    QPen pen = series->pen();
    pen.setWidth(3);//to change the line's width
    pen.setColor(level_colors[level]);//level_colors defined in hpp file indicates the color associated to each parameter level
    series->setPen(pen);
}

void DynamicGraph::get_dummy_point(double y1,double y2, double x1, double x2, double (&res)[2]){
    /*
     returns the dummy point that one need to add to the series to make it change color at the righ location.
     For example, if the parameter goes from y1=6 to y2=14 then the line has to change color at y=7. We have to compute the associated x to keep the same slope as before.
     */
    double target;//y coordinate of the dummy point
    int previous = associated_parameter_level(y1);
    int current = associated_parameter_level(y2);
    //important: we assume here that the parameter is only changing by 1 level. For example, if the new parameter level is "good", we assume that it was "medium" before. If this goes from "bad" to "good", this function should be called twice with well chosen parameters.
    //we first get the target
    if(previous==0){//then the parameter was bad and it turns medium
        target = 35;
    }else if(previous==1){
        if(current==2){//then it was medium before and good now
            target=75;
        }
        else{
            target=35;
        }
    }else{//the parameter was good and is now medium
        target = 75;
    }

    // We got the target. Now, let's compute the slope between our two points (x1,y1) and (x2,y2) and find what should be x so that (x,target) is correctly placed
    double slope = (y2-y1)/(x2-x1);
    // y1 + slope*x = target <=> x= (target-y1)/slope
    double x = x1 + (target-y1)/slope;
    res[0]=x;
    res[1]=target;
    // we don't return anything as res is given by reference.
}

double DynamicGraph::parameter_value(EntryPerso *entry, QString tracked_parameter) {
    if (tracked_parameter == "mood") {
        return entry->get_mood();
    } else if (tracked_parameter == "sleep") {
        return entry->get_sleep();
    } else if (tracked_parameter == "eating healthy") {
        return entry->get_eating_healthy();
    } else if (tracked_parameter == "productivity") {
        return entry->get_productivity();
    } else if (tracked_parameter == "communications") {
        return entry->get_communications();
    } else {
        return entry->get_screen_time();
    }
}

/////////////////////
//Constructor
DynamicGraph::DynamicGraph(std::vector<EntryPerso*>& entries, QString tracked_parameter)
    :listofseries(std::vector<QLineSeries*>()),entries(entries)
{   
    QDate today = QDate::currentDate();

    //////
    visible_green_points = new QScatterSeries();
    visible_green_points->setBorderColor("green");
    visible_green_points->setColor("green");
    visible_green_points->setMarkerSize(7);

    visible_orange_points = new QScatterSeries();
    visible_orange_points->setBorderColor("orange");
    visible_orange_points->setColor("orange");
    visible_orange_points->setMarkerSize(7);

    visible_red_points = new QScatterSeries();
    visible_red_points->setBorderColor("red");
    visible_red_points->setColor("red");
    visible_red_points->setMarkerSize(7);

    ///
    int n = entries.size()-1;//the x axis will be negative numbers: x days ago = -x.
    if(n==-1){return;}
    QLineSeries *series= new QLineSeries();//series in which we add the points to display on the graph
    parameterlevel current_parameter_level = associated_parameter_level(parameter_value(entries[0], tracked_parameter));
    set_color(series,current_parameter_level);//initialize the right color for the first point
    double y1;
    double x1 = - (entries[0]->get_qdate().daysTo(today));

    for(auto e: entries){

        double x2 = - (e->get_qdate().daysTo(today));
        double y2 = parameter_value(e, tracked_parameter);//current point
        //qDebug() << x2 << y2;

        parameterlevel level = associated_parameter_level(y2);
        if(abs(x1-x2) > 3){
            //qDebug() << x1 << x2;
            listofseries.push_back(series);
            series = new QLineSeries();

        }
        else if(level!=current_parameter_level){//the parameter level changed, we need to change the line's color, so create a new series (a series can only have one single color)
            double dummypoint1[2];
            double dummypoint2[2];
            if(abs(level-current_parameter_level) >=2){//if we jump directly from bad mood to good parameter, then we have to create a fake series to make the line orange between the first dummy point and the second dummy point.
                get_dummy_point(y1,y2,x1,x2,dummypoint1);//see description of corresponding function
                get_dummy_point(dummypoint1[1],y2,dummypoint1[0],x2,dummypoint2);
                *series<<QPointF(dummypoint1[0],dummypoint1[1]);
                listofseries.push_back(series);
                series = new QLineSeries();// we create anew curve with a different color
                set_color(series,medium);
                *series<<QPointF(dummypoint1[0],dummypoint1[1]);// the new series needs to start with the last point of the previous one to make them appear connected on the graph
                *series<<QPointF(dummypoint2[0],dummypoint2[1]);
                listofseries.push_back(series);
                series = new QLineSeries();
                *series<<QPointF(dummypoint2[0],dummypoint2[1]);
            }else{//jump of only one parameter level
                get_dummy_point(y1,y2,x1,x2,dummypoint1);
                *series<<QPointF(dummypoint1[0],dummypoint1[1]);
                listofseries.push_back(series);
                series = new QLineSeries();
                *series<<QPointF(dummypoint1[0],dummypoint1[1]);
            }

        }//if the parameter level remained the same, we just add the point to the current series
        current_parameter_level = level;
        set_color(series,level);
        *series<<QPointF(x2,y2);
        if(level==good){
            *visible_green_points<<QPointF(x2+0.01,y2);
        }else if(level==medium){
            *visible_orange_points<<QPointF(x2+0.01,y2);
        }else{
            *visible_red_points<<QPointF(x2+0.01,y2);
        }

        y1=y2;
        x1=x2;
    }
    listofseries.push_back(series);
}

////////////////////////
//setters and getters
std::vector<EntryPerso*> DynamicGraph::get_entries() const{return entries;}

////////////////////////
//display the graph
void DynamicGraph::display(QLayout *layout) const
{

    if(entries.size()==0){return;}
    QChart *parameter_chart = new QChart();
    for(int i=0;i<listofseries.size();i++){//we add every curve to the graph: one curve per colored section on the graph
        parameter_chart->addSeries(listofseries[i]);
    }
    parameter_chart->addSeries(visible_green_points);
    parameter_chart->addSeries(visible_orange_points);
    parameter_chart->addSeries(visible_red_points);
    parameter_chart->legend()->hide();



    parameter_chart->createDefaultAxes();
    parameter_chart->axes(Qt::Vertical).first()->setRange(0, 100);
    //mood_chart->axes(Qt::Vertical).first()->setTitleText(QString::fromStdString("Mood"));
    QFont font = QFont();
    font.setWeight(QFont::Thin);
    //assuming the vector is sorted(!) :
    // mood_chart->axes(Qt::Horizontal).first()->setRange( - (entries[entries.size()-1]->get_qdate().daysTo(QDate::currentDate())) , - (entries[0]->get_qdate().daysTo(QDate::currentDate())) + 1 );
    int start = std::min((int)- (entries[entries.size()-1]->get_qdate().daysTo(QDate::currentDate())) +1,0) ;
    int end = - (entries[0]->get_qdate().daysTo(QDate::currentDate())) ;
    //qDebug() << "yo mec" << start << end;
    parameter_chart->axes(Qt::Horizontal).first()->setRange( end, start);
    parameter_chart->axes(Qt::Horizontal).first()->setTitleFont(font);
    parameter_chart->axes(Qt::Horizontal).first()->setTitleText(QString::fromStdString("Days ago"));
    QValueAxis* xaxis = static_cast<QValueAxis*>(parameter_chart->axes(Qt::Horizontal).first()); //used to be able to call QValueAxis methods as we know that the axis is of type QValueAxis, which inherits from QAbstractAxis, returned by the function
    xaxis->setLabelFormat("%0.1f");
    //qDebug()<<"here";

    //qDebug()<<"et pas here";
    //mood_chart->axes(Qt::Horizontal).first()->setLabelFormat("%.2f");
    //tests to put absolute value as an x axis.
    /*
    //QValueAxis *axisX = new QValueAxis;
    mood_chart->Xaxis.setLabelFormat("%.2f");
    */

    parameter_chart->setAnimationOptions(QChart::GridAxisAnimations);
    /*
    QFont titlefont = QFont();
    titlefont.setWeight(QFont::Bold);
    parameter_chart->setTitleFont(titlefont);
    parameter_chart->setTitle("My mood");
    */
    QChartView *parameter_view = new QChartView(parameter_chart);
    parameter_view->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(parameter_view);//displays the graph on the screen in the indicated layout

}

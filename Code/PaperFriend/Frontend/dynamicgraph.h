#ifndef DYNAMICGRAPH_H
#define DYNAMICGRAPH_H

#pragma once

#include <QChartView>
#include <QLineSeries>
#include <QWidget>
#include <QtCharts>
// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>
// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>
// Used to create a line chart
#include <QtCharts/QLineSeries>
// Used to change names on axis
#include "entryclasses.h"
#include <QtCharts/QCategoryAxis>
#include <vector>

class DynamicGraph {
public:
  DynamicGraph(std::vector<EntryPerso *> &entries, QString tracked_parameter);
  ~DynamicGraph();
  void display(QLayout *parent_frame);
  // getters and setters
  std::vector<EntryPerso *> get_entries() const;

private:
  std::vector<QLineSeries *> listofseries;
  std::vector<EntryPerso *> entries;
  QScatterSeries *visible_green_points;
  QScatterSeries *visible_orange_points;
  QScatterSeries *visible_red_points;
  QColor level_colors[3] = {"red", "orange", "green"};
  enum parameterlevel { bad, medium, good };
  QChart *parameter_chart;
  QChartView *parameter_view;

  // methods
  parameterlevel associated_parameter_level(double parameter) const;
  void set_color(QLineSeries *series, parameterlevel level);
  void get_dummy_point(double y1, double y2, double x1, double x2,
                       double (&res)[2]);
  double parameter_value(EntryPerso *entry, QString tracked_parameter);
};

#endif // DYNAMICGRAPH_H

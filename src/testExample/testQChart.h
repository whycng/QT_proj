#pragma once


//#include <QtCharts> QLineSeries QAreaSeries QChart
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

void plotWaveform(QtCharts::QChart *chart,
                  QVector<double>& data_y,
                  QVector<double>& data_x,
                  int i_offset);
QVector<QVector<double>> splitToSegments(QVector<double> data);


void test_PLotCurve(QVector<double>& data_y,
                    QVector<double>& data_x);

void test_PLotCurve2(QVector<double>& data_y,
                    QVector<double>& data_x);


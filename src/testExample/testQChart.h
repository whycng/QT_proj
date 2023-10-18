#pragma once


//#include <QtCharts> QLineSeries QAreaSeries QChart

//#include <QtCharts/QAreaSeries>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QChart>
//#include <QtCharts/QChartView>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include <QRandomGenerator>
#include <QPainter>
#include <QLabel>

//#include <QOpenGLWidget>
#define QT_NO_OPENGL_ES_2
//#include <QOpenGLWidget>
//#include <QOpenGLFunctions>

//class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
//{
//public:
//    GLWidget() {}

//    void initializeGL() override {
//        initializeOpenGLFunctions();
//    }

//    void paintGL() override {
//        QRandomGenerator random;

//        glClear(GL_COLOR_BUFFER_BIT);

//        for(int i=0; i<width; i++) {
//            for(int j=0; j<height; j++) {

//                glColor3ub(random.generate()%256,
//                           random.generate()%256,
//                           random.generate()%256);

//                glRecti(i, j, i+1, j+1);
//            }
//        }
//    }

//private:
//    const int width = 1000;
//    const int height = 700;
//};





//void plotWaveform(QtCharts::QChart *chart,
//                  QVector<double>& data_y,
//                  QVector<double>& data_x,
//                  int i_offset);
//QVector<QVector<double>> splitToSegments(QVector<double> data);


void test_PLotCurve(QVector<double>& data_y,
                    QVector<double>& data_x);

void test_PLotCurve2(QVector<double>& data_y,
                    QVector<double>& data_x);

void test_plot_density();


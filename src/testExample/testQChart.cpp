#include "testQChart.h"
#include <QDebug>
//检测到正负交替，进行分割
QVector<QVector<double>> splitToSegments(QVector<double> data) {

    QVector<QVector<double>> segments;

    int start = 0;
    bool positive = data[0] >= 0;

    for(int i=1; i<data.size(); i++) {

        if((data[i] < 0 && positive) ||
            (data[i] >= 0 && !positive)) {

            // 检测到正负交换,新建一段
            QVector<double> segment;
            for(int j=start; j<i; j++) {
                segment.push_back(data[j]);
            }
            segments.push_back(segment);

            start = i;
            positive = !positive;
        }
    }

    // 处理最后一段
    QVector<double> segment;
    for(int j=start; j<data.size(); j++) {
        segment.push_back(data[j]);
    }
    segments.push_back(segment);

    return segments;
}


void plotWaveform(QtCharts::QChart *chart,
                  QVector<double>& data_y,
                  QVector<double>& data_x,
                  int i_offset) {

    QVector<QVector<double>> segments = splitToSegments(data_y);
    int index = 0;
    int i_tmp = 0;int test_i = 2;
//    qDebug() << "[Message]<plotWaveform> data_y:" <<  data_y;
//    qDebug() << "[Message]<plotWaveform> segments:" <<  segments;
//    qDebug() << "[Message]<plotWaveform> data_y.size:" <<  data_y.size();
//    qDebug() << "[Message]<plotWaveform> data_x.size:" <<  data_x.size();


    foreach(QVector<double> segment, segments) {
        double temp_first_x;
        QPen pen;
        QBrush brush;

        // 偏移
        for(int i=0;i< segment.size();i++)
        {
            segment[i] += i_offset;
        }

//        if(i_tmp <= test_i)
//        {
//             qDebug() << "[Message]<plotWaveform>";
//        }

//        if(i_tmp >=1)
//            break;

        //if(index <= 1)
        {
            QtCharts::QLineSeries *series1 = new QtCharts::QLineSeries();
            temp_first_x = data_x[index];

            if(segment.size() <=2 ) continue;
            for(int i=0; i<segment.size(); i++) {
                *series1 << QPointF(data_x[index], segment[i]);
//                if(i_tmp <= test_i)
//                {
//                    qDebug() << "[Message]<plotWaveform> data_x[index]:" <<  data_x[index]
//                             << "segment[i]" << segment[i];

//                }
                index++;
            }
            // 用于补全区域，一个波形起始终末两个点
            QtCharts::QLineSeries *series0 = new QtCharts::QLineSeries();
            *series0 << QPointF(temp_first_x, segment[0])
                     // <<  QPointF(data_x[index-1], segment[0])
                     << QPointF(data_x[index-1], segment[segment.size()-1]);

//            if(i_tmp <= test_i)
//            {
//                qDebug() << "[Message]<plotWaveform>series0; temp_first_x:" <<  temp_first_x
//                         << "segment[0]" << segment[0];
//                qDebug() << "[Message]<plotWaveform>series0; data_x[index-1]:" <<  data_x[index-1]
//                         << "segment[segment.size()-1]:" << segment[segment.size()-1];
//            }

            QtCharts::QAreaSeries *seriesA = new QtCharts::QAreaSeries(series1, series0);
            //seriesA->setName("Batman");
//            QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
//            gradient.setColorAt(0.0, 0x3cc63c);
//            gradient.setColorAt(1.0, 0x26f626);
//            gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
            seriesA->setBrush(Qt::green);
            seriesA->setUseOpenGL(true);
            QPen pen;
            pen.setColor(Qt::red);
            seriesA->setPen(pen);

            chart->addSeries(seriesA);

            // qDebug() << "[Message]<plotWaveform> seriesA:" <<  seriesA;
        }
        i_tmp++;
//
    }

}


void test_PLotCurve(QVector<double>& data_y,
                    QVector<double>& data_x)
{
    QwtPlot *plot = new QwtPlot();
    QwtPlotCurve* curve = new QwtPlotCurve;

    curve->attach(plot);
    curve->setSamples(data_x,data_y);// x轴  y轴数据，坐标
    QColor color = QColor(Qt::black);
    QBrush brush(color);
    curve->setBrush(brush);

    plot->resize(400, 300);
    plot->show();
}

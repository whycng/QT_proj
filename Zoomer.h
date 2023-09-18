
#ifndef Zoomer_H
#define Zoomer_H

#include <qwt_plot_zoomer.h>
#include <qwt_plot_canvas.h>
#include <QMouseEvent>

class Zoomer : public QwtPlotZoomer
{
public:
    Zoomer(QwtPlotCanvas *canvas);


    // 新增
    bool eventFilter(QObject *object, QEvent *event);
    void undoZoom();
    QRectF initialRect;
    QwtPlot* z_qwtPlot;//  = ui->qwtPlot;
    double xMin,xMax,yMin,yMax;
private:
};

#endif // Zoomer_H


/*
#ifndef __Zoomer_H__
#define __Zoomer_H__

#include <qwt_plot_zoomer.h>
#include <qwt_plot_canvas.h>
#include <QMouseEvent>
const unsigned int c_rangeMax = 1000;

class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer(QwtPlotCanvas *canvas,QRectF rect,bool bDir=true);
    void updateRange(QRectF rect);
    void setRect(QRectF rect);
    virtual void rescale();

    // 新增
    bool eventFilter(QObject *object, QEvent *event);
    void undoZoom();
    QRectF initialRect;
    QwtPlot* z_qwtPlot;//  = ui->qwtPlot;
    double xMin,xMax,yMin,yMax;
public Q_SLOTS:
	 virtual void zoom( const QRectF & );
	 virtual void zoom( int up );
private:
    bool m_bDir;
    QRectF m_rect;
};
#endif //__Zoomer_H__
*/

#include "Zoomer.h"
#include "qwt_scale_widget.h"
#include "qwt_plot.h"

Zoomer::Zoomer(QwtPlotCanvas *canvas )
    : QwtPlotZoomer(canvas)
{
}

bool Zoomer::eventFilter(QObject *object, QEvent *event)
{
    if (object == canvas() && event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton)
        {
            undoZoom(); // 在鼠标右键释放事件中调用 undoZoom()
        }
    }
    return QwtPlotZoomer::eventFilter(object, event);
}

void Zoomer::undoZoom()
{
    // 在这里添加你想要执行的还原操作

    z_qwtPlot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
    z_qwtPlot->setAxisScale(QwtPlot::yLeft, yMin, yMax);
    z_qwtPlot->replot();

    qDebug() << "undoZoom" << "   xMin:" << xMin << "   xMax:" << xMax;
}

/*
Zoomer::Zoomer(QwtPlotCanvas *canvas,QRectF rect, bool bDir):
    QwtPlotZoomer(canvas)
{
    m_bDir = bDir;
    m_rect = rect.normalized();

    // 设置鼠标右键释放事件过滤器
    canvas->installEventFilter(this);
}


bool Zoomer::eventFilter(QObject *object, QEvent *event)
{
    if (object == canvas() && event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton)
        {
            undoZoom(); // 在鼠标右键释放事件中调用 undoZoom()
        }
    }
    return QwtPlotZoomer::eventFilter(object, event);
}

void Zoomer::undoZoom()
{
    // 恢复初始坐标轴范围的操作 --没用
    // setZoomBase(m_rect);
//    setZoomBase(QRectF(100, 0, 250, 1000));
//    zoom(0);



    z_qwtPlot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
    z_qwtPlot->setAxisScale(QwtPlot::yLeft, yMin, yMax);
    z_qwtPlot->replot();

    qDebug() << "undoZoom" << "   xMin:" << xMin << "   xMax:" << xMax;
}



void Zoomer::rescale()
{
    QwtScaleWidget *scaleWidget = plot()->axisWidget(yAxis());
    QwtScaleDraw *sd = scaleWidget->scaleDraw();

    int minExtent = 0;
    if ( zoomRectIndex() > 0 )
    {
        // When scrolling in vertical direction
        // the plot is jumping in horizontal direction
        // because of the different widths of the labels
        // So we better use a fixed extent.

        minExtent = sd->spacing() + 1;//+ sd->majTickLength() 
        minExtent += sd->labelSize(
            scaleWidget->font(), c_rangeMax).width();
    }

    sd->setMinimumExtent(minExtent);

    QwtPlotZoomer::rescale();
}
void Zoomer::updateRange(QRectF rect)
{
    m_rect = rect.normalized();
}
void Zoomer::zoom( const QRectF &rect )
{
    QRectF zoomRect = rect.normalized();
    QwtPlot *plot = QwtPlotZoomer::plot();
    if ( !plot )
        return;

    QPointF lt = zoomRect.topLeft();
    QPointF rb = zoomRect.bottomRight();
    if(m_bDir)
    {
	lt.setY(m_rect.top());
	rb.setY(m_rect.bottom());

	if(lt.x()-m_rect.left()<1e-10)
		lt.setX(m_rect.left());
	if(rb.x()-m_rect.left()<1e-10)
		rb.setX(m_rect.left());

	if(lt.x()-m_rect.right()>1e-10)
		lt.setX(m_rect.right());
	if(rb.x()-m_rect.right()>1e-10)
		rb.setX(m_rect.right());

	QRectF zoom(lt,rb);
	QwtPlotZoomer::zoom(zoom);
    }
    else
    {
	lt.setX(m_rect.left());
	rb.setX(m_rect.right());

	if(lt.y()-m_rect.top()<1e-10)
		lt.setY(m_rect.top());
	if(rb.y()-m_rect.top()<1e-10)
		rb.setY(m_rect.top());

	if(lt.y()-m_rect.bottom()>1e-10)
		lt.setY(m_rect.bottom());
	if(rb.y()-m_rect.bottom()>1e-10)
		rb.setY(m_rect.bottom());

	QRectF zoom(lt,rb);
	QwtPlotZoomer::zoom(zoom);
    }

    plot->replot();
}
void Zoomer::zoom( int up )
{
	QwtPlotZoomer::zoom(up);
	QwtPlot *plot = QwtPlotZoomer::plot();
	plot->replot();
}

void Zoomer::setRect(QRectF rect)
{
    m_rect=rect;
}

*/


/*这个Zoomer类是一个继承自QwtPlotZoomer的自定义类，用于在QwtPlot中实现缩放功能并限制缩放范围。它具有以下功能：

1. 构造函数 `Zoomer::Zoomer(QwtPlotCanvas *canvas,QRectF rect, bool bDir)`：
   - 接受一个QwtPlotCanvas指针和一个矩形rect作为参数，并设置缩放方向bDir。
   - 初始化成员变量m_bDir和m_rect。

2. 函数 `void Zoomer::rescale()`：
   - 获取y轴的刻度标尺部件和刻度绘制对象。
   - 计算最小的刻度标尺宽度，确保缩放时图像不会跳动。
   - 设置刻度绘制对象的最小宽度。
   - 调用基类QwtPlotZoomer的rescale()函数进行缩放。

3. 函数 `void Zoomer::updateRange(QRectF rect)`：
   - 更新m_rect成员变量，用于存储限制的缩放范围。

4. 函数 `void Zoomer::zoom(const QRectF &rect)`：
   - 对给定的矩形rect进行缩放操作。
   - 根据缩放方向m_bDir和限制的缩放范围m_rect，调整矩形的坐标值。
   - 调用基类QwtPlotZoomer的zoom()函数进行缩放。
   - 重新绘制QwtPlot。

5. 函数 `void Zoomer::zoom(int up)`：
   - 对于给定的缩放方向up，调用基类QwtPlotZoomer的zoom()函数进行缩放。
   - 重新绘制QwtPlot。

6. 函数 `void Zoomer::setRect(QRectF rect)`：
   - 设置限制的缩放范围m_rect。

该Zoomer类主要通过重写QwtPlotZoomer的函数来实现自定义的缩放行为，
并且根据缩放方向和限制的范围对缩放矩形进行调整。它可以与QwtPlot对象结合使用，
实现在QwtPlot上通过鼠标进行缩放并限制缩放范围的功能。*/

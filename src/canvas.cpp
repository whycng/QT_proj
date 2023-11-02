#include <QDebug>
#include "canvas.h"
#include "qevent.h"
#include "qpainter.h"
#include "canvas.h"

/*
工区底图的绘制
*/


Canvas::Canvas(ParCanvas parCanvas, QWidget *parent)
    : QWidget(parent),m_parCanvas(parCanvas)
{
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);

    // 设置为绘图设备
    setAttribute(Qt::WA_PaintOnScreen);


    // 创建布局管理器
    mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    // 创建主窗口部件
    mainWindow = new QWidget();


    // 创建按钮部件
    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    // 设置布局的外边距和间距
//    buttonLayout->setContentsMargins(0, 0, 0, 0);
//    buttonLayout->setSpacing(0);
    // 设置布局的高度
    buttonWidget->setFixedHeight(40);

    // 创建按钮对象
    buttonDown = new QPushButton("确认", buttonWidget);
    buttonClear = new QPushButton("清除", buttonWidget);

    // 设置按钮的位置和大小
    buttonDown->setFixedSize(100, 30);
    buttonClear->setFixedSize(100, 30);

    // 添加按钮到按钮部分布局
    buttonLayout->addWidget(buttonDown);
    buttonLayout->addWidget(buttonClear);

    // 将按钮部件添加到主布局
    mainLayout->addWidget(buttonWidget);

    // 设置主窗口部件的布局
    mainWindow->setLayout(mainLayout);

    // 添加实例化的 Canvas 对象到布局中
    this->setFixedSize(500,500);
    mainLayout->addWidget(this);
    mainWindow->show();

    // 连接按钮的点击事件到槽函数
    connect(buttonDown, SIGNAL(clicked()), this, SLOT(onButtonDownClicked()));
    connect(buttonClear, SIGNAL(clicked()), this, SLOT(onButtonClearClicked()));

//    //初始化坐标轴

    drawOnce = true;

    qDebug()<< "[MEssage]<Canvas> 初始化！";
    drawing = false;
}


void Canvas::onButtonDownClicked()//确认
{
    qDebug() << "Button 1 clicked!";
    QVector<QPoint> real_points;
    // 将存储起来的点 m_Points 进行处理
    foreach (QPoint point, m_Points) {
        float tp;
        tp = point.x() - rect.x();
        tp = tp / ( rect.width() - rect.x() );// 占比
        tp *= m_parCanvas.xnum;
        point.setX(tp);

        tp = point.y() - rect.y();
        tp = tp / ( rect.height() - rect.y() );// 占比
        tp *= m_parCanvas.ynum;
        point.setY(tp);

        real_points.append(point);

        qDebug() << "[Message]<onButtonDownClicked>point:" << point;
    }
    qDebug() << "[Message]<onButtonDownClicked>pointNum:" << real_points.size();
    emit test(real_points);
    emit test2();
    emit test3(56);

    #pragma region "通过线取点-不好" {
/*
    if(drawLines.isEmpty())
    {
        return;
    }
    QVector<QPoint> points;
    // 返回坐标
    QPoint startPoint = drawLines[0].p1(); // 获取起始点坐标
    qDebug() << "start Point: " << startPoint.x() << ", " << startPoint.y();
    float tp;
    tp = startPoint.x() - rect.x();
    tp = tp / ( rect.width() - rect.x() );// 占比
    tp *= m_parCanvas.xnum;
    startPoint.setX(tp);
    tp = startPoint.y() - rect.y();
    tp = tp / ( rect.height() - rect.y() );// 占比
    tp *= m_parCanvas.ynum;
    startPoint.setY(tp);

    points.append(startPoint);

    for (int i = 0; i < drawLines.size(); ++i) {
        const QLine& line = drawLines[i];

        QPoint endPoint = line.p2();   // 获取终止点坐标
        qDebug() << "End Point: " << endPoint.x() << ", " << endPoint.y();
        //  endPoint 进行处理

        tp = endPoint.x() - rect.x();
        tp = tp / ( rect.width() - rect.x() );// 占比
        tp *= m_parCanvas.xnum;
        endPoint.setX(tp);
        tp = endPoint.y() - rect.y();
        tp = tp / ( rect.height() - rect.y() );// 占比
        tp *= m_parCanvas.ynum;
        endPoint.setY(tp);

        points.append(endPoint);


        // 打印起始点和终止点坐标
        //qDebug() << "End Point: " << endPoint.x() << ", " << endPoint.y();
    }
*/
    #pragma endregion }
}

void Canvas::onButtonClearClicked()//清理
{
    qDebug() << "Button 2 clicked!";
    drawLines.clear();
    m_Points.clear();// 用完清理
    //initialize();//初始化坐标轴所需线段
    update();

}

void Canvas::paintEvent(QPaintEvent*)
{

    painter.begin(this);
    qDebug()<< "[MEssage]<paintEvent> Pen:" << painter.pen().color();

    #pragma region "不如写在 index<=1" {
//    if(drawOnce)
//    {
//        qDebug()<< "[MEssage]< TEST > global_index:" <<global_index;
//        qDebug()<< "[MEssage]<paintEvent> drawOnce True! "  ;
//        initialize();// 这部分lines应该默认保存为static --tmp
//        drawOnce = false;
//    }
//    else
//    {
//        qDebug()<< "[MEssage]< TEST > global_index:" <<global_index;

//        qDebug()<< "[MEssage]<paintEvent> drawOnce False! "  ;

//    }
    #pragma endregion }

    /*，--tmp 字体只在第二次绘制事件被调用了，并且切换窗口，或者update事件。都会
导致再次触发该事件，导致不再绘制字体，只执行了绘制lines*/
    if(global_index <= 1)
    {
        /*
        QFont font;
        font.setPointSize(20); // 设置字体大小
        painter.setFont(font);
        painter.setPen(Qt::red); // 设置文本颜色为黑色
        painter.setBrush(Qt::NoBrush); // 设置无背景色，即透明背景
        painter.drawText(100, 100, "xxxxxxxxxxxxx");
        */

        initialize();// 这个一直起作用是因为lines里面保存了

        qDebug()<< "[MEssage]< TEST > Pen:" << painter.pen().color();
        // 只能说第一次调用绘制事件是确实执行了，但是后面又被销毁了？？
    }
    global_index++;

    // 绘制坐标轴下方字体
    QFont font;
    font.setPointSize(8); // 设置字体大小
    painter.setFont(font);
    //painter.setPen(Qt::red); // 设置文本颜色为黑色
    painter.setBrush(Qt::NoBrush); // 设置无背景色，即透明背景
    float tx = float(m_parCanvas.xnum) / m_scaleNum;
    float ty = float(m_parCanvas.ynum) / m_scaleNum;
    for(int i=0;i<m_scaleNum;i++)//x轴
    {
        painter.drawText(rect.x() + i * m_shiftX,
                         rect.height() + 15,
                         QString::number(i * tx));
    }
    for(int i=1;i<m_scaleNum;i++)//y轴  不需要0
    {
        painter.drawText(rect.x() - 20,
                         rect.y() + (m_scaleNum - i) * m_shiftY + 10,
                         QString::number(i * ty));
    }

    // 绘制所有线段
//    painter.setPen(Qt::black);
//    foreach(QLine line, lines) {
//        painter.drawLine(line);
//    }
    // 绘制用户所画线段
    foreach(QLine line, drawLines) {
        painter.drawLine(line);
    }
    // 绘制基本线段-如 坐标轴
    painter.setPen(Qt::black);
    foreach(QLine line, basicLines) {
        painter.drawLine(line);
    }

    painter.end();
}



void Canvas::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<< "[MEssage]<mousePressEvent>  ";
    if(event->button() == Qt::LeftButton) {
        drawing = true;
        if(event->pos() == lastPoint)
        {
            // 如果还是同一个位置，那么这个点不需要再被记录
        }
        else
        {
            m_Points.append(event->pos());
        }
        lastPoint = event->pos();

        qDebug()<< "[MEssage]<mousePressEvent> lastPoint" << lastPoint;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
//    qDebug()<< "[MEssage]<mouseMoveEvent>  ";
    //  先搁置了，实际不需要这个操作，移动的时候就显示线条，如果要实现，参考mouseReleaseEvent
//    if(drawing) {
//        if(painter.begin(this)){
//            painter.setPen(Qt::red);
//            painter.drawLine(lastPoint, event->pos());
//            lastPoint = event->pos();
//            qDebug()<< "[MEssage]<mouseMoveEvent>lastPoint " << lastPoint;
//        }
//        update();
//    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
//    qDebug()<< "[MEssage]<mouseReleaseEvent>  ";
//    update();
    if(drawing) {
        qDebug()<< "[MEssage]<mouseReleaseEvent> lastPoint" << lastPoint
                 << "   event->pos()" << event->pos();

        update();// 此处看来是必须的
//        painter.begin(this);
//        painter.setPen(Qt::red); // 显示没有被激活--前后加begin，错误写法
//        painter.end();
        QPoint endPoint = event->pos();

        // 将其限制在矩形之内,这里line由 lastPoint 和 event->pos() 这两个点组成，
        // lastPoint是起始点，event->pos()是末尾点，因此只需考虑起始点在矩形内，末尾点在矩形外的情况
        // 因为当两者都在矩形内，或者都在矩形外，直接处理，当起始点在外，末尾点在内，也被处理
        if( lastPoint.x() >= rect.x() && lastPoint.x() <= rect.width()
            && lastPoint.y() >= rect.y() && lastPoint.y() <= rect.height() )
        {
            // 这里就处理了超出矩形框那一部分线
            if( endPoint.x() < rect.x() ) endPoint.setX(rect.x()) ;
            if( endPoint.x() > rect.width() ) endPoint.setX(rect.width());
            if( endPoint.y() < rect.y() ) endPoint.setY(rect.y()) ;
            if( endPoint.y() > rect.height() ) endPoint.setY(rect.height());

            QLine line(lastPoint, endPoint);
            drawLines.append(line);
            m_Points.append(endPoint);
        }
        else
        {
            qDebug() << "[Warning] 这条线不在矩形之内";
        }

    }

    drawing = false;
    lastPoint = event->pos();
}

void Canvas::initialize()
{
    qDebug()<< "[MEssage]<initialize>  ";
    // 设置背景颜色
    setPalette(QPalette(Qt::lightGray));

    // 设置初始绘图样式
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(Qt::red);
    //lineColor = Qt::red;

    // 添加坐标轴
    // 设置矩形的初始位置和大小
    int rectX = 50;  // 矩形左上角的x坐标
    int rectY = 50;  // 矩形左上角的y坐标
    int rectWidth = width() - rectX;   // 矩形的宽度
    int rectHeight = height() - rectY; // 矩形的高度
    rect = QRect(rectX, rectY, rectWidth, rectHeight);

    QLine verticalLine(rectX, rectY, rectX, rectHeight);
    QLine verticalLine2(rectWidth,rectY , rectWidth, rectHeight);
    QLine horizontalLine(rectX, rectHeight, rectWidth, rectHeight);
    QLine horizontalLine2(rectX,  rectY, rectWidth,  rectY);
    basicLines.append(verticalLine);
    basicLines.append(verticalLine2);
    basicLines.append(horizontalLine);
    basicLines.append(horizontalLine2);

    //刻度
    m_scaleNum = 10;// 分这些个刻度
    double tp_x1,tp_y1,tp_x2,tp_y2;
    m_shiftX = ( rectWidth - rectX ) / m_scaleNum;
    m_shiftY = ( rectHeight - rectY ) / m_scaleNum;
    double ch = 10;// 小刻度的高度
    tp_x1 = rectX;tp_y1 = rectY;



    for(int i=0;i<m_scaleNum;i++)// 横向
    { // 这里使用rectHeight - ch 是因为y轴是向下的
        QLine tpLine(tp_x1 + i * m_shiftX, rectHeight, tp_x1 + i * m_shiftX, rectHeight - ch);
        basicLines.append(tpLine);
    }
    for(int i=0;i<m_scaleNum;i++)// 纵向
    {
        QLine tpLine(tp_x1, tp_y1 + i * m_shiftY, tp_x1 + ch, tp_y1 + i * m_shiftY);
        basicLines.append(tpLine);
    }


    //qDebug() << "[Message] width:" << width() << " height:" << height();
}



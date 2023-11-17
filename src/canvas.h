#ifndef CANVAS_H
#define CANVAS_H


#include "qboxlayout.h"
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QPushButton>

struct ParCanvas{
    int xnum;
    int ynum;
};

class Canvas : public QWidget
{
    Q_OBJECT
public
slots:
    void onButtonClearClicked();
    void onButtonDownClicked();
signals:
    void test(QVector<QPoint> real_points);
//    void test2();
//    void test3(int x);
public:
    Canvas(ParCanvas parCanvas,QWidget *parent = nullptr);
    QPushButton* buttonDown; // 按钮，确定
    QPushButton* buttonClear;// 按钮，清除

    //void todo_ButtonDownClicked();
protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    //初始化
    void initialize();
    // 按钮槽函数


private:
    ParCanvas m_parCanvas;
    QBoxLayout* mainLayout;
    QWidget* mainWindow;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* canvasLayout;

    bool drawing;
    bool drawOnce;//初始化
    int global_index = 0;
    QPoint lastPoint;
    //QVector<QLine> lines;
    QVector<QLine> drawLines;//绘制变动的线
    QVector<QLine> basicLines;//基础线
    QVector<QPoint> m_Points;
    QPainter painter;
    QRect rect;  // 矩形的位置和大小
    int m_scaleNum;// 分10个刻度
    double m_shiftX;// x轴刻度间距
    double m_shiftY;// y轴刻度间距
  };



#endif // CANVAS_H

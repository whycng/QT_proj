#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_legend.h>
#include "csegyread.h"
#include "Zoomer.h"
#include "util.h"

#include <QFileInfo>
#include <QFileSystemModel>
#include <QTime>
#include <QFileDialog>
#include <QProgressDialog>
#include <QScrollArea>
#include <qwt_plot_renderer.h>
#include <QMessageBox>
#include "qevent.h"
#include "Zoomer.h"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPoint>

#include <QtCharts/QAreaSeries>
#include "src/testExample/testQChart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QwtPlotCurve *curve_tp;//用于绘图 curve
    QwtPlotCurve *curve_tp2;

//    QtCharts::QChart *chart;
//    QtCharts::QChartView *chartView;

    // 线数，道数
    int inLineNum;
    int xLineNum;

    // qwt
    CSegyRead m_segy;

    QString m_strCurrentPath;
    QString m_strCurrentFile;

    QWidget *m_pTabHeader, *m_pTabData;

    int num_line;// 加载数据的时候判断累计线号

    int m_nTraceHeaderByteValue;
    int m_nCurrentEndianType;

    int m_nGeophones; //检波器个数
    int  m_nTotalTraceNum;
    int m_nTraceLen;
    int m_nCurrentTraceNum;

    int m_nComponent;  // X Y Z分量选择的组合，如果选中X和Y, 则为13+14=27
    int m_nComponentX; // X分量=13
    int m_nComponentY; // Y分量=14
    int m_nComponentZ; // Z分量=12
    int m_nTraceId;   //Y分量=14, X分量=13， Z分量=12
    int m_nDisMode; //显示所有道为0， 以检波器显示为1
    bool is_data_loaded;//是否加载数据

    float m_nScale;

    double absMax[100];

    QFileInfo m_fileinfo;
    QFileSystemModel *fileModel ;

    QVector<QVector<double>*> m_Traces; //一个SEGY文件中所有道的数据
    float** traces;
    void waveP2();

    QString file_sgy_path;// sgy文件路径
    int draw_mode;// 绘制模式
    double qwtPlot_scale[4];//存储qwtPlot默认大小 xmin，xmax,ymin,ymax xmin = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
    int trace_first;//从该道开始绘制
    int x_size;// 展示x_size个波形
    // Zoomer m_zoomer;
    Zoomer* m_zoomer;
    QwtPlotZoomer* zoomer;
    QwtPlotCanvas* m_canvas;
    QString icon_file_path;

    bool flag = true;//是否为炮号或线号绘制
    QVector<int> countInline;
    QVector<int> sourcesInline;
    int numInline=1;
    int checked;
//    bool cmp_esist;//
//    bool sor_esist;

    // 按钮
    QButtonGroup* btnGroup;
    QRadioButton *radioBtn1;//  = new QRadioButton();
    QRadioButton *radioBtn2; // = new QRadioButton();
    QRadioButton *radioBtn3;// = new QRadioButton();

    QPushButton* btn_workArea;// 工区底图


    // 函数
    int radio_button_checked();
    void waveP(int flag);
    void waveP_first();
    void on_pushButton_first_clicked(int flag);
    void on_pushButton_back_clicked(int flag);
    void on_pushButton_next_clicked(int flag);
    void on_pushButton_last_clicked(int flag);


    void updateEbcdicInfo();
    void updateVolumeInfo();
    void updateTraceHeadInfo();


    void setParameters();

    void loadData();
    void updateMicroseis();
    void updateDataInfo( const char *szFileName);
    void clearData();
    void waveP();
    void zoomIn(); // 放大缩小
    void zoomOut();
    void load_wave_data();// 加载绘制数据
    void window_scale_update();
    void restorePlotSize(QMouseEvent* event);// 恢复正常大小
    void fun_for_zommer();
    void layout_process();// 布局处理
    QFrame* layoutButtons(QVector<QPushButton*> buttons);
    void icon_gray(int i);
public slots:
    void handleCanvasButton(QVector<QPoint> points);// 连接处理Canvas
//    void handleCanvasButton2();
//    void handleCanvasButton3(int num);
private slots:


    void onRadioBtn1Clicked();
    void onRadioBtn2Clicked();
    void onRadioBtn3Clicked();

    void onQPushBtnClicked_workArea();

    void on_pushButton_chooseFile_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_originalSize_clicked();

    void on_pushButton_image_clicked();

    void on_pushButton_first_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_last_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_search_clicked();

    void on_pushButton_fill_zh_clicked();

    void on_pushButton_fill_fu_clicked();

    void on_pushButton_fill_no_clicked();

private:
    Ui::MainWindow *ui;
    void init_text();// 初始化文本
    void init_icon();// 初始化图标
    void init_parameter();// 参数初始化
    void prettify_button(QPushButton* button, QIcon icon);// 美化按钮
};
#endif // MAINWINDOW_H

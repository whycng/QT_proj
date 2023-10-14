

#include <QApplication>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QByteArray>


#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QTextCodec>

#include <QMessageBox>
#include <QString>
#include <QFileInfo>
#include <QModelIndex>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QSystemTrayIcon>
#include <QtGui>
#include <QListWidgetItem>
#include <QVector>

#include <QtWidgets>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <qwt_scale_draw.h>
#include <qwt_legend.h>
#include <qmath.h>
#include <iostream>

#include "mainwindow.h"
#include "csegyread.h"
#include "util.h"
#include "Zoomer.h"

QT_CHARTS_USE_NAMESPACE


// 输出指定目录下所有文件和文件夹
void PrintFiles(QDir dir){ // QDir dir("../shiyouFF");
    //当前目录
    QString currentDir = QDir::currentPath();
    qDebug() << "Current directory: " << currentDir;
    QStringList entries = dir.entryList();
    // 循环遍历列表并输出文件夹
    foreach (QString entry, entries) {
        if (entry != "." && entry != "..") {
            QString absPath = dir.absoluteFilePath(entry);
            if (QFileInfo(absPath).isDir()) {
                qDebug() << "Folder found: " << entry;
            } else if (QFileInfo(absPath).isFile()) {
                qDebug() << "File found: " << entry;
            }
        }
    }

}


CSegyRead m_segy;



QString m_strCurrentPath;
QString m_strCurrentFile;

QWidget *m_pTabHeader, *m_pTabData;

int m_nTraceHeaderByteValue;
int m_nCurrentEndianType;


int m_nGeophones; //检波器个数
int m_nTotalTraceNum;
int m_nTraceLen;
int m_nCurrentTraceNum;

int m_nComponent;  // X Y Z分量选择的组合，如果选中X和Y, 则为13+14=27
int m_nComponentX; // X分量=13
int m_nComponentY; // Y分量=14
int m_nComponentZ; // Z分量=12
int m_nTraceId;   //Y分量=14, X分量=13， Z分量=12
int m_nDisMode; //显示所有道为0， 以检波器显示为1


float m_nScale;

double absMax[100];






void updateEbcdicInfo();
void updateVolumeInfo();
void updateTraceHeadInfo();


void setParameters();

void loadData();
void updateMicroseis();

QFileInfo m_fileinfo;
QFileSystemModel *fileModel ;


QVector<QVector<double>*> m_Traces; //一个SEGY文件中所有道的数据

/*
void loadData()
{
    QVector<double>* m_ChangeData = nullptr;

    float* pTrace[m_nTotalTraceNum];
    double sampleValue = 0.0;

    qDebug() << "m_nTotalTraceNum: " <<m_nTotalTraceNum;
    for (int i=0; i<m_nTotalTraceNum; i++)
    {
        // 删除上一次循环创建的QVector<double>对象
        delete m_ChangeData;

        m_ChangeData = new QVector<double>(m_nTraceLen, sampleValue);
        pTrace[i] = m_segy.GetTraceData(i+1);

        //qDebug() << "pTrace[" << i << "][0]: " << pTrace[i][0];

        // 复制pTrace[i]中的数据到tempVector中
        QVector<double> tempVector;
        for (int k=0; k<m_nTraceLen; k++)
        {
            tempVector.append(pTrace[i][k]);
        }

        double absMax = 0.0;
        GetVectorMax(tempVector, absMax);

        if (absMax != 0.0)
        {
            for (int k=0; k<m_nTraceLen; k++)
            {
                (*m_ChangeData)[k] = tempVector[k] / absMax;
            }
        }
        //qDebug() << "m_ChangeData[0]: " << m_ChangeData->at(0);
        m_Traces.append(m_ChangeData);
        //qDebug() << "m_Traces[" << i << "][0]:" << m_Traces[i]->at(0) ;
    }

    for(int i=0;i<m_Traces.count();i++){
        qDebug() << "m_Traces[" << i << "][0]:" << m_Traces[i]->at(0) ;
    }

}
*/

void loadData()
{

    float* pTrace[m_nTotalTraceNum];
    double sampleValue = 0.0;
    QVector<double>* m_ChangeData = new QVector<double>(m_nTraceLen, sampleValue);

    qDebug() << "m_nTotalTraceNum: " <<m_nTotalTraceNum;
    for (int i=0; i<m_nTotalTraceNum; i++)
    {
        QVector<double>* m_ChangeData = new QVector<double>(m_nTraceLen, sampleValue);
        pTrace[i] = m_segy.GetTraceData(i+1);

        //qDebug() << "pTrace[" << i << "][0]: " << pTrace[i][0];

        // 复制pTrace[i]中的数据到tempVector中
        QVector<double> tempVector;
        for (int k=0; k<m_nTraceLen; k++)
        {
            tempVector.append(pTrace[i][k]);
        }

        double absMax = 0.0;
        GetVectorMax(tempVector, absMax);

        if (absMax != 0.0)
        {
            for (int k=0; k<m_nTraceLen; k++)
            {
                // (*m_ChangeData)[k] = tempVector[k] / absMax;
                (*m_ChangeData)[k] = tempVector[k] ;  // test?
            }
        }

        //qDebug() << "m_ChangeData[0]: " << m_ChangeData->at(0);
        m_Traces.append(m_ChangeData);
        //qDebug() << "m_Traces[" << i << "][0]:" << m_Traces[i]->at(0) ;
    }

    //    for(int i=0;i<m_Traces.count();i++){
    //        qDebug() << "m_Traces[" << i << "][0]:" << m_Traces[i]->at(0) ;
    //    }


}



void updateDataInfo( const char *szFileName)
{

    if(!m_segy.OpenFile(szFileName))
    {
        qDebug() << "-- fun:updateDataInfo";
        //QMessageBox::information("-- fun:updateDataInfo")
        //QMessageBox::information(this, tr("Open SEGY File"), tr("SEGY file open failed!"));
        return;
    }


    setParameters();

    loadData();
    // updateMicroseis();



}

void setParameters()
{

    m_nTotalTraceNum=m_segy.getTotalTraceNumber();
    m_nTraceLen = m_segy.getSamplesNumber();
    m_nGeophones = m_nTotalTraceNum/3;


}

void clearData()
{
    int i,j;
    if (!m_Traces.isEmpty())
    {
        i=m_Traces.count();
        for(j=i-1;j>=0;j--)
            m_Traces[j]->clear();
        m_Traces.clear();
    }
}

//int m_nGeophones; //检波器个数

/*m_TempValue=1+i+m_TempValue;这一步是将波形沿着纵轴方向进行平移。其中，1表示从y=1的位置开始绘制，
     * i表示当前波形的编号，即y轴偏移的距离，m_TempValue则表示x轴偏移的距离。

    这一步的目的是为了避免多条波形重叠在一起，使得每个波形都可以在图表上清晰地显示出来。同时，
    也能够让用户更加直观地比较不同波形之间的差异。


根据代码中的 `for(i=0;i<m_nGeophones*3;i++)`，可以知道 `m_Traces` 存储了 `m_nGeophones*3` 个波形数
据。每个波形数据包含三个分量（X、Y、Z）的数据，其中第一个分量对应 X 方向，第二个分量对应 Y 方向，第三个分量
对应 Z 方向。因此，可以将 `m_Traces` 视为一个二维数组，第一维表示 SEGY 文件中每个道的索引，第二维表示每个
道对应的三个分量。

具体来说，假设 `m_nGeophones` 表示 SEGY 文件中道数的总数，则 `m_Traces` 的结构可以表示为：

```
m_Traces[0]   // 第一道X方向的波形数据
m_Traces[1]   // 第一道Y方向的波形数据
m_Traces[2]   // 第一道Z方向的波形数据
m_Traces[3]   // 第二道X方向的波形数据
m_Traces[4]   // 第二道Y方向的波形数据
m_Traces[5]   // 第二道Z方向的波形数据
...
m_Traces[m_nGeophones*3-3]  // 最后一道X方向的波形数据
m_Traces[m_nGeophones*3-2]  // 最后一道Y方向的波形数据
m_Traces[m_nGeophones*3-1]  // 最后一道Z方向的波形数据
```

因此，你的理解是正确的。在 `for` 循环中，变量 `i` 的范围是从 0
到 `m_nGeophones*3-1`，每次循环处理一个道（包含三个分量）的数据。


*/
void wavePlot()
{



}

// 判断数组与数组是否有重复
void testDup(){
    QSet<double> mySet;

    for (const auto& array : m_Traces) {
        mySet.unite(QSet<double>::fromList(array->toList()));
    }

    if (mySet.size() == std::accumulate(m_Traces.begin(), m_Traces.end(), 0.0, [](double sum, const QVector<double>* v) { return sum + v->size(); }
                                        )) {
        qDebug() << "No duplicates found.";
    } else {
        qDebug() << "Duplicates found.";
    }

}

void test(){
    // test
    for(int i=0;i<m_nGeophones *3;i++)
    {
        // m_TempData.clear();
        qDebug() << "(*m_Traces["<< i << "])[400]" << (*m_Traces[i])[400] << " "<< (*m_Traces[i])[401] << " " << (*m_Traces[i])[402] << " " << (*m_Traces[i])[403] << " " <<(*m_Traces[i])[404];
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建共享内存对象
    QSharedMemory sharedMem("myApp");

    // 尝试将共享内存锁定
    if (!sharedMem.create(1)) {
        QMessageBox::warning(nullptr, "警告", "程序已经在运行中！");
        return 1;
    }

    // 主窗口
    MainWindow w;
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    w.resize(screenGeometry.width(), screenGeometry.height());
    w.setWindowState(Qt::WindowMaximized);
    w.show();


    // 测试 curve
//    QVector<double> x_data = {1,2,3,7,8,9,   7,  1};
//    QVector<double> y_data = {1,3,1,0.5,3,2, 0.5,1 };
//    test_PLotCurve(y_data, x_data);


    qDebug() << "main over--";
    return a.exec();
}

#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <chrono>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    // 参数初始化
    init_parameter();
    // 文本初始化
    init_text();
    // 图标初始化
    init_icon();
    // 布局处理
    layout_process();

    m_zoomer = nullptr;
    icon_file_path = "";

// 测试
    // 初始化为10
    ui->comboBox->setCurrentIndex(0);

    qDebug() << "init value: " << ui->comboBox->currentText();

    // 设置文本为100
    ui->comboBox->setCurrentText("100");

    qDebug() << "set text: " << ui->comboBox->currentText();

    // update刷新
    ui->comboBox->update();

    qDebug() << "after update: " << ui->comboBox->currentText();



}



MainWindow::~MainWindow()
{
    delete ui;
}

// 布局处理
void MainWindow::layout_process(){
    // 布局处理
    int num_btn = 12;
    QPushButton *btns[12] = {ui->pushButton_chooseFile, ui->pushButton_add, ui->pushButton_minus,
                             ui->pushButton_originalSize, /*ui->pushButton_color,*/ ui->pushButton_image,
                             ui->pushButton_first,ui->pushButton_back,ui->pushButton_next,
                             ui->pushButton_last, ui->pushButton_fill_zh,ui->pushButton_fill_fu,
                             ui->pushButton_fill_no, };
    /* pushButton_search pushButton_image pushButton_add pushButton_minus

pushButton_overscan pushButton_originalSize pushButton_color

pushButton_chooseFile pushButton_fill_zh pushButton_fill_fu pushButton_fill_no*/

    // 调整按钮大小--prettify_button
    // 去掉按钮的名字
    for(int i=0;i<num_btn;i++)
    {
        btns[i]->setText("");
    }
    ui->pushButton_search->setText("");// 查找没放在btns里面

    QWidget* mainWidget = new QWidget();

    // 总体垂直布局
    /*
    总体
        上半部分
            第一行
            第二行
            第三行
        下半部分

    */
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0); // 没变化--tmp--应该是设置了上下左右距离

    // 上半部分
    QWidget* topContainer = new QWidget();
    topContainer->setFixedHeight(90);// 上半部分的高度
    topContainer->setAutoFillBackground(true);
    topContainer->setPalette(QPalette(QColor("#EEE")));

    QVBoxLayout* topLayout = new QVBoxLayout(topContainer);
    topLayout->setSpacing(0);// 没变化--tmp

    // 第一行按钮
    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    // 设置布局间距为0个单位
    firstRowLayout->setSpacing(0);
    // 设置对齐方式为居左对齐
    firstRowLayout->setAlignment(Qt::AlignLeft);

    for(int i=0; i<5; i++){
        firstRowLayout->addWidget(btns[i]);
    }
    // 分割线，美观
    firstRowLayout->addWidget(new QFrame());
    QFrame *line = new QFrame();
    line->setFrameStyle(QFrame::VLine | QFrame::Sunken);
    firstRowLayout->addWidget(line);
    // 合并第二行
    for(int i=5; i<12; i++){
        firstRowLayout->addWidget(btns[i]);
    }

    // 第三行按钮
    QHBoxLayout* thirdRowLayout = new QHBoxLayout();

    QFrame *frame = new QFrame();
    frame->setFixedSize(600, 50);

    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->addWidget(ui->pushButton_search);// 查找按钮

    QFrame *frame_text_edit = new QFrame();
    //frame_text_edit->setFixedSize(130, 50); 导致只能从底层往上50个距离，导致无法居中 ?
    frame_text_edit->setMinimumSize(0, 50);
    QVBoxLayout *layout_text_edit = new QVBoxLayout(frame_text_edit);
    layout_text_edit->addWidget(ui->textEdit_2);

    radioBtn1 = new QRadioButton();
    radioBtn2 = new QRadioButton();
    radioBtn3 = new QRadioButton();
    btnGroup = new QButtonGroup();
    btnGroup->addButton(radioBtn1);
    btnGroup->addButton(radioBtn2);
    btnGroup->addButton(radioBtn3);
    btnGroup->setExclusive(true);// 按钮设置互斥
    radioBtn1->setChecked(true);// 默认选中第一个
    radioBtn1->setText("默认");
    radioBtn2->setText("Sources");
    radioBtn3->setText("CMP line");



    layout_text_edit->addStretch();//弹簧

    layout->addWidget(frame_text_edit); // 查找输入数字，文本编辑框，设置一定大小
    layout->addWidget(ui->label);// 道集大小文本
    layout->addWidget(ui->comboBox);// 选择道集
    layout->addWidget( radioBtn1);
    layout->addWidget( radioBtn2);
    layout->addWidget( radioBtn3);
    //...添加其他控件

    thirdRowLayout->addWidget(frame);
    thirdRowLayout->addStretch();


    topLayout->addLayout(firstRowLayout);
    // topLayout->addLayout(secondRowLayout);
    topLayout->addLayout(thirdRowLayout);

    // 下半部分
    QWidget* bottomContainer = new QWidget();
    bottomContainer->setAutoFillBackground(true);
    bottomContainer->setPalette(QPalette(QColor("#FFF")));
    // bottomContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* bottomLayout = new QVBoxLayout(bottomContainer);
    ui->qwtPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //ui->qwtPlot->setMinimumSize(100, 400);
//    ui->qwtPlot->setMaximumSize(2000, 2000);
    bottomLayout->addWidget(ui->qwtPlot);
    // bottomLayout->addStretch(); // 添加弹簧

    mainLayout->addWidget(topContainer);
    mainLayout->addWidget(bottomContainer);

    //mainLayout->addStretch();
    // mainLayout->setContentsMargins(10, 10, 10, 10);

    // setLayout(mainLayout);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    //----------------------
    // 槽函数设置
    connect(radioBtn1, &QRadioButton::clicked, this, &MainWindow::onRadioBtn1Clicked);

    connect(radioBtn2, &QRadioButton::clicked, this, &MainWindow::onRadioBtn2Clicked);

    connect(radioBtn3, &QRadioButton::clicked, this, &MainWindow::onRadioBtn3Clicked);
}

// 检测哪个被选中
int MainWindow::radio_button_checked(){
    bool checked1 = radioBtn1->isChecked();
    bool checked2 = radioBtn2->isChecked();
    bool checked3 = radioBtn3->isChecked();
    if(checked1) return 1;
    if(checked2) return 2;
    if(checked3) return 3;
}


// 默认
void MainWindow::onRadioBtn1Clicked() {
    // radioBtn1被点击后的处理
    if(is_data_loaded){
        checked = radio_button_checked();
        waveP();
    } else {

    }
}

// sources
void MainWindow::onRadioBtn2Clicked() {
    // radioBtn2被点击后的处理
    if(is_data_loaded && sourcesInline.size() > 2 ){
        checked = radio_button_checked();
        waveP(1);//sor
    } else{
        qDebug() << "ERR onRadioBtn2Clicked";
        radioBtn2->setChecked(false);
        if(checked==1){
            radioBtn1->setChecked(true);
        } else if(checked==3){
            radioBtn3->setChecked(true);
        }
    }
}

// cmp line
void MainWindow::onRadioBtn3Clicked() {
    bool checked1 = radioBtn1->isChecked();
    bool checked2 = radioBtn2->isChecked();
    bool checked3 = radioBtn3->isChecked();
    if(checked1){
        qDebug() << "checked1";
    }
    if(checked2){
        qDebug() << "checked2";
    }
    if(checked3){
        qDebug() << "checked3";
    }
    // radioBtn3 cmp 被点击后的处理
    if(is_data_loaded && countInline.size() > 2){//
        checked = radio_button_checked();
        waveP(2);// cmp
    } else {
        qDebug() << "ERR onRadioBtn3Clicked" << "  checked:" << checked;
        radioBtn3->setChecked(false);
        if(checked==1){
            radioBtn1->setChecked(true);
        } else if(checked==2){
            radioBtn2->setChecked(true);
        }
    }
}


void MainWindow::init_parameter(){

//    cmp_esist = false;
//    sor_esist = false;
    checked = 1;// 初始化选择默认按钮
    is_data_loaded = false;// 默认加载数据
    file_sgy_path = QString();// 初始为空
    draw_mode = 1;// 绘制模式 1.正填充
    x_size = 100; // 默认绘制100道数据

    icon_file_path = "E:/Proj/QtProj/shiyouT/icon/";

// 无法初始化comboBox的值
//    ui->comboBox->setCurrentIndex(0);
//    ui->comboBox->setCurrentText(QString::number(x_size));
//    ui->comboBox->update();


//    // 初始化为10
//    ui->comboBox->setCurrentIndex(0);

//    qDebug() << "init value: " << ui->comboBox->currentText();

//    // 设置文本为100
//    ui->comboBox->setCurrentText("100");

//    qDebug() << "set text: " << ui->comboBox->currentText();

//    // update刷新
//    ui->comboBox->update();

//    qDebug() << "after update: " << ui->comboBox->currentText();

    trace_first = 0;// 默认从第一道开始绘制

    // 下拉框数值
    ui->comboBox->addItem("10");
    ui->comboBox->addItem("20");
    ui->comboBox->addItem("40");
    for(int i = 50; i < 500 ; i+=50){
        ui->comboBox->addItem(QString::number(i));
    }

}


//处理按钮文本与图像的样式，原32x32
void MainWindow::prettify_button(QPushButton* button, QIcon icon){
    // QPushButton* button = ui->pushButton_back;
    button->setStyleSheet("QPushButton {"
                          "text-align: center;"
                          "background-color: transparent;"
                          "border: none;"
                          "}"
                          "QPushButton::indicator {"
                          "width: 0; height: 0;"
                          "}");

    QLabel* label = new QLabel(button);
    label->setPixmap(icon.pixmap(QSize(32, 32)));  // 调整图标的大小 32x32
    label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    QVBoxLayout* layout = new QVBoxLayout(button);
    layout->setContentsMargins(0, 0, 0, 0);  // 去除布局的边距
    layout->addWidget(label);
    layout->addWidget(button, 1, Qt::AlignHCenter | Qt::AlignTop);  // 使用布局中的剩余空间来放置按钮

    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);  // 设置按钮的大小策略为在垂直方向上尽量小

    // 可选：调整按钮的最小尺寸
    button->setMinimumSize(QSize(50, 50));  // 根据需要设置最小尺寸 80x80,正常 100x135
//    button->setMaximumSize(QSize(150,150));
}

void MainWindow::init_icon(){
    //QString t = "E:/Proj/QtProj/shiyouT/icon/";//
    QString t = "../shiyouT/icon/";

// 原
//    QIcon icon(t + "back.png");
//    ui->pushButton_back->setIcon(icon);

    QString iconPath = t + "back2.png";
    QIcon icon(iconPath);
    prettify_button(ui->pushButton_back,icon);// 下面操作用函数代替


    icon = QIcon(t + "forward2.png");
    prettify_button(ui->pushButton_next,icon);
    // ui->pushButton_next->setIcon(icon);

    icon = QIcon(t + "first2.png");
    prettify_button(ui->pushButton_first,icon);
    // ui->pushButton_first->setIcon(icon);

    icon = QIcon(t + "last2.png");
    prettify_button(ui->pushButton_last,icon);
    // ui->pushButton_last->setIcon(icon);

    icon = QIcon(t + "search2.png");
    prettify_button(ui->pushButton_search,icon);
    // ui->pushButton_search->setIcon(icon);

    icon = QIcon(t + "image2.png");
    prettify_button(ui->pushButton_image,icon);
    // ui->pushButton_image->setIcon(icon);

    icon = QIcon(t + "add2.png");
    prettify_button(ui->pushButton_add,icon);
    // ui->pushButton_add->setIcon(icon);//original-size

    icon = QIcon(t + "minus2.png");
    prettify_button(ui->pushButton_minus,icon);
    // ui->pushButton_minus->setIcon(icon);

    icon = QIcon(t + "overscan2.png"); // 22
    prettify_button(ui->pushButton_overscan,icon);
    // ui->pushButton_overscan->setIcon(icon);

    icon = QIcon(t + "original-size2.png");
    prettify_button(ui->pushButton_originalSize,icon);
    // ui->pushButton_originalSize->setIcon(icon);

    icon = QIcon(t + "color2.png");
    prettify_button(ui->pushButton_color,icon);
    // ui->pushButton_color->setIcon(icon);

    icon = QIcon(t + "file2.png");
    prettify_button(ui->pushButton_chooseFile,icon);
    // ui->pushButton_chooseFile->setIcon(icon);

    icon = QIcon(t + "fill_zh.png");
    prettify_button(ui->pushButton_fill_zh,icon);
    // ui->pushButton_chooseFile->setIcon(icon);

    icon = QIcon(t + "fill_fu.png");
    prettify_button(ui->pushButton_fill_fu,icon);
    // ui->pushButton_chooseFile->setIcon(icon);

    icon = QIcon(t + "fill_no.png");
    prettify_button(ui->pushButton_fill_no,icon);
    // ui->pushButton_chooseFile->setIcon(icon);
}

void MainWindow::init_text(){
    // 创建 QTextCharFormat 对象并设置样式
    QTextCharFormat textFormat;
    textFormat.setFontPointSize(12); // 设置字体大小为 12
    textFormat.setFontWeight(QFont::Bold); // 设置字体粗细为粗体
    textFormat.setForeground(Qt::red); // 设置字体颜色为红色

    // 在 QTextEdit 中插入文本并应用样式
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->textCursor().insertText("点击【选择文件】打开sgy文件，进行绘制，默认正填充", textFormat);

    // 可以继续添加其他样式的文本...

}

// 加载数据
void MainWindow::loadData()
{
    num_line = 0;
    // 查看线号，道号 VOLUMEHEADER &ReadVolumeHeader();
    int lino = m_segy.GetVolumeHeader().lino;
    int reno = m_segy.GetVolumeHeader().reno;// 卷号
    short ntrpr = m_segy.GetVolumeHeader().ntrpr;
    unsigned short hns = m_segy.GetVolumeHeader().hns;
    qDebug() << "[Message]1. lino线号：" << lino
        << ",reno卷号：" << reno
        << ",ntrpr:" << ntrpr
        << ",hns:" << hns;
//    数据一样的
//    VOLUMEHEADER volumeHeader = m_segy.ReadVolumeHeader();
//    qDebug() << "[Message]2. lino线号：" << volumeHeader.lino
//        << ",reno卷号：" << volumeHeader.reno
//        << ",ntrpr:" << volumeHeader.ntrpr
//        << ",hns:" << volumeHeader.hns;

    double sampleValue = 0.0;
    QVector<double>* m_ChangeData = new QVector<double>(m_nTraceLen, sampleValue);
    // 绘制进度条
//    QProgressDialog progressDialog("数据加载", "取消", 0, m_nTotalTraceNum, this);
//    progressDialog.setWindowModality(Qt::WindowModal);
//    progressDialog.setMinimumDuration(0);

    countInline.push_back(0);
    sourcesInline.push_back(0);
    qDebug() << "[Message]m_nTotalTraceNum: " <<m_nTotalTraceNum;
    // 开辟空间 --fix
    traces = (float**)alloca(m_nTotalTraceNum * sizeof(float*));
    for (int i=0; i<m_nTotalTraceNum; i++) // m_nTotalTraceNum -> m_nTraceLen
    {
        // 进度 170mb的数据，啥也不做，跑完循环6s;正常7s


        // 内存会被释放掉，导致没数据
        // 没啥区别，值拿到了
        traces[i] = m_segy.GetTraceData(i+1);// 单这一个循环下来 1.07s

        QVector<double>* m_ChangeData = new QVector<double>(m_nTraceLen, sampleValue);

        //7.27 CMP Line 大概花费了0.25s
        //Source
        if(m_segy.ReadTraceHeader(i+1).iOriNum != m_segy.ReadTraceHeader(i+2).iOriNum){

            sourcesInline.push_back(i+1);//
        } else {
            // 没有 sources模式
        }
        //CMP Line
        if(m_segy.ReadTraceHeader(i+1).Inline3D != m_segy.ReadTraceHeader(i+2).Inline3D){
            countInline.push_back(i+1);
            num_line++;
        } else {
            // 没用 cmp模式
        }

        double absMax = 0.0; // 最大值
        GetVectorMaxP(traces[i], m_nTraceLen, absMax);


        if (absMax != 0.0)
        {
            for (int k=0; k<m_nTraceLen; k++)
            {
                traces[i][k] /= absMax;
                (*m_ChangeData)[k] = traces[i][k];
                // 1. qDebug() << "[message] taces[" << i << "][" << k << "]= " << traces[i][k];
            }
        }

        // qDebug() << "[Message]<LoadData> traces:" << traces[i][0];
        m_Traces.append(m_ChangeData);
    }

    countInline.push_back(m_nTotalTraceNum);
    sourcesInline.push_back(m_nTotalTraceNum);

    // 经过循环拿到线号
    qDebug() << "[Message]num_line:" << num_line;
    // 判断该线号和卷头文件的线号是否相同
    if(m_segy.GetVolumeHeader().lino == num_line)
    {
        // 相同
    }
    else
    {
        qDebug() << "[Warning] 循环得出的线号和卷头文件给的线号不同";
    }

    //拿到数据
//    for(int i=0;i<100;i++)
//        qDebug() << "[Message] traces["<< i <<"]:" << traces[i][0];
}


// 参数初始化
void MainWindow::setParameters()
{

    m_nTotalTraceNum=m_segy.getTotalTraceNumber();
    m_nTraceLen = m_segy.getSamplesNumber();
    m_nGeophones = m_nTotalTraceNum/3;
    qDebug() << "[Message]<setParameters> m_nTotalTraceNum:" << m_nTotalTraceNum
        << "  m_nTraceLen:" << m_nTraceLen << "   m_nGeophones:" << m_nGeophones;

}

void MainWindow::clearData()
{
    int i,j;
    if (!m_Traces.isEmpty())
    {
        i=m_nTotalTraceNum;
        for(j=i-1;j>=0;j--)
            m_Traces[j]->clear();
        m_Traces.clear();
    }
}

// 放大
// Function to handle zoom-in operation
void MainWindow::zoomIn()
{
    // Get the current axis ranges
    double xmin = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
    double xmax = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).upperBound();
    double ymin = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).lowerBound();
    double ymax = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).upperBound();

    // Calculate the new axis ranges for zoom-in (e.g., reduce the range by half)
    double new_xmin = xmin + (xmax - xmin) / 4;
    double new_xmax = xmax - (xmax - xmin) / 4;
    double new_ymin = ymin + (ymax - ymin) / 4;
    double new_ymax = ymax - (ymax - ymin) / 4;

    // Set the new axis ranges
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, new_xmin, new_xmax);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, new_ymin, new_ymax);

    // Replot the graph
    ui->qwtPlot->replot();
}

// Function to handle zoom-out operation
void MainWindow::zoomOut()
{
    // Get the current axis ranges
    double xmin = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
    double xmax = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).upperBound();
    double ymin = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).lowerBound();
    double ymax = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).upperBound();

    // Calculate the new axis ranges for zoom-out (e.g., increase the range by half)
    double new_xmin = xmin - (xmax - xmin) / 2;
    double new_xmax = xmax + (xmax - xmin) / 2;
    double new_ymin = ymin - (ymax - ymin) / 2;
    double new_ymax = ymax + (ymax - ymin) / 2;

    // Set the new axis ranges
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, new_xmin, new_xmax);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, new_ymin, new_ymax);

    // Replot the graph
    ui->qwtPlot->replot();

}

// 加载sgy数据-判断路径
void MainWindow::load_wave_data(){
    // 数据只需加载一次
    qDebug() << "file_sgy_path: " << file_sgy_path;
    // updateDataInfo("E:\\Proj\\QtProj\\item2_mig.sgy");
    // 将 QString 转换成 QByteArray
    QByteArray byteArray = file_sgy_path.toUtf8(); // 或者使用 toLocal8Bit()，根据需要选择编码方式
    // 将 QByteArray 转换成 const char*
    const char* charArray = byteArray.constData();
    qDebug() << charArray;

    if(!m_segy.OpenFile(charArray))
    {
        qDebug() << "[Error]from functuion:updateDataInfo";
        return;
    }
    setParameters();
    auto start = std::chrono::high_resolution_clock::now();
    loadData();

//    for(int i=0;i<100;i++)
//        qDebug() << "[Message] traces["<< i <<"]:" << traces[i][0];

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed = duration.count() * 1e-6; // microseconds to seconds

    QString elapsed_str = QString::number(elapsed, 'f', 5); // 精确到5位小数

    qDebug() << "[Message]Elapsed time xx:" << elapsed_str << " seconds";
    // qDebug() << "[Message]Elapsed time: " << duration.count()   << " microseconds";

}

// 原始绘图
void MainWindow::waveP_first(){

    // 更改坐标，用于zoomer返回上一步 --test
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(trace_first) + double(x_size));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
    qDebug() << "[Message]trace_first:" << trace_first;


    // 初始化参数
    m_nCurrentEndianType = 0;
    m_nCurrentTraceNum = 1;
    // 以下三者为初始化数据，经updateDataInfo 更新
    //    m_nGeophones =12; //检波器个数
    //    m_nTotalTraceNum=100;
    //    m_nTraceLen=100;
    // absMax[100]={0}; // 没用？

    m_nTraceHeaderByteValue = 4;
    m_nComponent=14;
    m_nScale=1.0;
    m_nDisMode =0;

    // int mode = 3;// 三种模式，1.正填充 2.负填充 3.不填充
    // int x_size = 100; // x_size个波形 -->全局变量
    QTime timedebuge;//声明一个时钟对象
    timedebuge.start();//开始计时

    //    // 数据只需加载一次
    //    // 执行
    //    // updateDataInfo("C:\\Qt\\item2_mig.sgy"); // "E:\\Proj\\QtProj\\item2_mig.sgy"  file_sgy_path
    //    qDebug() << "file_sgy_path: " << file_sgy_path;
    //    // updateDataInfo("E:\\Proj\\QtProj\\item2_mig.sgy");
    //    // 将 QString 转换成 QByteArray
    //    QByteArray byteArray = file_sgy_path.toUtf8(); // 或者使用 toLocal8Bit()，根据需要选择编码方式
    //    // 将 QByteArray 转换成 const char*
    //    const char* charArray = byteArray.constData();
    //    qDebug() << charArray;
    //    if(charArray){
    //        updateDataInfo(charArray);// 问题
    //    } else {
    //        qDebug() << "size of charArray:" << sizeof(charArray);
    //        qDebug() << "路径问题";
    //    }


    //int rectY; //放大缩小矩形框纵坐标大小
    int i,k;
    double j=0.0;
    double m_TempValue;
    double m_TempValueBackup;

    QVector<double> m_TempData;
    QVector<double> vectorX3c;
    QVector<double> m_TempDataBackup;

    // 绘制前清除
    ui->qwtPlot->detachItems();
    vectorX3c.clear();



    //    QList<QwtPlotCurve*> m_curveList;

    for (int i=0; i<m_nTraceLen; i++)
    {
        vectorX3c<<j; // vectorX3c: 0.0 1.0 2.0 ...
        j+=1.0;
    }


    // 绘制进度条
    //    QProgressDialog progressDialog("绘制进度", "取消", 0, x_size, this);
    //    progressDialog.setWindowModality(Qt::WindowModal);
    //    progressDialog.setMinimumDuration(0);


    // x_size个波形；从i= trace_first 到 trace_first + x_size
    for( i = trace_first ;i< trace_first + x_size; i++)
    {
        // 进度条
        //        progressDialog.setValue(i);
        //        // 检查用户是否点击了取消按钮
        //        if (progressDialog.wasCanceled()) {
        //            // 清除所有容器... --tmp

        //            // 取消绘制操作
        //            break;
        //        }

        // m_TempData.clear();

        for(k=0;k<m_Traces[i]->count();k++)
        {
            m_TempValue=(*m_Traces[i])[k];

            //            qDebug()<<m_TempValue;
            m_TempValueBackup=(*m_Traces[i])[k];


            m_TempValue=m_nScale*m_TempValue;  //显示波形的幅度
            m_TempValue=1+i+m_TempValue;
            m_TempData<<m_TempValue;
            m_TempDataBackup<<m_TempValue;

        }

        QVector<QVector<double>> m_Segments;
        QVector<QVector<double>> m_y;
        QVector<QColor> m_Colors;

        //        const double threshold = 0.0; // 分割点的阈值

        // 遍历 m_TempDataBackup 中的数据
        int start = 0;
        for (int k = 1; k < m_TempDataBackup.size(); k++) {
            // 判断当前数据是否与上一个数据符号相反
            if ((m_TempDataBackup[k]-(i+1)) * (m_TempDataBackup[k-1]-(i+1)) < 0) {
                // 符号相反或者数据过小，认为需要分段
                QVector<double> segment;
                QVector<double> y;

                segment.append(i+1);
                for (int j = start; j < k; j++) {
                    segment.append(m_TempDataBackup[j]);
                    y.append(j+1);
                }
                y.append(k+1);
                y.append(k+2);
                segment.append(i+1);

                m_Segments.append(segment);
                m_y.append(y);
                start = k;
            }
        }

        // 处理最后一段数据
        if (start < m_TempDataBackup.size()) {
            QVector<double> segment;
            QVector<double> y;
            segment.append(i+1);
            for (int j = start; j < m_TempDataBackup.size(); j++) {
                segment.append(m_TempDataBackup[j]);
                y.append(j+1);
            }
            segment.append(i+1);
            y.append(k+1);
            y.append(k+2);
            m_Segments.append(segment);
            m_y.append(y);
        }
        switch (draw_mode){
        case 1:{// 正填充
            for(int k=0;k<m_Segments.size();k++){
                QwtPlotCurve *curve = new QwtPlotCurve;
                curve->setSamples(m_Segments[k],m_y[k]);// x轴  y轴数据，坐标

                // 遍历 m_Segments，根据读取到小容器的正负对该段数据填充不同的颜色

                QVector<double> segment = m_Segments[k];
                QColor color;
                if (segment[1]-(i+1) > 0) {
                    // 正数填充黑色
                    //
                    color = QColor(Qt::black);
                    QBrush brush(color);

                    curve->setBrush(brush);

                } else {
                    // 负数填充白色
                    //
                    color = QColor(Qt::white);
                    QBrush brush(color);
                    curve->setBrush(brush);

                }
                m_Colors.append(color);

                //启用抗锯齿渲染模式
                curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

                // 将曲线添加到 QwtPlot 上
                // curve->attach(plot);
                // 更换到 qwtPlot控件
                curve->attach(ui->qwtPlot);
                m_TempDataBackup.clear();
                //            m_y.clear();
            }
            break;
        }
        case 2:{// 负填充  m_Segments内存储的是容器
            for(int k=0;k<m_Segments.size();k++){
                QwtPlotCurve *curve = new QwtPlotCurve;
                curve->setSamples(m_Segments[k],m_y[k]);// x轴  y轴数据，坐标

                // 遍历 m_Segments，根据读取到小容器的正负对该段数据填充不同的颜色

                QVector<double> segment = m_Segments[k];
                QColor color;
                if (segment[1]-(i+1) > 0) {
                    // 正数
                } else {
                    // 负数填充黑色
                    color = QColor(Qt::black);
                    QBrush brush(color);
                    curve->setBrush(brush);
                }
                m_Colors.append(color);

                //启用抗锯齿渲染模式
                curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

                // 将曲线添加到 QwtPlot 上
                // curve->attach(plot);
                // 更换到 qwtPlot控件
                curve->attach(ui->qwtPlot);
                m_TempDataBackup.clear();
                //            m_y.clear();
            }
            break;
        }
        case 3:{
            for(int k=0;k<m_Segments.size();k++){
                QwtPlotCurve *curve = new QwtPlotCurve;
                curve->setSamples(m_Segments[k],m_y[k]);// x轴  y轴数据，坐标
                curve->attach(ui->qwtPlot);
                m_TempDataBackup.clear();
            }

            break;
        }
        default:{

            break;
        }
        }
        // qDebug()<<"正在添加第 " << i << "道数据到plot上;  "<< "m_Traces[i]->count()"<<"i:"<<i<<","<<m_Traces[i]->count();
    }

    // 绘制完成后隐藏进度条
    //    progressDialog.hide();

    // 清理
    //    foreach (QwtPlotCurve *curve, m_curveList) {
    //        delete curve;
    //    }
    //    m_curveList.clear();

    // 设置坐标轴范围和标签
    //    plot->setAxisTitle(QwtPlot::yLeft, "Time");
    //    plot->setAxisTitle(QwtPlot::xBottom, "Channel");


    //plot->setAxisScale(QwtPlot::yLeft, 0.0, 10);

    //    qDebug()<<"正在绘制...";

    // 添加图例
    //    QwtLegend* legend = new QwtLegend();
    //    plot->insertLegend(legend, QwtPlot::RightLegend);
    // 显示 QwtPlot
    //    plot->resize(1200, 1200);
    //    plot->show();

    //
    // QwtPlotCurve *curve = new QwtPlotCurve();
    // curve->attach(ui->qwtPlot);

    /*  用于缩放
    //m_zoomer = new Zoomer(m_canvas, QRectF(double(trace_first), 0.0, double(x_size), m_nTraceLen), true);
//    m_zoomer->xMin = double(trace_first) ;
//    m_zoomer->xMax = double(trace_first) + double(x_size);
//    m_zoomer->yMin = 0.0;
//    m_zoomer->yMax = m_nTraceLen;
//    m_zoomer->z_qwtPlot = ui->qwtPlot;
*/
    fun_for_zommer();

    // 设置 x 轴和 y 轴范围
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(trace_first) + double(x_size));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);

    // 重新绘制图形
    ui->qwtPlot->replot();

    // clearData(); 数据还能用到

    qDebug() << "wave over--";
    qDebug()<<"[Message]<waveP first()>程序耗时："<<timedebuge.elapsed()/1000.0<<"s";//输出计时
}



// 绘制函数 改
void MainWindow::waveP(){


    // 更改坐标，用于zoomer返回上一步 --test
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(trace_first) + double(x_size));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
    qDebug() << "trace_first:" << trace_first;


    // 初始化参数
    m_nCurrentEndianType = 0;
    m_nCurrentTraceNum = 1;

    m_nTraceHeaderByteValue = 4;
    m_nComponent=14;
    m_nScale=1.0;
    m_nDisMode =0;

    // 计时
    QTime timedebuge;//声明一个时钟对象
    timedebuge.start();//开始计时
    auto start = std::chrono::high_resolution_clock::now();// 另一个计时方法


    //int rectY; //放大缩小矩形框纵坐标大小
    int i,k;
    double j=0.0;
    double m_TempValue;
    double m_TempValueBackup;

    QVector<double> m_TempData;
    QVector<double> vectorX3c;
    QVector<double> m_TempDataBackup;
    // std::vector<double> wave_amplitudes;// 替代m_TempDataBackup

    // 用于测试
    //draw_mode=3;
    // 绘制前清除
    ui->qwtPlot->detachItems();
    vectorX3c.clear();
//    if(draw_mode == 3 )//不填充模式 --  填充模式的x值不是与y值一一对应的
//    {
//        // 纵坐标给值
//        for (int i=0; i<m_nTraceLen; i++)
//        {
//            vectorX3c<<j; // vectorX3c: 0.0 1.0 2.0 ...
//            j+=1.0;
//        }
//    }
    for (int i=0; i<m_nTraceLen; i++)
    {
        vectorX3c<<j; // vectorX3c: 0.0 1.0 2.0 ...
        j+=1.0;
    }



    // x_size个波形；从i= trace_first 到 trace_first + x_size
    double index = 0;
    for( i = trace_first ;i< trace_first + x_size; i++)
    {



        for(k=0;k<m_Traces[i]->count();k++)
        {
            m_TempValue=(*m_Traces[i])[k];

            //            qDebug()<<m_TempValue;
            m_TempValueBackup=(*m_Traces[i])[k];


            m_TempValue=m_nScale*m_TempValue;  //显示波形的幅度
            m_TempValue=1+i+m_TempValue;
            m_TempData<<m_TempValue;
            m_TempDataBackup<<m_TempValue;

        }


        QVector<QVector<double>> m_Segments;
        QVector<QVector<double>> m_y;
        QVector<QColor> m_Colors;

        //        const double threshold = 0.0; // 分割点的阈值

        // 遍历 m_TempDataBackup 中的数据
        int index_w = 0;
        for (int k = 1; k < m_TempDataBackup.size(); k++) {
            // 判断当前数据是否与上一个数据符号相反
            if ((m_TempDataBackup[k]-(i+1)) * (m_TempDataBackup[k-1]-(i+1)) < 0) {
                // 符号相反或者数据过小，认为需要分段
                QVector<double> segment;
                QVector<double> y;

                segment.append(i+1);
                for (int j = index_w; j < k; j++) {
                    segment.append(m_TempDataBackup[j]);
                    y.append(j+1);
                }
                y.append(k+1);
                y.append(k+2);
                segment.append(i+1);

                m_Segments.append(segment);
                m_y.append(y);
                index_w = k;
            }
        }

        // 处理最后一段数据
        if (index_w < m_TempDataBackup.size()) {
            QVector<double> segment;
            QVector<double> y;
            segment.append(i+1);
            for (int j = index_w; j < m_TempDataBackup.size(); j++) {
                segment.append(m_TempDataBackup[j]);
                y.append(j+1);
            }
            segment.append(i+1);
            y.append(k+1);
            y.append(k+2);
            m_Segments.append(segment);
            m_y.append(y);
        }
        index_w++;

        QVector<double> seg_V1;// 正填充的curve使用
        QVector<double> y_V1;
        QVector<double> seg_V2;
        QVector<double> y_V2;
        for (int k = 0; k < m_Segments.size(); k++)
        {
            if (m_Segments[k][1]-(i+1) > 0)
            {
                for(int i =0 ;i<m_Segments[k].size();i++ )
                {
                    seg_V1.append(m_Segments[k][i]);
                    y_V1.append(m_y[k][i]);
                }

            }
            else
            {
                for(int i =0 ;i<m_Segments[k].size();i++ )
                {
                    seg_V2.append(m_Segments[k][i]);
                    y_V2.append(m_y[k][i]);
                }
            }
        }


        switch (draw_mode){

        case 1:{// 正填充
            curve_tp = new QwtPlotCurve;
            curve_tp->setSamples(seg_V1, y_V1);

            QColor color = QColor(Qt::black);
            QBrush brush(color);
            curve_tp->setBrush(brush);

            // 不要线条
           //curve_tp->setPen(QPen(Qt::white));
           //curve_tp->setPen(QPen(Qt::white, 0));

           curve_tp->attach(ui->qwtPlot);

           // 不填充那部分的线条
           curve_tp2 = new QwtPlotCurve;
           curve_tp2->setSamples(seg_V2, y_V2);

           curve_tp2->attach(ui->qwtPlot);

            break;
        }

        case 2:{// 负填充
            curve_tp = new QwtPlotCurve;
            curve_tp->setSamples(seg_V2, y_V2);

            QColor color = QColor(Qt::black);
            QBrush brush(color);
            curve_tp->setBrush(brush);

            // 不要线条
            //curve_tp->setPen(QPen(Qt::white));
            //curve_tp->setPen(QPen(Qt::white, 0));

            curve_tp->attach(ui->qwtPlot);

            // 不填充那部分的线条
            curve_tp2 = new QwtPlotCurve;
            curve_tp2->setSamples(seg_V1, y_V1);

            curve_tp2->attach(ui->qwtPlot);

            break;
        }
        case 3:{// 不填充
            // qDebug() << "[Message]<waveP>m_Traces[i]->count()" << m_Traces[i]->count();
            // wave_amplitudes.reserve(m_Traces[i]->count());
            for(k=0;k<m_Traces[i]->count();k++)
            {
                m_TempValue=(*m_Traces[i])[k];
                // qDebug() << "[M]" << i << "--"<< k << ",m_TempValue:" << m_TempValue;
                m_TempValue=m_nScale*m_TempValue;  //显示波形的幅度
                m_TempValue=1+i+m_TempValue; // 偏移
                m_TempDataBackup<<m_TempValue;
                // wave_amplitudes.emplace_back(m_TempValue);
            }

            QwtPlotCurve *curve = new QwtPlotCurve();
            curve->setSamples(m_TempDataBackup,vectorX3c);// x轴  y轴数据，坐标
            curve->attach(ui->qwtPlot);
            break;
        }
        default:
            qDebug() << "[WARNING] draw_mode 不为1，2，3";
            break;
        }
        //qDebug() << m_TempDataBackup;
//        qDebug() << "[Message]m_TempDataBackup[0]:" << m_TempDataBackup.at(0)
//                 << ",wave_amplitudes[0]:" << wave_amplitudes[0];

        // 数据清理
        // vectorX3c 数据是不用动的，是固定的，不需要clear
        m_TempDataBackup.clear();
        //wave_amplitudes.clear();
    }
    //qDebug() << "[Message]<waveP()><for( i = trace_first ;i< trace_first + x_size; i++)>Elapsed time:" << elapsed_str << " seconds";

    // 用于缩放
    fun_for_zommer();

    // 设置 x 轴和 y 轴范围
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(trace_first) + double(x_size));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
//    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, 100);
//    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, -1,1);
    // 重新绘制图形
    ui->qwtPlot->replot();

    //QChart绘制测试
    /*
    chart->setTitle(" example");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(-3, 700);
    chart->axes(Qt::Vertical).first()->setRange(-3,100);
//    chart->axes(Qt::Horizontal).first()->setRange(double(trace_first), double(trace_first) + double(x_size));
//    chart->axes(Qt::Vertical).first()->setRange(0.0, m_nTraceLen);

    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(800,600);
    chartView->show();*/

    // 清理数据
    // clearData(); 数据还能用到

    // 计时
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed = duration.count() * 1e-6; // microseconds to seconds
    QString elapsed_str = QString::number(elapsed, 'f', 5); // 精确到5位小数
    qDebug() << "[Message]<waveP()><绘图>Elapsed time:" << elapsed_str << " seconds";
    qDebug()<<"[Message]<waveP()>程序耗时："<<timedebuge.elapsed()/1000.0<<"s";//输出计时
}



// 选择文件 sgy文件
void MainWindow::on_pushButton_chooseFile_clicked()
{
    clearData();// 清除加载的数据
    file_sgy_path = QFileDialog::getOpenFileName(this, tr("选择sgy文件"), "", tr("SGY Files (*.sgy)"));

    if (!file_sgy_path.isEmpty()) {
        // 执行文件路径非空的逻辑
        file_sgy_path.replace("/","//"); // 需要的路径
        qDebug() << "选择的sgy文件路径：" << file_sgy_path;
        load_wave_data();// 加载sgy数据
        is_data_loaded = true;
        qDebug() << "[Message]准备绘制";

        //waveP_first();
        waveP();// 进行绘制，默认黑白模式 --tmp
        qDebug() << "[Message]绘制完毕";
        // 读取该图像的长宽尺寸
        qwtPlot_scale[0] = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
        qwtPlot_scale[1] = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).upperBound();
        qwtPlot_scale[2] = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).lowerBound();
        qwtPlot_scale[3] = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).upperBound();
        // 进一步处理选中的文件路径...
    } else {
        // 执行文件路径为空的逻辑
        qDebug() << "未选择sgy文件";
        is_data_loaded = false;
    }
}

// 正填充 --弃用
void MainWindow::on_pushButton_13_clicked()
{
    if(is_data_loaded){
        if(draw_mode == 1){
                // 恢复初始化，大小 --tmp
        } else {
                draw_mode = 1;
                waveP();
        }
    }

}

// 负填充 --弃用
void MainWindow::on_pushButton_14_clicked()
{
    if(is_data_loaded){
        if(draw_mode == 2){
                // 恢复初始化，大小 --tmp
        } else {
                draw_mode = 2;
                waveP();
        }
    }

}

// 不填充 --弃用
void MainWindow::on_pushButton_15_clicked()
{
    if(is_data_loaded){
        if(draw_mode == 3){
                // 恢复初始化，大小 --tmp
        } else {
                draw_mode = 3;
                waveP();
        }
    }

}

// 放大
void MainWindow::on_pushButton_add_clicked()
{
    if(is_data_loaded){
        zoomIn();
    }

}

// 缩小
void MainWindow::on_pushButton_minus_clicked()
{
    if(is_data_loaded){
        zoomOut();
    }

}

// 标准
void MainWindow::on_pushButton_originalSize_clicked()
{
    if(is_data_loaded){
        // Set the new axis ranges
        ui->qwtPlot->setAxisScale(QwtPlot::xBottom, qwtPlot_scale[0], qwtPlot_scale[1]);
        ui->qwtPlot->setAxisScale(QwtPlot::yLeft, qwtPlot_scale[2], qwtPlot_scale[3]);

        // Replot the graph
        ui->qwtPlot->replot();
    }

}

// 快照
void MainWindow::on_pushButton_image_clicked()
{
    QString filename = "sgy_" + QString::number(qwtPlot_scale[0]) + "_" + QString::number(x_size) + ".png";

//    QwtPlotRenderer renderer;
//    renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, false);
//    renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
//    renderer.renderDocument(ui->qwtPlot, filename, QSizeF(300, 200), 85);


//    // 获取程序所在目录
//    QString appPath = QCoreApplication::applicationDirPath();

//    // 拼接默认文件名
//    QString defaultName = appPath + filename;

    // 弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", filename, "Images (*.png)");

    if (!fileName.isEmpty()) {

        // 设置渲染参数
        QwtPlotRenderer renderer;
        renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, false);
        renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);

        // 获取保存大小
        QSizeF size(300, 200);

        // 渲染 保存plot
        renderer.renderDocument(ui->qwtPlot, fileName, size, 85);
    }

}

// 获取当前窗口尺寸
void MainWindow::window_scale_update(){
    qwtPlot_scale[0] = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).lowerBound();
    qwtPlot_scale[1] = ui->qwtPlot->axisScaleDiv(QwtPlot::xBottom).upperBound();
    qwtPlot_scale[2] = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).lowerBound();
    qwtPlot_scale[3] = ui->qwtPlot->axisScaleDiv(QwtPlot::yLeft).upperBound();

}

// 用于图像放缩
void MainWindow::fun_for_zommer(){
    QwtPlot* qwtPlot = ui->qwtPlot;
    m_canvas = qobject_cast<QwtPlotCanvas*>(qwtPlot->canvas());
    if (m_canvas) {
        // 转换成功，进行后续操作
    } else {
        // 转换失败，处理错误
        qDebug() << "无法将QWidget转换为QwtPlotCanvas";
    }

    if(m_zoomer){
        //qDebug() << "存在";
        delete m_zoomer;
        m_zoomer = nullptr;
    } else {
        //qDebug() << "不存在";
    }

//    m_zoomer = new Zoomer(m_canvas, ui->qwtPlot->canvas()->rect(), true);
    m_zoomer = new Zoomer(m_canvas);
    // m_zoomer.initialRect = ui->qwtPlot->axisScaleRect(QwtPlot::xBottom, QwtPlot::yLeft) ;
    m_zoomer->xMin = qwtPlot_scale[0] ;
    m_zoomer->xMax = qwtPlot_scale[1] ;
    m_zoomer->yMin = qwtPlot_scale[2];
    m_zoomer->yMax = qwtPlot_scale[3];
    m_zoomer->z_qwtPlot = ui->qwtPlot;

    /*
    // 更改坐标，用于zoomer返回上一步 --test
//    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(trace_first) + double(x_size));
//    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen); //
//    zoomer = new QwtPlotZoomer(ui->qwtPlot->canvas());
//    zoomer->setZoomBase();
//    zoomer->setRubberBandPen(QColor(Qt::black));
//    zoomer->setTrackerPen(QColor(Qt::black));

    double xMin = trace_first;
    double xMax = trace_first + x_size;
    double yMin = 0.0;
    double yMax = m_nTraceLen;

    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, xMin, xMax);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, yMin, yMax);

    zoomer = new QwtPlotZoomer(ui->qwtPlot->canvas());

//    QwtScaleMap xScaleMap = ui->qwtPlot->canvasMap(QwtPlot::xBottom);
//    QwtScaleMap yScaleMap = ui->qwtPlot->canvasMap(QwtPlot::yLeft);
//    QRectF zoomBaseRect(xMin, yMin, xMax - xMin, yMax - yMin);
//    zoomer->setZoomBase(zoomBaseRect);

    // QRectF zoomBaseRect(xMin, yMin, xMax - xMin, yMax - yMin);
    // qDebug() << "zoomBaseRect: " << zoomBaseRect;
//    zoomer->setZoomBase(zoomBaseRect);

    // zoomer->setZoomBase(ui->qwtPlot->canvas()->rect()); // 将初始大小设置为 canvas 的大小
    // qDebug() << "Canvas Rect: " << ui->qwtPlot->canvas()->rect();// 发现rect是画布大小  Canvas Rect:  QRect(0,0 370x363)
    qDebug() << "xMin:" << xMin << "  xMax:" << xMax;

    zoomer->setRubberBandPen(QColor(Qt::black));
    zoomer->setTrackerPen(QColor(Qt::black));
*/
}

// 第一个
void MainWindow::on_pushButton_first_clicked()
{
    if(is_data_loaded && radio_button_checked() ==  1){
        if(trace_first == 0){
                // 标准化
                on_pushButton_originalSize_clicked();
                // 弹框，已经是第一个
        } else {
                trace_first = 0;

                //fun_for_zommer();

                waveP();
        }
        window_scale_update();
    } else if (is_data_loaded && radio_button_checked() ==  2){// sources
        on_pushButton_first_clicked(1);
    } else if(is_data_loaded && radio_button_checked() ==  3){// cmp line
        on_pushButton_first_clicked(2);
    }
    icon_gray(1);// 第一个
}

// 前一个
void MainWindow::on_pushButton_back_clicked()
{
    if(is_data_loaded && radio_button_checked() ==  1){
        trace_first -= x_size;
        if(trace_first < 0){// 没有前一个道集，但不是第一个道集，从零开始
                trace_first = 0;
                //fun_for_zommer();
                waveP();
                icon_gray(1);
        } else if (trace_first == 0){ // 是第一个，无动作

        } else { // 有前一个
                // fun_for_zommer();
                waveP();
                // init_icon();
        }
        window_scale_update();
    }else if (is_data_loaded && radio_button_checked() ==  2){// sources
        on_pushButton_back_clicked(1);
        window_scale_update();
    } else if(is_data_loaded && radio_button_checked() ==  3){// cmp line
        on_pushButton_back_clicked(2);
        window_scale_update();
    }

}

// 下一个
void MainWindow::on_pushButton_next_clicked()
{
    if(is_data_loaded && radio_button_checked() ==  1){
        qDebug() << "on_pushButton_next_clicked; radio_button_checked() ==  1 ";
        trace_first += x_size;
        if(trace_first >= m_nTotalTraceNum - 1 ){// 没有下一个，取最后一个道集
                trace_first = m_nTotalTraceNum - 1 - x_size;
                // window_scale_update();
                //fun_for_zommer();
                waveP();
                icon_gray(2);
        } else { // 有下一个
                window_scale_update();// --测试
                //fun_for_zommer();
                waveP();
                // init_icon();
        }
        window_scale_update();
    }else if (is_data_loaded && radio_button_checked() ==  2){// sources
        qDebug() << "on_pushButton_next_clicked; radio_button_checked() ==  2 ";
        on_pushButton_next_clicked(1);
        window_scale_update();
        for(int i=0;i<4;i++){
            qDebug() <<"qwtPlot_scale:" <<qwtPlot_scale[i];
        }
        qDebug() <<"   m_zoomer->xMax" <<m_zoomer->xMax<<"   m_zoomer->xMin" <<m_zoomer->xMin;
    } else if(is_data_loaded && radio_button_checked() ==  3){// cmp line
        qDebug() << "on_pushButton_next_clicked; radio_button_checked() ==  3 ";
        on_pushButton_next_clicked(2);
        window_scale_update();
    }

}

/*处理按钮灰色 判断是不是第一个或者最后一个--1.已经是第一个 2.已经是最后一个*/
void MainWindow::icon_gray(int i){

    // 一堆bug
//    QIcon icon;
//    switch (i){
//    case 1:
//        icon = QIcon(icon_file_path + "first2_gray.png");
//        prettify_button(ui->pushButton_first,icon);
//        icon = QIcon(icon_file_path + "back2_gray.png");
//        prettify_button(ui->pushButton_back,icon);
//        break;
//    case 2:
//        icon = QIcon(icon_file_path + "forward2_gray.png");
//        prettify_button(ui->pushButton_next,icon);
//        icon = QIcon(icon_file_path + "last2_gray.png");
//        prettify_button(ui->pushButton_last,icon);
//        break;
//    case 3:
//        init_icon();
//        break;
//    }
}

// 最后一个
void MainWindow::on_pushButton_last_clicked()
{
    if(is_data_loaded && radio_button_checked() ==  1){
        trace_first = m_nTotalTraceNum - 1 - x_size;
        qDebug() << "[Message]<最后一个>trace_first："<< trace_first;
        //fun_for_zommer();
        waveP();
        window_scale_update();

        icon_gray(2); // 2：最后一个
        // 直接写进函数
        // QIcon icon = QIcon(icon_file_path + "last2.png");
        // prettify_button(ui->pushButton_last,icon);
    }else if (is_data_loaded && radio_button_checked() ==  2){// sources
        on_pushButton_last_clicked(1);
    } else if(is_data_loaded && radio_button_checked() ==  3){// cmp line
        on_pushButton_last_clicked(2);
    }

}

// 下拉框 选择x_size的大小
void MainWindow::on_comboBox_activated(int index)
{
    if( radio_button_checked() ==  1){ // 默认模式
        QString tmp = ui->comboBox->currentText();
        x_size = tmp.toInt();
        if(file_sgy_path.isEmpty()){
                // 请先选择sgy文件
        } else {
                // 如果trace_first + x_size 已经越界，取最后一个
                if( trace_first > m_nTotalTraceNum - 1 - x_size){
                    trace_first = m_nTotalTraceNum - 1 - x_size;
                }
                waveP();
                window_scale_update();
        }
    }

}

// 查找
void MainWindow::on_pushButton_search_clicked()
{
    if(radio_button_checked() ==  1){// 默认模式
        QString no = ui->textEdit_2->toPlainText();
        bool ok; // 用于判断转换是否成功的标志变量
        int num_trace = QVariant(no).toInt(&ok);

        if(is_data_loaded){
                if (ok) {
                    // 转换成功，执行相应操作

                    if(num_trace > m_nTotalTraceNum - 1 - x_size){// 最后一个
                        trace_first = m_nTotalTraceNum - 1 - x_size;
                        icon_gray(2);
                    } else if(num_trace == 0 ) {
                        icon_gray(1);
                    } else {
                        trace_first = num_trace;
                        // init_icon();
                    }
                    //fun_for_zommer();
                    waveP();
                    window_scale_update();
                } else {
                    // 转换失败，输出错误信息或执行其他操作
                    qDebug() << "Invalid input or not a number.";
                    QMessageBox::warning(this, "错误", "输入无效或不是数字！");
                }

        }
    }

}

// 正填充
void MainWindow::on_pushButton_fill_zh_clicked()
{
    if(is_data_loaded){
        if(draw_mode == 1){
            // 恢复初始化，大小 --tmp
        } else {
            draw_mode = 1;
            waveP();
        }
    }
}

// 负填充
void MainWindow::on_pushButton_fill_fu_clicked()
{
    if(is_data_loaded){
        if(draw_mode == 2){
            // 恢复初始化，大小 --tmp
        } else {
            draw_mode = 2;
            waveP();
        }
    }
}

// 不填充
void MainWindow::on_pushButton_fill_no_clicked()
{
    if(is_data_loaded){
        if(draw_mode == 3){
            // 恢复初始化，大小 --tmp
        } else {
            draw_mode = 3;
            waveP();
        }
    }
}






// 新 炮号和线号绘制
void MainWindow::waveP(int flag){
    QVector<int> tmpInline;
    // QVector<int> sourcesInline;
    if(flag == 1){// sourcesInline
                tmpInline = sourcesInline;
    } else if (flag == 2){// countInline
                tmpInline = countInline;
    } else {
                qDebug() << "[ERROR] flag!=1 flag!=2 ,waveP_12";
                return;
    }

//    qDebug() << "[Message]waveP(int flag)  tmpInline:" << tmpInline;

//    dasd
//    dsa

//    sa
//    das

#pragma region "test" {
    //    ds d
    //        sad asd
    //        a
    //        sada

#pragma endregion }

    //不是最后一道绘制时
    if(trace_first!=tmpInline.at(tmpInline.size() - 2)){
                // 更改坐标，用于zoomer返回上一步 --test
                ui->qwtPlot->setAxisScale(QwtPlot::xBottom, trace_first, tmpInline[numInline]);
                ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
                // qDebug() << "trace_first:" << trace_first;
                // qDebug() << "countInline[numInline]" << tmpInline[numInline];
    }
    //最后一道绘制时
    else{
                // 更改坐标，用于zoomer返回上一步 --test
                ui->qwtPlot->setAxisScale(QwtPlot::xBottom, trace_first, m_nTotalTraceNum);
                ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
    }

    // 更改坐标，用于zoomer返回上一步 --test
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(trace_first) + double(x_size));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
    qDebug() << "trace_first:" << trace_first;


    // 初始化参数
    m_nCurrentEndianType = 0;
    m_nCurrentTraceNum = 1;

    m_nTraceHeaderByteValue = 4;
    m_nComponent=14;
    m_nScale=1.0;
    m_nDisMode =0;

    // 计时
    QTime timedebuge;//声明一个时钟对象
    timedebuge.start();//开始计时
    auto start = std::chrono::high_resolution_clock::now();// 另一个计时方法


    //int rectY; //放大缩小矩形框纵坐标大小
    int i,k;
    double j=0.0;
    double m_TempValue;
    double m_TempValueBackup;

    QVector<double> m_TempData;
    QVector<double> vectorX3c;
    QVector<double> m_TempDataBackup;
    // std::vector<double> wave_amplitudes;// 替代m_TempDataBackup

    // 用于测试
    //draw_mode=3;
    // 绘制前清除
    ui->qwtPlot->detachItems();
    vectorX3c.clear();
    //    if(draw_mode == 3 )//不填充模式 --  填充模式的x值不是与y值一一对应的
    //    {
    //        // 纵坐标给值
    //        for (int i=0; i<m_nTraceLen; i++)
    //        {
    //            vectorX3c<<j; // vectorX3c: 0.0 1.0 2.0 ...
    //            j+=1.0;
    //        }
    //    }
    for (int i=0; i<m_nTraceLen; i++)
    {
                vectorX3c<<j; // vectorX3c: 0.0 1.0 2.0 ...
                j+=1.0;
    }

    int num_tp = 0;
    if(trace_first!=tmpInline.at(tmpInline.size() - 2)){
                num_tp = tmpInline[numInline];
    } else {
                num_tp = m_nTotalTraceNum;
    }
     qDebug() << "[Message]waveP(int flag)  num_tp:" << num_tp;

    // x_size个波形；从i= trace_first 到 trace_first + x_size
    double index = 0;
    for( i = trace_first ;i< num_tp; i++)
    {



                for(k=0;k<m_Traces[i]->count();k++)
                {
            m_TempValue=(*m_Traces[i])[k];

            //            qDebug()<<m_TempValue;
            m_TempValueBackup=(*m_Traces[i])[k];


            m_TempValue=m_nScale*m_TempValue;  //显示波形的幅度
            m_TempValue=1+i+m_TempValue;
            m_TempData<<m_TempValue;
            m_TempDataBackup<<m_TempValue;

                }


                QVector<QVector<double>> m_Segments;
                QVector<QVector<double>> m_y;
                QVector<QColor> m_Colors;

                //        const double threshold = 0.0; // 分割点的阈值

                // 遍历 m_TempDataBackup 中的数据
                int index_w = 0;
                for (int k = 1; k < m_TempDataBackup.size(); k++) {
            // 判断当前数据是否与上一个数据符号相反
            if ((m_TempDataBackup[k]-(i+1)) * (m_TempDataBackup[k-1]-(i+1)) < 0) {
                // 符号相反或者数据过小，认为需要分段
                QVector<double> segment;
                QVector<double> y;

                segment.append(i+1);
                for (int j = index_w; j < k; j++) {
                    segment.append(m_TempDataBackup[j]);
                    y.append(j+1);
                }
                y.append(k+1);
                y.append(k+2);
                segment.append(i+1);

                m_Segments.append(segment);
                m_y.append(y);
                index_w = k;
            }
                }

                // 处理最后一段数据
                if (index_w < m_TempDataBackup.size()) {
            QVector<double> segment;
            QVector<double> y;
            segment.append(i+1);
            for (int j = index_w; j < m_TempDataBackup.size(); j++) {
                segment.append(m_TempDataBackup[j]);
                y.append(j+1);
            }
            segment.append(i+1);
            y.append(k+1);
            y.append(k+2);
            m_Segments.append(segment);
            m_y.append(y);
                }
                index_w++;

                QVector<double> seg_V1;// 正填充的curve使用
                QVector<double> y_V1;
                QVector<double> seg_V2;
                QVector<double> y_V2;
                for (int k = 0; k < m_Segments.size(); k++)
                {
            if (m_Segments[k][1]-(i+1) > 0)
            {
                for(int i =0 ;i<m_Segments[k].size();i++ )
                {
                    seg_V1.append(m_Segments[k][i]);
                    y_V1.append(m_y[k][i]);
                }

            }
            else
            {
                for(int i =0 ;i<m_Segments[k].size();i++ )
                {
                    seg_V2.append(m_Segments[k][i]);
                    y_V2.append(m_y[k][i]);
                }
            }
                }


                switch (draw_mode){

                case 1:{// 正填充
            curve_tp = new QwtPlotCurve;
            curve_tp->setSamples(seg_V1, y_V1);

            QColor color = QColor(Qt::black);
            QBrush brush(color);
            curve_tp->setBrush(brush);

            // 不要线条
            //curve_tp->setPen(QPen(Qt::white));
            //curve_tp->setPen(QPen(Qt::white, 0));

            curve_tp->attach(ui->qwtPlot);

            // 不填充那部分的线条
            curve_tp2 = new QwtPlotCurve;
            curve_tp2->setSamples(seg_V2, y_V2);

            curve_tp2->attach(ui->qwtPlot);

            break;
                }

                case 2:{// 负填充
            curve_tp = new QwtPlotCurve;
            curve_tp->setSamples(seg_V2, y_V2);

            QColor color = QColor(Qt::black);
            QBrush brush(color);
            curve_tp->setBrush(brush);

            // 不要线条
            //curve_tp->setPen(QPen(Qt::white));
            //curve_tp->setPen(QPen(Qt::white, 0));

            curve_tp->attach(ui->qwtPlot);

            // 不填充那部分的线条
            curve_tp2 = new QwtPlotCurve;
            curve_tp2->setSamples(seg_V1, y_V1);

            curve_tp2->attach(ui->qwtPlot);

            break;
                }
                case 3:{// 不填充
            // qDebug() << "[Message]<waveP>m_Traces[i]->count()" << m_Traces[i]->count();
            // wave_amplitudes.reserve(m_Traces[i]->count());
            for(k=0;k<m_Traces[i]->count();k++)
            {
                m_TempValue=(*m_Traces[i])[k];
                // qDebug() << "[M]" << i << "--"<< k << ",m_TempValue:" << m_TempValue;
                m_TempValue=m_nScale*m_TempValue;  //显示波形的幅度
                m_TempValue=1+i+m_TempValue; // 偏移
                m_TempDataBackup<<m_TempValue;
                // wave_amplitudes.emplace_back(m_TempValue);
            }

            QwtPlotCurve *curve = new QwtPlotCurve();
            curve->setSamples(m_TempDataBackup,vectorX3c);// x轴  y轴数据，坐标
            curve->attach(ui->qwtPlot);
            break;
                }
                default:
            qDebug() << "[WARNING] draw_mode 不为1，2，3";
            break;
                }
                //qDebug() << m_TempDataBackup;
                //        qDebug() << "[Message]m_TempDataBackup[0]:" << m_TempDataBackup.at(0)
                //                 << ",wave_amplitudes[0]:" << wave_amplitudes[0];

                // 数据清理
                // vectorX3c 数据是不用动的，是固定的，不需要clear
                m_TempDataBackup.clear();
                //wave_amplitudes.clear();
    }
    //qDebug() << "[Message]<waveP()><for( i = trace_first ;i< trace_first + x_size; i++)>Elapsed time:" << elapsed_str << " seconds";

    // 用于缩放
    fun_for_zommer();

    // 设置 x 轴和 y 轴范围
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, double(trace_first), double(num_tp));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, 0.0, m_nTraceLen);
    //    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, 100);
    //    ui->qwtPlot->setAxisScale(QwtPlot::yLeft, -1,1);
    // 重新绘制图形
    ui->qwtPlot->replot();



    // 清理数据
    // clearData(); 数据还能用到

    // 计时
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed = duration.count() * 1e-6; // microseconds to seconds
    QString elapsed_str = QString::number(elapsed, 'f', 5); // 精确到5位小数
    qDebug() << "[Message]<waveP()><绘图>Elapsed time:" << elapsed_str << " seconds";
    qDebug()<<"[Message]<waveP()>程序耗时："<<timedebuge.elapsed()/1000.0<<"s";//输出计时
}



 //采用炮号，线号显示数据
 // 第一个
 void MainWindow::on_pushButton_first_clicked(int flag)
 {
    if(is_data_loaded){
        if(trace_first == 0){
        // 标准化
        on_pushButton_originalSize_clicked();
        // 弹框，已经是第一个
            } else {
        trace_first = 0;
        numInline = 1;
        //fun_for_zommer();
        if(flag == 1){//
            waveP(1);// sor
        } else if(flag == 2){
            waveP(2);//cmp
        }
        window_scale_update();
    }

 }
 }

 // 前一个
 void MainWindow::on_pushButton_back_clicked(int flag)
 {


    if(is_data_loaded){
        if(flag == 1){// sor
            if(numInline>1){
                numInline--;
                trace_first = sourcesInline[numInline-1];
                qDebug()<< "前一个 else：trace_first " << trace_first;
                waveP(1);//sor
            }
            else {
                QMessageBox::information(nullptr, "提示", "已经是第一个道集");
            }
        } else if(flag == 2){// cmp
            if(numInline>1){
                numInline--;
                trace_first = countInline[numInline-1];
                qDebug()<< "前一个 else：trace_first " << trace_first;
                waveP(2);// cmp
            }
            else {
                QMessageBox::information(nullptr, "提示", "已经是第一个道集");
            }

        }

    }

    window_scale_update();
 }



 // 下一个
 void MainWindow::on_pushButton_next_clicked(int flag)// sor 1  ; cmp 2
 {

    qDebug()<<"on_pushButton_next_clicked :countInline";

    if(is_data_loaded){
        if(flag == 1 ){// sor
            qDebug()<< "numInline:" << numInline << "  sourcesInline.size():" << sourcesInline.size();
            if(numInline >= sourcesInline.size()-1 ){// 没有下一个，取最后一个道集
                    qDebug()<<sourcesInline.size();
                    qDebug()<<numInline;
                    QMessageBox::information(nullptr, "提示", "已经是最后一个道集");

                    numInline = sourcesInline.size()-1;
                    trace_first = sourcesInline[numInline-1];

                    waveP(1);// sor
                    // window_scale_update();
                    //fun_for_zommer();
            }
            else { // 有下一个
                    numInline++;
                    trace_first = sourcesInline[numInline-1];
                    window_scale_update();//  --测试
                    //fun_for_zommer();
                    waveP(1);//sor
            }

        } else if(flag == 2){// cmp
            qDebug()<< "numInline:" << numInline << "  countInline.size():" << countInline.size();
            if(numInline >= countInline.size()-1 ){// 没有下一个，取最后一个道集
                    qDebug()<<countInline.size();
                    qDebug()<<numInline;
                    QMessageBox::information(nullptr, "提示", "已经是最后一个道集");

                    numInline = countInline.size()-1;
                    trace_first = countInline[numInline-1];

                    waveP(2);// cmp
                    // window_scale_update();
                    //fun_for_zommer();
            }
            else { // 有下一个
                    numInline++;
                    trace_first = countInline[numInline-1];
                    window_scale_update();//  --测试
                    //fun_for_zommer();
                    waveP(2);
            }

        }
     window_scale_update();
    }

 }

 // 最后一个
 void MainWindow::on_pushButton_last_clicked(int flag)
 {

    if(is_data_loaded){
        if(flag == 1){//sor
            numInline = sourcesInline.size() - 1;
            trace_first = sourcesInline[numInline-1];

            //fun_for_zommer();
            waveP(1);//sor
        } else if (flag == 2){// cmp
            numInline = countInline.size() - 1;
            trace_first = countInline[numInline-1];

            //fun_for_zommer();
            waveP(2);//cmp
        }

        window_scale_update();
    }

 }



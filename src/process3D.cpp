#include "process3D.h"

//Process3D::Process3D(QObject *parent) : QObject(parent)
//{
//    // 构造函数的实现，如果有需要可以进行初始化操作

//    // 初始化 QOpenGLFunctions
//    initializeOpenGLFunctions();

//    // 进行其他的初始化操作，如创建 OpenGL 上下文、设置渲染参数等
//}


//-----------
//Process3D::Process3D(QObject *parent) : QObject(parent)
//{
//    m_openglWidget = new QOpenGLWidget(); // 创建 QOpenGLWidget 对象
//}

//void Process3D::paintGL()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // 绘制三维数据
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glVertex3f(1.0f, -1.0f, -1.0f);
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glVertex3f(0.0f, 1.0f, -1.0f);
//    glEnd();
//}

//void Process3D::resizeGL(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0, (double)w / h, 0.1, 10.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, -3.0f);
//}

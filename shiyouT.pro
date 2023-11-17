QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17



LIBS += -L "E:\app\QT\5.15.2\mingw81_64\lib" -lqwtd
INCLUDEPATH += "E:\app\QT\5.15.2\mingw81_64\include\Qwt"


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csegyread.cpp \
    icontextbutton.cpp \
    main.cpp \
    mainwindow.cpp \
    src/canvas.cpp \
    src/dataProcess/dataProcess.cpp \
    src/process3D.cpp \
    src/testExample/testQChart.cpp \
    util.cpp \
    zoomer.cpp

HEADERS += \
    Zoomer.h \
    csegyread.h \
    icontextbutton.h \
    mainwindow.h \
    src/canvas.h \
    src/dataProcess/dataProcess.h \
    src/process3D.h \
    src/testExample/testQChart.h \
    util.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

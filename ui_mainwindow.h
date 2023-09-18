/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_chooseFile;
    QTextEdit *textEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QwtPlot *qwtPlot;
    QPushButton *pushButton_image;
    QPushButton *pushButton_back;
    QPushButton *pushButton_next;
    QPushButton *pushButton_last;
    QPushButton *pushButton_search;
    QTextEdit *textEdit_2;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton_first;
    QPushButton *pushButton_fill_fu;
    QPushButton *pushButton_fill_zh;
    QPushButton *pushButton_fill_no;
    QPushButton *pushButton;
    QPushButton *pushButton_color;
    QPushButton *pushButton_originalSize;
    QPushButton *pushButton_add;
    QPushButton *pushButton_overscan;
    QPushButton *pushButton_minus;
    QMenuBar *menubar;
    QMenu *menusgy;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(899, 459);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton_chooseFile = new QPushButton(centralwidget);
        pushButton_chooseFile->setObjectName(QStringLiteral("pushButton_chooseFile"));
        pushButton_chooseFile->setGeometry(QRect(0, 40, 93, 28));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(700, 290, 191, 141));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(30, 290, 651, 531));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 649, 529));
        qwtPlot = new QwtPlot(scrollAreaWidgetContents_2);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));
        qwtPlot->setGeometry(QRect(20, 30, 601, 481));
        scrollArea->setWidget(scrollAreaWidgetContents_2);
        pushButton_image = new QPushButton(centralwidget);
        pushButton_image->setObjectName(QStringLiteral("pushButton_image"));
        pushButton_image->setGeometry(QRect(610, 40, 84, 28));
        pushButton_back = new QPushButton(centralwidget);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setGeometry(QRect(92, 130, 84, 28));
        pushButton_back->setMouseTracking(false);
        pushButton_back->setIconSize(QSize(20, 20));
        pushButton_next = new QPushButton(centralwidget);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setGeometry(QRect(183, 130, 84, 28));
        pushButton_last = new QPushButton(centralwidget);
        pushButton_last->setObjectName(QStringLiteral("pushButton_last"));
        pushButton_last->setGeometry(QRect(274, 130, 85, 28));
        pushButton_search = new QPushButton(centralwidget);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(366, 130, 84, 28));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(450, 160, 75, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(539, 186, 60, 19));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(606, 182, 82, 24));
        pushButton_first = new QPushButton(centralwidget);
        pushButton_first->setObjectName(QStringLiteral("pushButton_first"));
        pushButton_first->setGeometry(QRect(0, 130, 85, 28));
        pushButton_fill_fu = new QPushButton(centralwidget);
        pushButton_fill_fu->setObjectName(QStringLiteral("pushButton_fill_fu"));
        pushButton_fill_fu->setGeometry(QRect(800, 40, 93, 28));
        pushButton_fill_zh = new QPushButton(centralwidget);
        pushButton_fill_zh->setObjectName(QStringLiteral("pushButton_fill_zh"));
        pushButton_fill_zh->setGeometry(QRect(700, 40, 93, 28));
        pushButton_fill_no = new QPushButton(centralwidget);
        pushButton_fill_no->setObjectName(QStringLiteral("pushButton_fill_no"));
        pushButton_fill_no->setGeometry(QRect(700, 150, 93, 28));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(800, 150, 93, 28));
        pushButton_color = new QPushButton(centralwidget);
        pushButton_color->setObjectName(QStringLiteral("pushButton_color"));
        pushButton_color->setGeometry(QRect(501, 41, 93, 28));
        pushButton_originalSize = new QPushButton(centralwidget);
        pushButton_originalSize->setObjectName(QStringLiteral("pushButton_originalSize"));
        pushButton_originalSize->setGeometry(QRect(301, 41, 93, 28));
        pushButton_add = new QPushButton(centralwidget);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        pushButton_add->setGeometry(QRect(101, 41, 93, 28));
        pushButton_overscan = new QPushButton(centralwidget);
        pushButton_overscan->setObjectName(QStringLiteral("pushButton_overscan"));
        pushButton_overscan->setGeometry(QRect(401, 41, 93, 28));
        pushButton_minus = new QPushButton(centralwidget);
        pushButton_minus->setObjectName(QStringLiteral("pushButton_minus"));
        pushButton_minus->setGeometry(QRect(201, 41, 93, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 899, 25));
        menusgy = new QMenu(menubar);
        menusgy->setObjectName(QStringLiteral("menusgy"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menusgy->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton_chooseFile->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_image->setText(QApplication::translate("MainWindow", "\345\277\253\347\205\247", Q_NULLPTR));
        pushButton_back->setText(QApplication::translate("MainWindow", "\345\211\215\344\270\200\344\270\252", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252", Q_NULLPTR));
        pushButton_last->setText(QApplication::translate("MainWindow", "\346\234\200\345\220\216\344\270\200\344\270\252", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\351\201\223\351\233\206\345\244\247\345\260\217", Q_NULLPTR));
        pushButton_first->setText(QApplication::translate("MainWindow", "\347\254\254\344\270\200\344\270\252", Q_NULLPTR));
        pushButton_fill_fu->setText(QApplication::translate("MainWindow", "\350\264\237\345\241\253\345\205\205", Q_NULLPTR));
        pushButton_fill_zh->setText(QApplication::translate("MainWindow", "\346\255\243\345\241\253\345\205\205", Q_NULLPTR));
        pushButton_fill_no->setText(QApplication::translate("MainWindow", "\344\270\215\345\241\253\345\205\205", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\346\257\224\344\276\213", Q_NULLPTR));
        pushButton_color->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262", Q_NULLPTR));
        pushButton_originalSize->setText(QApplication::translate("MainWindow", "\346\240\207\345\207\206", Q_NULLPTR));
        pushButton_add->setText(QApplication::translate("MainWindow", "\346\224\276\345\244\247", Q_NULLPTR));
        pushButton_overscan->setText(QApplication::translate("MainWindow", "\351\223\272\346\273\241", Q_NULLPTR));
        pushButton_minus->setText(QApplication::translate("MainWindow", "\347\274\251\345\260\217", Q_NULLPTR));
        menusgy->setTitle(QApplication::translate("MainWindow", "sgy", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

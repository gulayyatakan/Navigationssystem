/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QWidget *centralwidget;
    QRadioButton *cityButton1;
    QRadioButton *cityButton3;
    QRadioButton *Dresden;
    QRadioButton *cityButton2;
    QRadioButton *cityButton4;
    QRadioButton *cityButton5;
    QPushButton *distanceButton;
    QPushButton *infoButton;
    QPushButton *allLocationsButton;
    QPushButton *myLocationButton;
    QLabel *mapLabel;
    QRadioButton *meinOrt;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1598, 1198);
        MainWindow->setAutoFillBackground(true);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName("actionLoad");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        cityButton1 = new QRadioButton(centralwidget);
        cityButton1->setObjectName("cityButton1");
        cityButton1->setGeometry(QRect(740, 410, 99, 20));
        cityButton3 = new QRadioButton(centralwidget);
        cityButton3->setObjectName("cityButton3");
        cityButton3->setGeometry(QRect(630, 1050, 99, 20));
        Dresden = new QRadioButton(centralwidget);
        Dresden->setObjectName("Dresden");
        Dresden->setGeometry(QRect(670, 730, 99, 20));
        cityButton2 = new QRadioButton(centralwidget);
        cityButton2->setObjectName("cityButton2");
        cityButton2->setGeometry(QRect(300, 320, 91, 20));
        cityButton4 = new QRadioButton(centralwidget);
        cityButton4->setObjectName("cityButton4");
        cityButton4->setGeometry(QRect(130, 930, 99, 20));
        cityButton5 = new QRadioButton(centralwidget);
        cityButton5->setObjectName("cityButton5");
        cityButton5->setGeometry(QRect(360, 1030, 99, 20));
        distanceButton = new QPushButton(centralwidget);
        distanceButton->setObjectName("distanceButton");
        distanceButton->setGeometry(QRect(980, 100, 171, 32));
        infoButton = new QPushButton(centralwidget);
        infoButton->setObjectName("infoButton");
        infoButton->setGeometry(QRect(980, 130, 171, 32));
        allLocationsButton = new QPushButton(centralwidget);
        allLocationsButton->setObjectName("allLocationsButton");
        allLocationsButton->setGeometry(QRect(980, 170, 171, 32));
        myLocationButton = new QPushButton(centralwidget);
        myLocationButton->setObjectName("myLocationButton");
        myLocationButton->setGeometry(QRect(980, 210, 171, 32));
        mapLabel = new QLabel(centralwidget);
        mapLabel->setObjectName("mapLabel");
        mapLabel->setGeometry(QRect(10, 0, 971, 1246));
        mapLabel->setMinimumSize(QSize(971, 0));
        mapLabel->setMaximumSize(QSize(971, 16777215));
        mapLabel->setAutoFillBackground(false);
        mapLabel->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/navigation_scrollbar/866-8664209_leer-deutschland-karte.png")));
        meinOrt = new QRadioButton(centralwidget);
        meinOrt->setObjectName("meinOrt");
        meinOrt->setGeometry(QRect(310, 880, 99, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1598, 24));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad->setText(QCoreApplication::translate("MainWindow", "Laden", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Speichern", nullptr));
        cityButton1->setText(QCoreApplication::translate("MainWindow", "Berlin", nullptr));
        cityButton3->setText(QCoreApplication::translate("MainWindow", "Munchen", nullptr));
        Dresden->setText(QCoreApplication::translate("MainWindow", "Dresden", nullptr));
        cityButton2->setText(QCoreApplication::translate("MainWindow", "Bremen", nullptr));
        cityButton4->setText(QCoreApplication::translate("MainWindow", "Saarbr\303\274cken", nullptr));
        cityButton5->setText(QCoreApplication::translate("MainWindow", "Stuttgart", nullptr));
        distanceButton->setText(QCoreApplication::translate("MainWindow", "Entfernung", nullptr));
        infoButton->setText(QCoreApplication::translate("MainWindow", "Information", nullptr));
        allLocationsButton->setText(QCoreApplication::translate("MainWindow", "Alle Orte", nullptr));
        myLocationButton->setText(QCoreApplication::translate("MainWindow", "Mein Standort", nullptr));
        mapLabel->setText(QString());
        meinOrt->setText(QCoreApplication::translate("MainWindow", "h-da", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

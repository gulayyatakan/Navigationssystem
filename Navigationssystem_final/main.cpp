#include "mainwindow.h"
#include "navigationssystem_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Navigationssystem_test t;
    QTest::qExec(&t);
    w.show();
    return a.exec();
}

#ifndef NAVIGATIONSSYSTEM_TEST_H
#define NAVIGATIONSSYSTEM_TEST_H
#include <QtTest/QTest>
#include "mainwindow.h"
#include "navigationsverwaltung.h"
#include <qcompare.h>
#include "ort.h"
#include "adresse.h"
class Navigationssystem_test:public QObject {
    Q_OBJECT

private slots:
    void test_berechnungvonentfernung();
    void test_two_cities_selection();
};

#endif // NAVIGATIONSSYSTEM_TEST_H

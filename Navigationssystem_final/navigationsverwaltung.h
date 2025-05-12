#ifndef NAVIGATIONSVERWALTUNG_H
#define NAVIGATIONSVERWALTUNG_H
#include<iostream>
#include<vector>
#include<ort.h>
#include <QTextEdit>
#include<meinort.h>
#include <QMessageBox>
using namespace std;

class Navigationsverwaltung
{
public:
    Navigationsverwaltung();
    ~Navigationsverwaltung();
    const double R=6371.0;
    double doubletoradians(double degree);
    double berechnungvonentfernung(Ort *ort1, Ort *ort2);
    void benutzerDialog();
    void Ortanlegenadresse();
    void Ortanlegenpoi();
    void Karteanzeigen(QMessageBox*  outputBox);
    void Karteladen();
    void Kartespeichern();
    int nachbarSuchen(Ort* pos );
    void AktuellePosition(double Längen,double Breiten);
    vector<Ort *> &getOrte();
    string getName(int id);
    Ort* getOrte(int id);

protected:
    vector<Ort*>Orte;

};

#endif // NAVIGATIONSVERWALTUNG_H


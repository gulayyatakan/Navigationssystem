#ifndef MEINORT_H
#define MEINORT_H
#include"ort.h"
#include<iostream>
using namespace std;

class MeinOrt:public Ort
{
public:
    MeinOrt(double Längengrad,double Breitengrad, string Name, string Parameter);

    string getName() const;

    string getParameter() const;

    void verschieben(double neueLatitude, double neueLongitude);
    bool getAktiv() const;
    void setAktiv(bool newAktiv);

    void setParameter(const string &newParameter);

private:
    string Name,Parameter;
    bool aktiv=false;
    int Id=0;
    mutable double aktuellerBreitengrad;
    mutable double aktuellerLaengengrad;

};

#endif // MEINORT_H


#include "meinort.h"

MeinOrt::MeinOrt(double Längengrad,double Breitengrad, string Name, string Parameter)
    : Ort(Längengrad,Breitengrad), Name(Name), Parameter(Parameter), aktuellerBreitengrad(Längengrad), aktuellerLaengengrad(Breitengrad) {}

string MeinOrt::getName() const
{
    return Name;
}

string MeinOrt::getParameter() const
{
    return Parameter;
}


bool MeinOrt::getAktiv() const
{
    return aktiv;
}

void MeinOrt::setAktiv(bool newAktiv)
{
    aktiv = newAktiv;
}

void MeinOrt::setParameter(const string &newParameter)
{
    Parameter = newParameter;
}
void MeinOrt::verschieben(double neueBreitengrad, double neueLaengengrad){
    aktuellerBreitengrad = neueBreitengrad;
    aktuellerLaengengrad = neueLaengengrad;
}

#include "navigationsverwaltung.h"
#include"ort.h"
#include"adresse.h"
#include"poi.h"
#include"meinort.h"
#include<iomanip>
#include<cmath>
#include<vector>
#include <QTextEdit>
#include<fstream>
#include <QMessageBox>
#include<sstream>
#include <QDebug>
Navigationsverwaltung::Navigationsverwaltung()
{


}

Navigationsverwaltung::~Navigationsverwaltung()
{
    for(auto it:Orte){
        delete it;
    }

}

void Navigationsverwaltung::benutzerDialog()
{

    while(true){
        cout<<"Navigationssystem: "<<endl;
        cout<<"1: Ort anlegen"<<endl;
        cout<<"2: Karte anzeigen"<<endl;
        cout<<"3: Entfernung berechnen"<<endl;
        cout<<"4: karte speichern/laden"<<endl;
        cout<<"0: Programm beenden"<<endl;
        cout<<"Geben Sie bitte den Auswahl ein"<<endl;
        char choice;
        cin>>choice;
        switch(choice){
        case('1'):{
            cout<<"Möchten Sie eine Adresse (1) oder einen Point of Interess(2)"<<endl;
            char choice;
            cin>>choice;
            if(choice=='1'){
                Ortanlegenadresse();
                break;

            }
            else if(choice=='2'){
                Ortanlegenpoi();

                break;


            }
            else{
                cout<<"Ungültige Eingabe"<<endl;
            }
            break;




        }
        case('2'):{
            //  Karteanzeigen();
            break;




        }
        case('3'):{

            Ort* ort1 = nullptr;
            Ort* ort2 = nullptr;

            if (Orte.empty()) {
                cout << "Keine ausreichenden Orte" << endl;
                break;
            } else {
                bool found = false;
                cout << "Geben Sie die Ids von den Orten" << endl;
                int Id1, Id2;
                cin >> Id1;
                cin >> Id2;
                for (auto pos : Orte) {
                    if (pos->getId() == Id1) {
                        ort1 = pos;

                    }
                }

                for (auto ort : Orte) {
                    if (ort->getId() == Id2) {
                        ort2 = ort;
                    }

                }

                if (ort1 == nullptr || ort2 == nullptr) {
                    cout << "Falsche Eingabe" << endl;
                    break;
                }
                cout << "Distanz: " << berechnungvonentfernung(ort1, ort2) << endl;
            }

            break;
        }





        case('4'):{
            cout<<"1: Speicehrn 2: Laden"<<endl;
            char choice;
            cin>>choice;
            if(choice=='1'){
                Kartespeichern();
                break;

            }
            else if(choice=='2'){
                Karteladen();
                break;

            }
            break;

        }
        case('0'):{
            cout<<"Sie wollen uns verlassen"<<endl;
            return;

        }
        }
    }


}

void Navigationsverwaltung::Ortanlegenadresse()
{
    double Längen,Breite;
    string Name,Parameter;
    cout<<"Geben Sie bitte die Länge ein"<<endl;
    cin>>Längen;
    cout<<"Geben Sie bitte die Breite ein"<<endl;
    cin>>Breite;
    cout<<"Geben Sie bitte die Name"<<endl;
    cin.ignore();

    getline(cin,Name);
    cout<<"Geben Sie bitte die Parameter"<<endl;
    cin.ignore();
    getline(cin,Parameter);
    Ort*adresse=new Adresse(Längen,Breite,Name,Parameter);
    Orte.push_back(adresse);
    cout<<"Adresse wird angelegt mit dem Nummer: "<<adresse->getId()<<endl;

}

void Navigationsverwaltung::Ortanlegenpoi()
{
    double Länge,Breite;
    cout<<"Geben Sie bitte die Länge ein"<<endl;
    cin>>Länge;
    cout<<"Geben Sie bitte die Breite ein"<<endl;
    cin>>Breite;
    string Name,Parameter;
    cout<<"Geben Sie bitte die Name ein"<<endl;
    cin.ignore();
    getline(cin,Name);
    cout<<"Geben Sie bitte die Parameter ein"<<endl;
    cin.ignore();
    getline(cin,Parameter);

    Ort*poi=new Poi(Länge,Breite,Name,Parameter);
    Orte.push_back(poi);
    cout<<"Point of Interess wird angelegt: "<<poi->getId()<<endl;

}








void Navigationsverwaltung::Karteanzeigen(QMessageBox* outputBox) {
    // Validate the output box
    if (!outputBox) {
        qDebug() << "Error: outputBox is null!";
        return;
    }

    // Compose the output content
    QString content;

    qDebug() << "Validating Orte...";
    qDebug() << "Orte size:" << Orte.size();

    if (Orte.empty()) {
        qDebug() << "Orte is empty. No additional items to display.";
        content = "No additional Orte available.\n";
    } else {
        for (Ort* ort : Orte) {
            if (!ort) {
                qDebug() << "Warning: Null pointer in Orte!";
                continue;
            }
            if (auto mein = dynamic_cast<MeinOrt*>(ort)) {
                content += QString("%1%2%3\n")
                .arg(QString::number(mein->getId()), 10)
                    .arg(QString::fromStdString(mein->getName()), 20)
                    .arg("Mein Ort", 20);
            } else if (auto adr = dynamic_cast<Adresse*>(ort)) {
                content += QString("%1%2%3\n")
                .arg(QString::number(adr->getId()), 10)
                    .arg(QString::fromStdString(adr->getName()), 20)
                    .arg("Adresse", 20);
            } else if (auto poi = dynamic_cast<Poi*>(ort)) {
                content += QString("%1%2%3\n")
                .arg(QString::number(poi->getId()), 10)
                    .arg(QString::fromStdString(poi->getName()), 20)
                    .arg("POI", 20);
            } else {
                qDebug() << "Unknown type in Orte!";
            }
        }
    }

    qDebug() << "Karteanzeigen completed successfully.";

    // Set the content to the message box
    outputBox->setText(content);
}


void Navigationsverwaltung::Karteladen()
{
    ifstream datei("Kartenavi.txt");
    if (!datei) {
        cerr << "Fehler beim Öffnen der Datei" << endl;
        return;
    }

    Orte.clear();
    string line;

    while (getline(datei, line)) {
        if (line == "Adresse:") {
            double längengrad, breitengrad;
            string Name, Parameter;

            datei.ignore(256, ':'); datei >> längengrad;
            datei.ignore(256, ':'); datei >> breitengrad;
            datei.ignore(256, ':'); getline(datei, Name);
            datei.ignore(256, ':'); getline(datei, Parameter);
            Ort* adresse = new Adresse(längengrad, breitengrad, Name,Parameter);
            Orte.push_back(adresse);
        } else if (line == "Poi:") {
            double längengrad, breitengrad;
            string Name, Parameter;
            datei.ignore(256, ':'); datei >> längengrad;
            datei.ignore(256, ':'); datei >> breitengrad;
            datei.ignore(256, ':'); getline(datei, Name);
            datei.ignore(256, ':'); getline(datei, Parameter);
            Ort* poi = new Poi(längengrad, breitengrad,Name ,Parameter );
            Orte.push_back(poi);
        }
    }

    datei.close();
    //cout << "Karte wird geladen" << endl;
}

void Navigationsverwaltung::Kartespeichern()
{
    cout<<"Karte speichern "<<endl;
    ofstream datei("Kartenavi.txt");
    if(!datei){
        cerr<<"Fehler bei der Öffnung"<<endl;
    }


    for(Ort*ort:Orte){
        if(auto adresse=dynamic_cast<Adresse*>(ort)){
            datei<<"Adresse:"<<endl;
            datei<<"Längengrad:"<<adresse->getLängengrad()<<endl;
            datei<<"Breitengrad:"<<adresse->getBreitengrad()<<endl;
            datei<<"Name:"<<adresse->getName()<<endl;
            datei<<"Parameter:"<<adresse->getParameter()<<endl;
        }
        else if(auto poi=dynamic_cast<Poi*>(ort)){
            datei<<"Poi: "<<endl;
            datei<<"Längengrad: "<<poi->getLängengrad()<<endl;
            datei<<"Breitengrad: "<<poi->getBreitengrad()<<endl;
            datei<<"Name: "<<poi->getName()<<endl;
            datei<<"Parameter: "<<poi->getParameter()<<endl;
        }




    }
    datei.close();
    //cout<<"Karte wurde gespeichert"<<endl;**/

}

void Navigationsverwaltung::AktuellePosition(double Längen,double Breiten)
{



    string Name,Parameters;


    if (dynamic_cast<MeinOrt*>(Orte[0]) != nullptr) {
        MeinOrt* meinOrt = dynamic_cast<MeinOrt*>(Orte[0]);
        meinOrt->verschieben(Längen,Breiten);

    } else {
        std::cerr << "Error: The first element is not a MeinOrt instance." << std::endl;
    } }








vector<Ort *> &Navigationsverwaltung::getOrte()
{
    return Orte;
}
int Navigationsverwaltung::nachbarSuchen(Ort* pos) {
    int minIndex = -1;  // Initialize minIndex to -1 to handle the case if no neighbors are found
    std::vector<double> entfernungen;  // Vector to store distances

    // Calculate distances for each Ort
    for (Ort* ort : Orte) {
        if (ort != pos) {  // Avoid calculating the distance to itself
            double entfernung = berechnungvonentfernung(pos, ort);
            entfernungen.push_back(entfernung); // Store the distance in the vector
            qDebug() << "Distance to Ort "  << ": "<< QString::fromStdString(ort->getName());
        }
    }

    // Check if the entfernungen vector is empty to prevent errors
    if (entfernungen.empty()) {
        qDebug() << "No neighbors found!";
        return -1;  // Return a default value or handle the error as needed
    }

    // Debug: Print all distances to check correctness
    for (size_t i = 0; i < entfernungen.size(); ++i) {
        qDebug() << "Distance to Ort " << i << ": " << entfernungen[i];
    }

    // Initialize the minimum distance to the first distance in the vector
    double minEntfernung = entfernungen[0];
    minIndex = 0;  // The index of the first element

    // Search for the smallest distance
    for (size_t i = 1; i < entfernungen.size(); ++i) {
        if (entfernungen[i] < minEntfernung) {
            minEntfernung = entfernungen[i];  // Update the minimum distance
            minIndex = i;  // Update the index of the nearest location
            qDebug() << "New minimum distance: " << minEntfernung << " at index " << minIndex;
        }
    }

    // Return the index of the nearest neighbor
    return minIndex;
}
Ort*  Navigationsverwaltung::getOrte(int id){
    if (id >= 0 && id < Orte.size()) {
        return Orte[id];  // Return the Poi object
    }
    return nullptr;

}
string Navigationsverwaltung::getName(int id){
    string name;
    name=Orte[id]->getName();
    return name;
}
double Navigationsverwaltung::berechnungvonentfernung(Ort* pos ,Ort*ort2)
{


    double lag1=doubletoradians(pos->getLängengrad());
    double bre1=doubletoradians(pos->getBreitengrad());
    double lag2=doubletoradians(ort2->getLängengrad());
    double bre2=doubletoradians(ort2->getBreitengrad());
    double difbe=lag2-lag1;
    double difla=bre2-bre1;
    double a =sin(difla / 2) * sin(difla / 2) +cos(lag1) *cos(lag2) *sin(difbe / 2) * sin(difbe/ 2);

    double c=2*atan2(sqrt(a),sqrt(1-a));
    double distanz= R*c  ;
    return distanz;



}

double Navigationsverwaltung::doubletoradians(double degree)
{
    return degree*(M_PI/180.0);
}

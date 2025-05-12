#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QRadioButton>
#include <QGroupBox>
#include "poi.h"
#include <QTimer>
#include <QDialog>
#include <QPainter>
#include <fstream>
#include "meinort.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QStringList>
#include "adresse.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), navVerwaltung(new Navigationsverwaltung)
{ ui->setupUi(this);

    setupMap();
    outputBox = new QTextEdit(this);
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(outputBox);
    ui->centralwidget->setLayout(horizontalLayout);

    connect(ui->cityButton1, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);
    connect(ui->cityButton2, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);
    connect(ui->cityButton3, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);
    connect(ui->cityButton4, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);
    connect(ui->cityButton5, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);
    connect(ui->meinOrt, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveData);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadData);
}

void MainWindow::saveData() {
    QString dateiName = "/Users/aminecht/Documents/Studium/Prog 2/Prak5/Auf16/Karte.txt";
    if (dateiName.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Keine Datei ausgewählt.");
        return;
    }

    std::ofstream datei(dateiName.toStdString());
    if (!datei) {
        QMessageBox::warning(this, "Fehler", "Konnte Datei nicht öffnen.");
        return;
    }

    for (Ort* ort : navVerwaltung->getOrte()) {
        if (auto mein = dynamic_cast<MeinOrt*>(ort)) {
            datei << "Adresse:\n";
            datei << "Name: " << mein->getName() << "\n";
            datei << "Längengrad: " << mein->getLängengrad() << "\n";
            datei << "Breitengrad: " << mein->getBreitengrad() << "\n";
            datei << "Parameter: " << mein->getParameter() << "\n";
        }
        else if (auto adresse = dynamic_cast<Adresse*>(ort)) {
            datei << "Adresse:\n";
            datei << "Name: " << adresse->getName() << "\n";
            datei << "Längengrad: " << adresse->getLängengrad() << "\n";
            datei << "Breitengrad: " << adresse->getBreitengrad() << "\n";
            datei << "Parameter: " << adresse->getParameter() << "\n";
        }

        else if (auto poi = dynamic_cast<Poi*>(ort)) {
            datei << "Poi:\n";
            datei << "Name: " << poi->getName() << "\n";
            datei << "Längengrad: " << poi->getLängengrad() << "\n";
            datei << "Breitengrad: " << poi->getBreitengrad() << "\n";
            datei << "Parameter: " << poi->getParameter() << "\n";

        }
    }

    datei.close();

    QMessageBox::information(this, "Erfolg", "Karte wurde erfolgreich gespeichert.");
}


void MainWindow::loadData() {
    //QString dateiName = QFileDialog::getOpenFileName(this, "Laden", "", "Textdateien (*.txt);;Alle Dateien (*)");

    QString dateiName = "/Users/aminecht/Documents/Studium/Prog 2/Prak5/Auf16/Karte.txt";
    /* if (dateiName.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Keine Datei ausgewählt.");
        return;
    }*/

    std::ifstream datei(dateiName.toStdString());
    if (!datei) {
        QMessageBox::warning(this, "Fehler", "Konnte Datei nicht öffnen.");
        return;
    }

    std::string line;
    while (std::getline(datei, line)) {
        if (line == "Adresse:") {
            std::string name, parameter;
            double laengengrad, breitengrad;

            std::getline(datei, line);
            name = line.substr(6);
            std::getline(datei, line);
            laengengrad = std::stod(line.substr(12));
            std::getline(datei, line);
            breitengrad = std::stod(line.substr(13)); // Entfernen von "Breitengrad: "
            std::getline(datei, line); // Parameter
            parameter = line.substr(11); // Entfernen von "Parameter: "
            Ort* adresse = new Adresse(laengengrad, breitengrad, name, parameter);
            navVerwaltung->getOrte().push_back(adresse);

            QPoint pixel_coordinates = gpsToPixel(laengengrad, breitengrad,mapLabel);

            QRadioButton* newButton = new QRadioButton(QString::fromStdString(name), mapLabel);

            newButton->setGeometry(pixel_coordinates.x(), pixel_coordinates.y(), 90, 35);
            newButton->setProperty("associatedOrt", QVariant::fromValue(static_cast<void*>(adresse)));
            newButton->show();
            connect(newButton, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);


        }
        // Wenn die Zeile mit "Poi" beginnt, dann laden wir ein Point of Interest
        else if (line == "Poi:") {
            std::string name, parameter;
            double laengengrad, breitengrad;

            // Name, Längengrad, Breitengrad und Parameter einlesen
            std::getline(datei, line); // Name
            name = line.substr(6); // Entfernen von "Name: "
            std::getline(datei, line); // Längengrad
            laengengrad = std::stod(line.substr(12)); // Entfernen von "Längengrad: "
            std::getline(datei, line); // Breitengrad
            breitengrad = std::stod(line.substr(13)); // Entfernen von "Breitengrad: "
            std::getline(datei, line); // Parameter
            parameter = line.substr(11); // Entfernen von "Parameter: "
            Ort* poi = new Poi(laengengrad, breitengrad, name, parameter);

            navVerwaltung->getOrte().push_back(poi);
            QPoint pixel_coordinates = gpsToPixel(laengengrad, breitengrad,mapLabel);

            QRadioButton* newButton = new QRadioButton(QString::fromStdString(name), mapLabel);
            newButton->setGeometry(pixel_coordinates.x(), pixel_coordinates.y(), 100, 35);
            newButton->setProperty("associatedOrt", QVariant::fromValue(static_cast<void*>(poi)));
            newButton->show();
            connect(newButton, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);




        }
        if (line == "Myort:") {
            std::string name, parameter;
            double laengengrad, breitengrad;


            std::getline(datei, line);
            name = line.substr(6);
            std::getline(datei, line);
            laengengrad = std::stod(line.substr(12));
            std::getline(datei, line);
            breitengrad = std::stod(line.substr(13));
            std::getline(datei, line);
            parameter = line.substr(11);
            Ort* pos = new MeinOrt(laengengrad, breitengrad, name, parameter);
            navVerwaltung->getOrte().push_back(pos);
            QPoint pixel_coordinates = gpsToPixel(laengengrad, breitengrad,mapLabel);

            QRadioButton* newButton = new QRadioButton(QString::fromStdString(name), mapLabel);
            newButton->setGeometry(pixel_coordinates.x(), pixel_coordinates.y(), 150, 50);
            newButton->setProperty("associatedOrt", QVariant::fromValue(static_cast<void*>(pos)));
            newButton->show();
            connect(newButton, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);


        }
    }

    datei.close();
    QMessageBox::information(this, "Erfolg", "Karte wurde erfolgreich geladen.");

}
void MainWindow::onMeinStandortClicked() {

    QMessageBox::StandardButton choice = QMessageBox::question(
        nullptr,
        "Aktuelle Position",
        "Was möchten Sie MeinOrt verschieben ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (choice == QMessageBox::Yes) {
        bool ok;
        double Laengen = QInputDialog::getDouble(nullptr, "Längengrad", "Geben Sie bitte den Längengrad ein:", 0, -180, 180, 8, &ok);
        if (!ok) return;
        double Breiten = QInputDialog::getDouble(nullptr, "Breitengrad", "Geben Sie bitte den Breitengrad ein:", 0, -90, 90, 8, &ok);
        if (!ok) return;

        navVerwaltung->AktuellePosition(Laengen,Breiten);
        QPoint pixel_coordinates = gpsToPixel(Laengen, Breiten,mapLabel);
        ui->meinOrt->move(pixel_coordinates.x(), pixel_coordinates.y());
        ui->meinOrt->show();
        QMessageBox::information(nullptr, "Erfolg", "Ihre Position wurde hinzugefügt.");

    }
    else{
        if (!ui->meinOrt) {
            QMessageBox::critical(this, "Fehler", "Meinort Button wurde nicht gefunden.");
            return;
        }

        ui->meinOrt->setStyleSheet("QRadioButton { background-color: yellow; }");


        QTimer::singleShot(2000, this, [this]() {
            ui->meinOrt->setStyleSheet("");
        });}
}





MainWindow::~MainWindow()
{
    delete ui;
    delete navVerwaltung;
}

void MainWindow::setupMap()
{


    QPixmap mapImage("/Users/aminecht/Documents/Studium/Prog 2/navigation_karte/866-8664209_leer-deutschland-karte.png");

    if (mapImage.isNull()) {
        qDebug() << "Failed to load the map image!";
        QMessageBox::warning(this, "Image Load Error", "Failed to load the map image.");
        return;
    }

    mapLabel->setPixmap(mapImage);
    mapLabel->setFixedSize(mapImage.size());



    /** ui->cityButton1->setParent(mapLabel);
    ui->cityButton1->move(750, 410);  // Berlin
    ui->cityButton1->show();
    ui->cityButton2->setParent(mapLabel);
    ui->cityButton2->move(295, 325);  // Bremen
    ui->cityButton2->show();
    ui->cityButton3->setParent(mapLabel);
    ui->cityButton3->move(600, 1050);  //München
    ui->cityButton3->show();
    ui->cityButton4->setParent(mapLabel);
    ui->cityButton4->move(100, 900);  //Saarbrücken
    ui->cityButton4->show();
    ui->cityButton5->setParent(mapLabel);
    ui->cityButton5->move(400, 1000);  //Stuttgart
    ui->cityButton5->show();
    ui->meinOrt->setParent(mapLabel);
    ui->meinOrt->move(299, 890);  // MeinOrt
    ui->meinOrt->show();


    navVerwaltung->getOrte().push_back(new MeinOrt(49.86682, 8.639912, "h-da", "Mein Ort"));
    navVerwaltung->getOrte().push_back(new Poi(52.5200, 13.4050, "Berlin", "Hauptstadt"));
    navVerwaltung->getOrte().push_back(new Poi(53.0793, 8.8017, "Bremen", "Freie Hansestadt"));
    navVerwaltung->getOrte().push_back(new Poi(48.1351, 11.5820, "München", "Landeshauptstadt Bayern"));
    navVerwaltung->getOrte().push_back(new Poi(49.0073, 7.1287, "Saarbrücken", "Landeshauptstadt Saarland"));
    navVerwaltung->getOrte().push_back(new Poi(48.7758, 9.1829, "Stuttgart", "Landeshauptstadt Baden-Württemberg"));
**/
    /**QRadioButton* meinOrt = new QRadioButton("h-da", mapLabel);
    // Create meinOrt as a member variable to ensure accessibility in other methods
     ui->meinOrt->move(299, 890);  // Adjust position as needed
     ui->meinOrt->show();**/


    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(mapLabel);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    setCentralWidget(scrollArea);

    QPushButton* distanceButton = new QPushButton("Entfernung berechnen", this);
    distanceButton->setObjectName("distanceButton");
    distanceButton->setGeometry(1000, 500, 180, 40);
    connect(distanceButton, &QPushButton::clicked, this, &MainWindow::onDistanceButtonClicked);
    QPushButton* infoButton = new QPushButton("Information", this);
    infoButton->setObjectName("infoButton");
    infoButton->setGeometry(1000, 540, 180, 40);
    connect(infoButton, &QPushButton::clicked, this, &MainWindow::infButtonCkicked);
    QPushButton* allLocationsButton = new QPushButton("Alle Orte", this);
    allLocationsButton->setObjectName("allLocationsButton");
    allLocationsButton->setGeometry(1000, 580, 180, 40);
    connect(allLocationsButton, &QPushButton::clicked, this, &MainWindow::alleOrteButton);



    QPushButton* meinStandortButton = new QPushButton("Mein Standort", this);
    meinStandortButton->setObjectName("meinStandortButton");
    meinStandortButton->setGeometry(1000, 620, 180, 40);
    connect(meinStandortButton, &QPushButton::clicked, this, &MainWindow::onMeinStandortClicked);

    QPushButton* neueEingabeButton = new QPushButton("Neueingabe eines Orte", this);
    neueEingabeButton ->setObjectName("neueEingabeButton ");
    neueEingabeButton ->setGeometry(1000, 460, 180, 40);
    connect(neueEingabeButton , &QPushButton::clicked, this, &MainWindow::neueEingabeClicked);

}
QPoint MainWindow::gpsToPixel(double latitude, double longitude, QLabel* mapLabel){

    double minLongitude = 5.866;
    double maxLongitude = 15.042;
    double minLatitude = 47.270;
    double maxLatitude = 55.058;


    int width = mapLabel->width();
    int height = mapLabel->height();


    int x = static_cast<int>((longitude - minLongitude) / (maxLongitude - minLongitude) * width);
    int y = static_cast<int>((maxLatitude - latitude) / (maxLatitude - minLatitude) * height);

    return QPoint(x, y);
}


void MainWindow::neueEingabeClicked()
{
    int idNachbar;
    string nachbarName;
    QStringList optionen = {"Adresse", "POI"};
    QString auswahl = QInputDialog::getItem(this, "Ort hinzufügen", "Was möchten Sie hinzufügen?", optionen, 0, false);

    if (auswahl == "Adresse") {
        double laengengrad = QInputDialog::getDouble(this, "Breitengrad eingeben", "Breitengrad:" , 0.0000, -1000.0, 1000.0, 10);
        double breitengrad = QInputDialog::getDouble(this, "Längengrad eingeben", "Längengrad:", 0.0000, -1000.0, 1000.0, 10);
        QString name = QInputDialog::getText(this, "Name eingeben", "Name:");

        QString parameter = QInputDialog::getText(this, "Parameter eingeben", "Parameter:");



        Adresse* adresse = new Adresse(laengengrad, breitengrad,name.toStdString(),parameter.toStdString());
        navVerwaltung->getOrte().push_back(adresse);
        idNachbar=navVerwaltung->nachbarSuchen(adresse);
        nachbarName=navVerwaltung->getName(idNachbar);
        QMessageBox::information(this, "Nachbar", QString("Die ID von Nachbar ist: %1").arg(QString::fromStdString(nachbarName)));

        std::string updatedParameter = adresse->getParameter() + " Nachbar ID: " + std::to_string(idNachbar);


        adresse->setParameter(updatedParameter);

        QPoint pixel_coordinates = gpsToPixel(laengengrad, breitengrad,mapLabel);

        QRadioButton* newButton = new QRadioButton(name, mapLabel);
        newButton->setGeometry(pixel_coordinates.x(), pixel_coordinates.y(), 150, 50);
        newButton->setProperty("associatedOrt", QVariant::fromValue(static_cast<void*>(adresse)));
        newButton->show();
        connect(newButton, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);


        connect(newButton, &QRadioButton::toggled, [this, name](bool checked) {
            if (checked) {
                QMessageBox::information(this, "Button Clicked", QString("Button for %1 clicked!").arg(name));
            }
        });

    }
    else if (auswahl == "POI") {
        double laengengrad = QInputDialog::getDouble(this, "Breitengrad eingeben", "Breitengrad:" ,0.0000,-1000.0,  1000.0,6);
        double breitengrad = QInputDialog::getDouble(this, "Längengrad eingeben", "Längengrad:",0.0000,-1000.0,  1000.0,6);
        QString name = QInputDialog::getText(this, "Name eingeben", "Name:");

        QString parameter = QInputDialog::getText(this, "Parameter eingeben", "Parameter:");

        Poi* poi = new Poi(laengengrad, breitengrad,name.toStdString(),parameter.toStdString());
        navVerwaltung->getOrte().push_back(poi);
        idNachbar=navVerwaltung->nachbarSuchen(poi);
        nachbarName=navVerwaltung->getName(idNachbar);
        QPoint pixel_coordinates = gpsToPixel(laengengrad, breitengrad,mapLabel);

        QMessageBox::information(this, "Nachbar", QString("Die ID von Nachbar ist: %1").arg(QString::fromStdString(nachbarName)));
        std::string updatedParameter = poi->getParameter() + " Nachbar ID: " + std::to_string(idNachbar);
        poi->setParameter(updatedParameter);
        Ort* nachbarPoi = navVerwaltung->getOrte(idNachbar);// Assuming you have a way to get the neighbor POI
        QPoint nachbarPixelCoordinates = gpsToPixel(nachbarPoi->getLängengrad(), nachbarPoi->getBreitengrad(), mapLabel);

        QPainter painter(mapLabel);
        painter.setPen(QPen(Qt::red, 2)); // Set the line color and width
        painter.drawLine(pixel_coordinates, nachbarPixelCoordinates); // Draw line between the new POI and its neighbor



        QRadioButton* newButton = new QRadioButton(name, mapLabel);
        newButton->setGeometry(pixel_coordinates.x(), pixel_coordinates.y(), 150, 50);
        newButton->setProperty("associatedOrt", QVariant::fromValue(static_cast<void*>(poi)));
        newButton->show();
        connect(newButton, &QRadioButton::toggled, this, &MainWindow::onCityButtonToggled);


        connect(newButton, &QPushButton::clicked, [this, name]() {
            QMessageBox::information(this, "Button Clicked", QString("Button for %1 clicked!").arg(name));

        });
    }
    else {
        QMessageBox::warning(this, "Warnung", "Ungültige Eingabe!");
    }
}


void MainWindow::alleOrteButton() {

    QMessageBox* outputBox = new QMessageBox(this);
    outputBox->setWindowTitle("Karteanzeigen");


    navVerwaltung->Karteanzeigen(outputBox);


    outputBox->exec();

}




void MainWindow::onDistanceButtonClicked()
{
    qDebug() << "Selected cities count:" << entfernung.size();
    for (Ort* city : entfernung) {
        qDebug() << "City in list:" << QString::fromStdString(city->getName());
    }

    if (entfernung.size() != 2) {
        QMessageBox::warning(this, "Fehler", "Bitte genau zwei Städte auswählen!");
        entfernung.clear();
        return;
    }

    Ort* city1 = entfernung[entfernung.size()-2];
    Ort* city2 = entfernung[entfernung.size()-1];


    if (!city1 || !city2) {
        QMessageBox::critical(this, "Fehler", "Ein oder beide ausgewählten Orte sind ungültig!");
        return;
    }


    double distance = navVerwaltung->berechnungvonentfernung(city1, city2);


    QString formattedDistance = QString::number(distance, 'f', 2);


    QMessageBox::information(this, "Entfernung",
                             QString("Die Entfernung zwischen %1 und %2 beträgt %3 km.")
                                 .arg(QString::fromStdString(city1->getName()))
                                 .arg(QString::fromStdString(city2->getName()))
                                 .arg(formattedDistance));
    entfernung.clear();

}


void MainWindow::infButtonCkicked() {

    if (selectedCities.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Kein Ort ausgewählt!");
        return;
    }

    Ort* selectedCity = selectedCities.first();
    if (!selectedCity) {
        QMessageBox::warning(this, "Fehler", "Kein gültiger Ort ausgewählt!");
        return;
    }

    QString info = QString("ID: %1\nName: %2\nKoordinaten: %3, %4\nParameter: %5")
                       .arg(selectedCity->getId())
                       .arg(QString::fromStdString(selectedCity->getName()))
                       .arg(QString::number(selectedCity->getLängengrad(), 'f', 2))
                       .arg(QString::number(selectedCity->getBreitengrad(), 'f', 2))
                       .arg(QString::fromStdString(selectedCity->getParameter()));

    QMessageBox::information(this, "Stadtinformationen", info);

    selectedCities.removeOne(selectedCity);
    qDebug() << "Removed city from infobutton:" << QString::fromStdString(selectedCity->getName());
}

Ort* MainWindow::getCityFromButton(QRadioButton* button) {
    auto &orte = navVerwaltung->getOrte();
    try {
        if (button == ui->meinOrt) {
            return orte.at(0);
        }
        else if (button == ui->cityButton1) {
            return orte.at(1);
        } else if (button == ui->cityButton2) {
            return orte.at(2);
        } else if (button == ui->cityButton3) {
            return orte.at(3);
        } else if (button == ui->cityButton4) {
            return orte.at(4);
        } else if (button == ui->cityButton5) {
            return orte.at(5);
        } else if (button) {
            QVariant associatedOrt = button->property("associatedOrt");
            if (associatedOrt.isValid()) {
                return static_cast<Ort*>(associatedOrt.value<void*>());
            }
        }
    } catch (const std::out_of_range&) {
        qDebug() << "Index out of bounds when accessing Orte vector!";
    }
    return nullptr;
}

void MainWindow::onCityButtonToggled(bool checked) {
    QRadioButton* button = qobject_cast<QRadioButton*>(sender());
    if (button) {
        Ort* city = getCityFromButton(button);
        if (city) {
            if (checked) {

                if (infoCity != city) {
                    infoCity = city;
                    if (std::find(selectedCities.begin(), selectedCities.end(), city) == selectedCities.end()) {
                        selectedCities.push_back(city);
                        entfernung.push_back(city);
                    }
                    qDebug() << "Selected city for info mode:" << QString::fromStdString(city->getName());
                } else {
                    qDebug() << "City already selected.";
                }
            } else {

                if (infoCity == city) {
                    infoCity = nullptr;
                    auto it = std::find(selectedCities.begin(), selectedCities.end(), city);
                    if (it != selectedCities.end()) {
                        selectedCities.erase(it);
                    }
                    qDebug() << "City deselected.";
                }
            }
        } else {
            qDebug() << "No associated Ort found for this button!";
        }
    } else {
        qDebug() << "Sender is not a QRadioButton!";
    }
}

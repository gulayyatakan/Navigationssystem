#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_MainWindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include"navigationsverwaltung.h"
#include"ort.h"
#include <QHBoxLayout>
#include <QList>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void onCityButtonToggled(bool checked);
    void onDistanceButtonClicked();
    void infButtonCkicked();
    void alleOrteButton();
    void  onMeinStandortClicked();
    void saveData() ;
    void loadData();
    void neueEingabeClicked();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<Ort*> getLastTwoCities();
    QPoint gpsToPixel(double latitude, double longitude, QLabel* mapLabel);
private:

    void setupMap();
    Ui::MainWindow *ui;
    Navigationsverwaltung* navVerwaltung;
    QVector<Ort*> selectedCities;
    QVector<Ort*> entfernung;
    Ort* getCityFromButton(QRadioButton* button);
    QTextEdit* outputBox;
    QHBoxLayout *horizontalLayout;
    QLabel* mapLabel = new QLabel(this);
    QRadioButton* meinOrt;
    QMap<QRadioButton*, Ort*> buttonToOrtMap;
    bool isDistanceMode = false;
    Ort* infoCity;

};

#endif // MAINWINDOW_H

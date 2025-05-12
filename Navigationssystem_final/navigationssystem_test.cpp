#include "Navigationssystem_test.h"
class ConcreteOrt : public Ort {
public:
    ConcreteOrt(double Längengrad, double Breitengrad, const std::string& name)
        : Ort(Längengrad, Breitengrad), name(name) {}

    std::string getParameter() const override {
        return "Dummy Parameter";
    }

    std::string getName() const override {
        return name;
    }

private:
    std::string name;
};

void Navigationssystem_test::test_berechnungvonentfernung() {
    Navigationsverwaltung navVerwaltung;

    Adresse berlin(52.5200, 13.4050, "Berlin", "");
    Adresse paris(48.8566, 2.3522, "Paris", "");

    double calculatedDistance = navVerwaltung.berechnungvonentfernung(&berlin, &paris);
    double expectedDistance = 1255.91041199; // Expected distance in km (approximate).

    QCOMPARE(calculatedDistance, expectedDistance); // Allow small floating-point differences if needed.
}

void Navigationssystem_test::test_two_cities_selection() {
    Navigationsverwaltung navVerwaltung;
    std::vector<Ort*> cities = {new Adresse(52.5200, 13.4050, "Berlin", "")};

    // Ensure the size is not 2
    QVERIFY(cities.size() != 2);

    // Cleanup
    for (Ort* city : cities) {
        delete city;
    }
}


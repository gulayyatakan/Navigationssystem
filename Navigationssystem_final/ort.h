#ifndef ORT_H
#define ORT_H
#include<iostream>
#include<vector>
using namespace std;

class Ort
{
public:
    Ort(double Längengrad,double Breitengrad);
    virtual~Ort()=default;


    double getLängengrad() const;
    void setLängengrad(double newLängengrad);

    double getBreitengrad() const;
    void setBreitengrad(double newBreitengrad);
    virtual string getParameter() const=0;
    int getId() const;
    virtual std::string getName() const = 0;


    static void setCounter(int newCounter);

private:
    const double Längengrad;
    const double Breitengrad;
    int Id;
    static int counter;

};

#endif // ORT_H

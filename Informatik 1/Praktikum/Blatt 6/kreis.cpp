#include <iostream>
#include "kreis.h"
#include <cmath>

using namespace std;

Kreis::Kreis()
{
    x = 0.0;
    y = 0.0;
    radius = 1.0;
}
Kreis::Kreis(double ax, double ay, double aradius)
{
    {
        if (ax < -100)
        {
            cout << "x liegt außerhalb des Wertebereichs. Setze auf -100..." << endl;
            x = -100;
        }
       else if (ax > 100)
        {
            cout << "x liegt außerhalb des Wertebereichs. Setze auf 100..." << endl;
            x = 100;
        } else
            x = ax;
        if (ay < -100)
        {
            cout << "y liegt außerhalb des Wertebereichs. Setze auf -100..." << endl;
            y = -100;
        }
        else if (ay > 100)
        {
            cout << "y liegt außerhalb des Wertebereichs. Setze auf 100..." << endl;
            y = 100;
        }
        else
            y = ay;
        if (aradius < 1)
        {
            cout << "Der Radius liegt außerhalb des Wertebereichs. Setze auf 1..." << endl;
            radius = 1;
        }
        else if (aradius > 50)
        {
            cout << "Der Radius liegt außerhalb des Wertebereichs. Setze auf 50..." << endl;
            radius = 50;
        } else
            radius = aradius;
    }
}
void Kreis::setzeX(double ax)
{
    if (ax < -100)
    {
        cout << "x liegt außerhalb des Wertebereichs. Setze auf -100..." << endl;
        x = -100;
    }
    else if (ax > 100)
    {
        cout << "x liegt außerhalb des Wertebereichs. Setze auf 100..." << endl;
        x = -100;
    }
    else
    x = ax;
}
void Kreis::setzeY(double ay)
{
    if (ay < -100)
    {
        cout << "y liegt außerhalb des Wertebereichs. Setze auf -100..." << endl;
        y = -100;
    }
    else if (ay > 100)
    {
        cout << "y liegt außerhalb des Wertebereichs. Setze auf 100..." << endl;
        y = 100;
    }
    else
        y = ay;
}
void Kreis::setzeRadius(double aradius)
{
    if (aradius < 1)
    {
        cout << "Der Radius liegt außerhalb des Wertebereichs. Setze auf 1..." << endl;
        radius = 1;
    }
    else if (aradius > 50)
    {
        cout << "Der Radius liegt außerhalb des Wertebereichs. Setze auf 50..." << endl;
        radius = 50;
    } else
        radius = aradius;
}
double Kreis::getX()
{
    return x;
}
double Kreis::getY()
{
    return y;
}
double Kreis::getRadius()
{
    return radius;
}
double Kreis::umfang()
{
    return 2 * M_PI * radius;
}
double Kreis::flaeche()
{
    return M_PI*pow(radius, 2);
}
bool Kreis::liegtInnerhalb(double ax, double ay)
{
    double deltax = ax - x;
    double deltay = ay - y;
    return (pow(deltay, 2) + pow(deltax, 2)) <= radius;
}

int main()
{
    Kreis kreisEinheit;
    Kreis kreis2(0.0, 0.0, 2);
    Kreis punktTest(2.0, 2.0, 1);
    cout << "Fläche vom Einheitskreis: " << kreisEinheit.flaeche() << endl;
    cout << "Umfang vom Einheitskreis: " << kreisEinheit.umfang() << endl;
    cout << "Fläche vom Kreis mit dem anderen Radius: " << kreis2.flaeche() << endl;
    cout << "Umfang vom Kreis mit dem anderen Radius: " << kreis2.umfang() << endl;
    if (punktTest.liegtInnerhalb(1.25, 1.25))
    {
        cout << "Der Punkt (1.25, 1.25) liegt innerhalb des Kreises mit dem Mittelpunkt (2, 2)." << endl;
    }
    else
    {
        cout << "Der Punkt (1.25, 1.25) liegt NICHT innerhalb des Kreises mit dem Mittelpunkt (2, 2)." << endl;
    }
    return 0;
}
#include <iostream>
#include <cstring>

using namespace std;

class Fahrzeug
{
private:
    int hubraum;
    int leistung;
    string farbe;
    int raeder;
    double zustand;
public:
    Fahrzeug(int ihubraum, int ileistung, string ifarbe, int iraeder, double izustand): hubraum(ihubraum), leistung(ileistung), farbe(ifarbe), raeder(iraeder), zustand(izustand) {}
    Fahrzeug(): hubraum(623), leistung(26), farbe("Schwarz"), raeder(4), zustand(100.00) {}
    void printDetails();
    void tunen();
    void fahren(int strecke);
    bool istSchrott();
};

void Fahrzeug::printDetails() {
    cout << "Fahrzeugdetails:" << endl;
    cout << "Hubraum (in ccm)\tLeistung (in kW)\tFarbe\t\tRäder\t Zustand (in %)" << endl;
    cout << hubraum << "\t\t\t" << leistung << "\t\t\t" << farbe << "\t\t" << raeder  << "\t" << zustand << endl;
}
void Fahrzeug::tunen()
{
    if (istSchrott()) //pre-check
    {
        cout << "Das Fahrzeug ist kaputt und kann nicht mehr getunt werden." << endl;
        return;
    }
    leistung *= 1.15;
    zustand = zustand - 10;
    if (istSchrott()) //post-check
    {
        cout << "Das Fahrzeug ist beim Tunen leider zusammengebrochen. :(" << endl;
        return;
    }
    cout << "Fahrzeug getunt! Die Leistung beträgt nun " << leistung << "kW und der Zustand des Fahrzeugs beträgt " << zustand << "%." << endl;
}
void Fahrzeug::fahren(int kilometer)
{
    if (istSchrott()) //pre-check
    {
        cout << "Das Fahrzeug ist kaputt und kann nicht mehr gefahren werden." << endl;
        return;
    }
    double verschleiss = 0.00002 * kilometer;
    zustand = zustand - verschleiss;
    if (istSchrott()) //post-check
    {
        cout << "Das Fahrzeug hat auf der Strecke leider das Zeitliche gesegnet. Schade... :(" << endl;
        return;
    }
    cout << "Das Fahrzeug ist " << kilometer << "km gefahren. Der Zustand des Fahrzeugs beträgt nun " << zustand << "%." << endl;
}
bool Fahrzeug::istSchrott()
{
    if (zustand <= 0)
        return true;
    else return false;
}
int main()
{
    Fahrzeug gti(1984, 162, "Schwarz", 4, 100.00);
    Fahrzeug ecoAuto;
    gti.printDetails();
    ecoAuto.printDetails();
    ecoAuto.tunen();
    ecoAuto.fahren(150);
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.tunen();
    ecoAuto.fahren(450000);
    ecoAuto.fahren(100000);
return 0;
}
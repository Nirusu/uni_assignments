#include <iostream>

using namespace std;

int main ()

{

    int monat;

    char schaltjahr;

    cout << " Bitte geben Sie die Nummer des Monats ein " << endl;

    cout << "1- Januar , 2- Februar , ... , 12- Dezember " << endl;

    cin >> monat;

    while (monat < 1 || monat > 12) // keinen Buchstaben oder etwas, was einen Overflow verursacht, eingeben, sonst gibt's die Schleife des Bösen

    {

        cout << "Die Eingabe muss zwischen 1 und 12 liegen." << endl;

        cin >> monat;

    }

    if (monat == 2)

    {

        schaltjahr = 'z'; //Platzhalter

        cout << "Schaltjahr?" << endl;

        while (schaltjahr != 'j' && schaltjahr != 'J' && schaltjahr != 'n' && schaltjahr != 'N')

        {

            cin >> schaltjahr;

        }

        if (schaltjahr == 'j' || schaltjahr == 'J')

        {

            cout << "Der Monat hat 29 Tage." << endl;

        }

        else

        {

            cout << "Der Monat hat 28 Tage." << endl;

        }

    }

    else if (monat == 4 || monat == 6) // manuelle Prüfung, da sich für diese zwei Monate eine Prüfung auf geraden Zahlen nicht lohnt, da der Februar ja auch wieder eine Ausnahme ist.

    {

        cout << "Der Monat hat 30 Tage." << endl;

    }

    else if (monat <=7 && monat % 2 != 0)

    {

        cout << "Der Monat hat 31 Tage." << endl;

    }

    else if (monat >=8 && monat % 2 == 0)

    {

        cout << "Der Monat hat 31 Tage." << endl;

    }

    else

    {

        cout << "Der Monat hat 30 Tage." << endl;

    }

    return 0;

}

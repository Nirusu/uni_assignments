//-----------------------------------------------
// Rahmenprogramm zu Blatt 5, Aufgabe 2
//-----------------------------------------------

#include <iostream>
using namespace std;


void PascalschesDreieck(int **pascal, int n)
{
    int breite = 1;
    for (int i=0; i<n; i++)
    {
        pascal[i] = new int[breite];
        if (i == 0)
        {
            pascal[0][0] = 1;

        }
        else if (i == 1)
        {
            pascal[1][0] = 1;
            pascal[1][1] = 1;
        }
        else
        {
            pascal[i][0] = 1;
            for (int j=1; j<breite; j++) {
                pascal[i][j] = pascal[i - 1][j] + pascal[i - 1][j - 1];
            }
            pascal[i][breite-1] = 1;
        }
        breite++;
    }
    // TODO: Code zur Berechnung des Dreiecks hier einfuegen (2 Punkte)
}


int main()
{
    int n = 0;
    int **pascal;

    // TODO: Code zur Eingabe der Anzahl zu berechnender Zeilen hier einfuegen (1 Punkt)
    cin >> n;

    // TODO: Code zur Reservierung des Speichers hier einfuegen (2 Punkte)
    pascal = new int*[n];

    // Berechnung des Dreiecks
    PascalschesDreieck(pascal,n);


    // TODO Code zur Ausgabe des Dreiecks hier einfuegen (2 Punkte)
    int breite = 1;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<breite; j++)
        {
            cout << pascal[i][j] << " ";
        }
        cout << endl;
        breite++;
    }
    // TODO: Code zur Freigabe des Speichers hier einfuegen (1 Punkt)

    delete pascal;

    return 0;
}
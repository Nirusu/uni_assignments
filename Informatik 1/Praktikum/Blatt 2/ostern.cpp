   /*
    * ostern.cpp
    * Ein Programm zur Berechnung des Datums des Ostersonntags
    * fuer ein vorgegebenes Jahr
    */

    #include<iostream>
    using namespace std;

    int main() {
        // Variablen nach http://de.wikipedia.org/wiki/Gau%C3%9Fsche_Osterformel
        // (Gregorianischer Kalender)
        int Jahr = 2084;
        int Ostern;
        int a, b, c, d, e, k, p, q, N, M;

        //++++++++++++++++++++++++++++++++++++++++++++
        // Hier bitte die Berechnungsfolge einfuegen:

        a = Jahr % 19;
        b = Jahr % 4;
        c = Jahr % 7;
        k = Jahr / 100;
        p = (8*k + 13) / 25;
        q = k / 4;
        M = (15 + k - p - q) % 30;
        d = (19*a + M) % 30;
        N = (4 + k - q) % 7;
        e = (2*b + 4*c + 6*d + N) % 7;
        Ostern = (22 + d + e);


        //++++++++++++++++++++++++++++++++++++++++++++

        cout << "Der Ostersonntag ist am ";
        if (Ostern <= 31)
            cout << Ostern << ". Maerz " << Jahr << endl;
        else
            cout << (Ostern - 31) << ". April " << Jahr << endl;

        return 0;
    }

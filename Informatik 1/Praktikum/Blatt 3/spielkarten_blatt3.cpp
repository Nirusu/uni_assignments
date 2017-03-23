/*
 *  Definiert Wert und Farbe von Spielkarten als
 *  Aufzählungstyp und gibt alle Spielkarten in
 *  aufsteigender Reihenfolge aus
 */
#include <iostream>
using namespace std;

int main() {
	enum wert {
		Sieben, Acht, Neun, Zehn, Bube, Dame, Koenig, As
	};
	enum farbe {
		Karo, Herz, Pik, Kreuz
	};
	for (int j = 7; j >= 0; j--) {
		for (int i = 3; i >= 0; i--) {
			switch (i) {
			case Kreuz:
				cout << "Kreuz ";
				break;
			case Pik:
				cout << "Pik ";
				break;
			case Herz:
				cout << "Herz ";
				break;
			case Karo:
				cout << "Karo ";
				break;
			}
			switch (j) {
			case As:
				cout << "As" << endl;
				break;
			case Koenig:
				cout << "Koenig" << endl;
				break;
			case Dame:
				cout << "Dame" << endl;
				break;
			case Bube:
				cout << "Bube" << endl;
				break;
			case Zehn:
				cout << "Zehn" << endl;
				break;
			case Neun:
				cout << "Neun" << endl;
				break;
			case Acht:
				cout << "Acht" << endl;
				break;
			case Sieben:
				cout << "Sieben" << endl;
				break;
			}

		}
	}
	return 0;
}

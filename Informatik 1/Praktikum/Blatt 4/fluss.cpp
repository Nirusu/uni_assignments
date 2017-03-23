/*
 *  Das Programm erlaubt es Spielstrategien des bekannten
 *  Ziege-Wolf-Kohlkopf-Problems interaktiv durchzuspielen.
 */

#include <iostream>
using namespace std;

int main()
{
	enum subjekte {Bauer,Kohlkopf,Wolf,Ziege};
	enum ufer {ufer_links,ufer_rechts};
	struct info {char name[10]; ufer ort;};

	info lage[4] = {{"Bauer", ufer_links}, {"Kohlkopf", ufer_links}, {"Wolf", ufer_links}, {"Ziege", ufer_links}};

	bool abbruch = false;
	int status;
	char input;
	do {
	status = 1337; // um falsche Eingaben abzufangen.
	cout << "Ufer links: ";
	for(info currentlage: lage)
	{
		if (currentlage.ort == ufer_links)
		{
			cout << currentlage.name << " ";
		}
	}
	cout << endl << "-----------------------------------------------------" << endl;
	cout << "Ufer rechts: ";
	for(info currentlage: lage)
	{
		if (currentlage.ort == ufer_rechts)
		{
			cout << currentlage.name << " ";
		}
	}
	cout << endl;
	if (lage[Wolf].ort == lage[Ziege].ort && lage[Bauer].ort != lage[Ziege].ort && lage[Kohlkopf].ort != lage[Ziege].ort)
	{
		cout << "Wolf und Ziege sind alleine auf einer Seite. Leider verloren!";
		abbruch = true;
	}
	else if (lage[Ziege].ort == lage[Kohlkopf].ort && lage[Bauer].ort != lage[Ziege].ort && lage[Wolf].ort != lage[Ziege].ort)
	{
		cout << "Kohlkopf und Ziege sind alleine auf einer Seite. Leider verloren!";
		abbruch = true;
	}
	else if (lage[Bauer].ort == ufer_rechts && lage[Kohlkopf].ort == ufer_rechts && lage[Wolf].ort == ufer_rechts && lage[Ziege].ort == ufer_rechts)
	{
		cout << "Du hast gewonnen, herzlichen Glueckwunsch!";
		abbruch = true;
	}
	if (!abbruch){
	cout << "Aktion eingeben: ";
	cin >> input;
		switch(input)
		{
		case 'K':
			status = 1;
			break;
		case 'W':
			status = 2;
			break;
		case 'Z':
			status = 3;
			break;
		case 'B':
			status = 0;
			break;
		case 'Q':
			abbruch = true;
			break;
		}
		if (status != 0 && status < 4)
		{
			if (lage[status].ort == ufer_links && lage[Bauer].ort == ufer_links)
						{
							lage[status].ort=ufer_rechts;
							lage[Bauer].ort=ufer_rechts;
						}
						else if (lage[status].ort == ufer_rechts && lage[Bauer].ort == ufer_rechts)
						{
							lage[status].ort=ufer_links;
							lage[Bauer].ort=ufer_links;
						}
		}
		else if (status == 0)
		{
			if (lage[Bauer].ort == ufer_links)
			lage[Bauer].ort=ufer_rechts;
			else
			lage[Bauer].ort=ufer_links;
		}
		else if (status >= 4)
		{
			cout << "Ungültige Eingabe.";
		}
		cout << endl;
	}
	}
	while(!abbruch);
	return 0;
}

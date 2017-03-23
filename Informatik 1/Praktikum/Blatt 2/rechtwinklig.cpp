#include <iostream>
using namespace std;

int main()
{
	int a = 2;
	int b = 3;
	int c = 4;
	if (c <= a || c <= b) // Der Satz des Pytagoras erfordert, dass c die größte Zahl ist, da c ja die Hypothenuse ist, welcher per Definition die längste Seite in einem rechtwinkligen Dreieck ist. Wäre c also kleiner, würde der Satz des Pytagoras sowieso nicht zutreffen, weshalb wir abbrechen können.
	{
		cout << "c ist nicht das Maximum!" << endl;
		return 1;
	}
	else if (a <= 0 || b <= 0 || c <= 0)
	{
		cout << "Nicht alle Variablen sind positiv!" << endl;
		return 1;
	}
	else if (a*a + b*b != c*c)
	{
		cout << "Das Dreieck mit den Seitenlaengen " << a << ", " << b << ", " << c << " ist NICHT rechtwinklig." << endl;
		return 0;
	}
	else
	{
		cout << "Das Dreieck mit den Seitenlaengen " << a << ", " << b << ", " << c << " ist rechtwinklig." << endl;
		return 0;
	}
}

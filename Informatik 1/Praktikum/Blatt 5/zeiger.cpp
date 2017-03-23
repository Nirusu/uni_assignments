#include <iostream>
using namespace std;

int main() {
    int i = 40;
    int j = 21;
    int *p = &i;
    int *q = &j;
    cout << "Teilaufgabe A:" << endl;
    cout << '\t' << '\t' << '\t' << "Adresse:" << '\t' << '\t' << "Inhalt" << '\t' << '\t' << '\t' << "referenzierter Wert:" << endl;
    cout << "Variable i" << '\t' << &i << '\t' << i << endl;
    cout << "Variable j" << '\t' << &j << '\t' << j << endl;
    cout << endl;
    cout << "Zeiger p" << '\t' << &p << '\t' << p << '\t' << *p << endl;
    cout << "Zeiger q"  << '\t' << &q  << '\t' << q << '\t' << *q << endl;
    cout << endl;
    int *tmp = p;
    p = q;
    q = tmp;
    cout << "Teilaufgabe B:" << endl;
    cout << '\t' << '\t' << '\t' << "Adresse:" << '\t' << '\t' << "Inhalt" << '\t' << '\t' << '\t' << "referenzierter Wert:" << endl;
    cout << "Variable i" << '\t' << &i << '\t' << i << endl;
    cout << "Variable j" << '\t' << &j << '\t' << j << endl;
    cout << endl;
    cout << "Zeiger p" << '\t' << &p << '\t' << p << '\t' << *p << endl;
    cout << "Zeiger q"  << '\t' << &q  << '\t' << q << '\t' << *q << endl;
    cout << endl;
    cout << endl;
    *q = *q + 2;
    cout << "Teilaufgabe D:" << endl;
    cout << '\t' << '\t' << '\t' << "Adresse:" << '\t' << '\t' << "Inhalt" << '\t' << '\t' << '\t' << "referenzierter Wert:" << endl;
    cout << "Variable i" << '\t' << &i << '\t' << i << endl;
    cout << "Variable j" << '\t' << &j << '\t' << j << endl;
    cout << endl;
    cout << "Zeiger p" << '\t' << &p << '\t' << p << '\t' << *p << endl;
    cout << "Zeiger q"  << '\t' << &q  << '\t' << q << '\t' << *q << endl;
    cout << endl;
}


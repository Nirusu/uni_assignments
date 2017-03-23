#include <iostream>
using namespace std;

int main() {
    int a;
	int b;
	char c = 'c';
	char d = '?';

	a = 7;
	b = 7;

	if(a < b) {
		cout << "der kleinere Wert ist a: " << a << endl;
	}
	else if (a > b) {
		cout << "der kleinere Wert ist b: " << b << endl;
	}
	else {
		cout << "beide Werte sind gleich groß: " << b << endl;
	}

    return 0;
}

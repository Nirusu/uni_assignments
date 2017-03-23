    #include <iostream>
	#include <math.h>
    using namespace std;

    int main() {
        int in;
        bool out[8] = {0};
        bool outInverted[8] = {0};
        int invToDec = 0;
        int pos = 8;
        int rest = 0;

        cout << "Bitte geben Sie eine Zahl ein:";
        cin >> in;

        if (in < 0 || in > 255) return 1;

        do {
            rest = in % 2;
            in = in / 2;
            out[--pos] = rest;
        } while (in > 0);

        // b)
        cout << "Binaerdarstellung: ";
        for (int i=0; i<8; i++)
            cout << out[i];

        // eigener Teil
        cout << endl << "Invertierte Binaerdarstellung: ";
        for (int i=0; i<8; i++)
        {
        	if (out[i] == 0)
        	{
        		outInverted[i] = 1;
        	}
        	else
        	{
        		outInverted[i] = 0;
        	}
        	invToDec += outInverted[i] * (pow(2, (7-i)));
        	cout << outInverted[i];
        }
        cout << endl;
        cout << "Invertierte Zahl: " << invToDec << endl;
        return 0;
    }

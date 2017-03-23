#include <iostream>

using namespace std;

int main () {

double a[10] = {12.6, 33.77, 51.32, 95.11, 19.78,

635.34, 85.18, 89.0, 37.5, 24.1};

double sum, quad, quadsum;

    sum = 0;

    quadsum = 0;

    quad = 0;

    for (int i=0; i<=(sizeof(a)/sizeof(*a))-1; i++)

    {

        sum += (a[i])/(i+1);

        quadsum += a[i]*a[i];

    }

    quad = quadsum/(sizeof(a)/sizeof(*a));

cout << "Gewichtete Summe: " << sum << endl;

cout << "Quadrat des quadratischen Mittels: ";

cout << quad << endl;



return 0;

}

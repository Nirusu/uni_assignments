#include <iostream>

using namespace std;



int main () {

int a[20] = {238, 18760, 14704, 19802, 25766,

25878, 4729, 14634, 18361, 9880,

29451, 30831, 30265, 10345, 20195,

9538, 492, 21769, 18197, 31417};

int sum;

int ctr;

sum = 0;

ctr = 0;

    for (int i=0; i<=(sizeof(a)/sizeof(*a))-1; i++)

    {

        sum += a[i] % 17;

        if ((a[i] % 4) != 0)

        {

            ctr++;

        }

    }

cout << "Summe der Reste: " << sum << endl;

cout << "Anzahl der Zahlen, die kein Vielfaches von 4 sind: ";

cout << ctr << endl;



return 0;

}

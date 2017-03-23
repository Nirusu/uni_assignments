#include <iostream>

using namespace std;

int main ()

{

    unsigned int m = 2;

    double sum = 0;

    long n;

    n = 0;

    do

    {

        n++;

        sum += (1/(double) n);

    }

    while(sum<=m);

    cout << "Man muss " << n <<" Zahlen aufsummieren ." << endl ;

    cout << "Die Summe ist " << sum << endl ;

    return 0;

}

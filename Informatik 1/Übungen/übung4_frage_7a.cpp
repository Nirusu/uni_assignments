#include <iostream>

using namespace std;

int main ()

{

    unsigned int m = 2;

    double sum = 0;

    long n;

    for(n=0; sum<=m; n++)

    {

        sum += (1/(double) (n+1)); // statt den Startwert anzupassen wird hier +1 im Bruch gerechnet da n=1 in der For-Schleife dafür sorgt, dass n am Ende um 1 zu hoch ist.

    }

    cout << "Man muss " << n <<" Zahlen aufsummieren ." << endl ;

    cout << "Die Summe ist " << sum << endl ;

    return 0;

}

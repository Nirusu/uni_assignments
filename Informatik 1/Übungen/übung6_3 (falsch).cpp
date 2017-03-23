#include <iostream>

using namespace std;

int numRekursion(int num, int n)
{
    int counter = 0;
    if (n == 1)
        return 1;
    
    switch (num)
    {
        case 0:
            counter += numRekursion(4, n-1);
            counter += numRekursion(6, n-1);
            break;
        case 1:
            counter += numRekursion(6, n-1);
            counter += numRekursion(8, n-1);
            break;
        case 2:
            counter += numRekursion(7, n-1);
            counter += numRekursion(9, n-1);
            break;
        case 3:
            counter += numRekursion(4, n-1);
            counter += numRekursion(8, n-1);
            break;
        case 4:
            counter += numRekursion(0, n-1);
            counter += numRekursion(3, n-1);
            counter += numRekursion(9, n-1);
            break;
            //case 5 gibt's nicht, man kann von der 5 aus nicht wie ein Springer springen
        case 6: 
            counter += numRekursion(0, n-1);
            counter += numRekursion(1, n-1);
            counter += numRekursion(7, n-1);
        case 7:
            counter += numRekursion(2, n-1);
            counter += numRekursion(6, n-1);
            break;
        case 8:
            counter += numRekursion(1, n-1);
            counter += numRekursion(3, n-1);
            break;
        case 9:
            counter += numRekursion(2, n-1);
            counter += numRekursion(4, n-1);
            break;
    }
    
    return counter;
}


int main() {
    int result = 0;
    for (int i=1; i<=9; i++)
    {
        result += numRekursion(i, 7); // Mitgliedsnummer hat 7 Ziffern
    }
    cout << "Es gibt " << result << " verschiedene Möglichkeiten." << endl;
    return 0;
}
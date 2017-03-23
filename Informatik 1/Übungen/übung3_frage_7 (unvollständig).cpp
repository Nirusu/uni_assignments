#include <iostream>

using namespace std;



int main ()

{

    const unsigned int n = 5;

    unsigned int matrix[n][n];

    int addition = 0;

    for (int i=0; i<n; i++)

    {

        for (int f=n; f>=0; f--)

        {

            matrix[i][f] = 0;

        }

    }

    for (int i=0; i<n; i++)

    {

        matrix[0][i] = i+1;

    }

    for (int i=1; i<n; i++)

    {

        matrix[i][n-1] = n+i;

    }

    for (int i=n-2; i>=0; i--)

    {

        matrix[n-1][i] = (2*n) + addition;

        if (i!=0)

        {

            matrix[i][0] = (3*n) + addition - 1;

            addition++;

        }

    }

//hier fehlt der Teil für den Rest, hat leider nicht ganz geklappt bei mir :(

    for (unsigned int r = 0; r < n; ++r)

    {

        for (unsigned int c = 0; c < n; ++c)

        {

            if (matrix [r][c] < 10)

            {

                cout << ' ';

            }

            cout << matrix[r][c] << ' ';

        }

        cout << endl;

    }



    return 0;

}

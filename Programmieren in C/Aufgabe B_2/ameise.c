#include <stdio.h>
#include "area.h"

struct Ameise
{
    int x;
    int y;
    enum {OBEN=0, RECHTS=1, UNTEN=2, LINKS=3} blick;
};




int main()
{
    struct Ameise ameise;

    int nextStep(struct Ameise* ameise, int len, char (*)[len]);

    int size;
    int stepcount;

    printf("Feldgroesse: ");
    scanf("%i", &size);

    printf("Schrittzahl: ");
    scanf("%i", &stepcount);

    char field[size][size];
    initArea(size, field);

    ameise.x = size/2;
    ameise.y = size/2;
    ameise.blick = 2;

    for (int i=0; i < stepcount; i++)
    {
        if(nextStep(&ameise, size, field) == 0)
        {
            printf("Rand des Rasters ueberschritten beim %i. Schritt!\n", i);
            break;
        }
    }
    showArea(size, field);
    return 0;
}

int nextStep(struct Ameise* ameise, int len, char (*cr)[len]) {
    if (ameise->x < 0 || ameise->y < 0 || ameise->y > len-1 || ameise->x > len-1)
    {
        return 0;
    }
    else if (cr[ameise->y][ameise->x] == ' ') {
        cr[ameise->y][ameise->x] = '#';
        ameise->blick = ((int) ameise->blick + 1) % 4;
    } else if (cr[ameise->y][ameise->x] == '#'){
        cr[ameise->y][ameise->x] = ' ';
        if((((int) ameise->blick - 1) % 4) < 0)
        {
            ameise->blick = (((int) ameise->blick - 1) % 4) + 4;
        }
        else
        {
            ameise->blick = ((int) ameise->blick - 1) % 4;
        }
    }
        if (ameise->blick == 0)
        {
            ameise->y--;
        }
        else if (ameise->blick == 1)
        {
            ameise->x++;
        }
        else if (ameise->blick == 2)
        {
            ameise->y++;
        }
        else if (ameise->blick == 3)
        {
            ameise->x--;
        }
        return 1;
}




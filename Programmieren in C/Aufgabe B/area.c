#include <stdio.h>
#include "area.h"

void initArea(int len, char (*area)[len])
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            area[i][j] = ' ';
        }
    }
    return;
}
void showArea (int len, char (*area)[len])
{
    printOuterBorder(len);
    for (int i=0; i < len; i++)
    {
        printf("|");
        for (int j=0; j < len; j++)
        {
            printf("%c", area[i][j]);
        }
        printf("|\n");
    }
    printOuterBorder(len);
    return;
}

void printOuterBorder(int len)
{
    printf("*");
    for (int i=0; i < len; i++)
    {
        printf("-");
    }
    printf("*\n");
    return;
}
#include <stdio.h>

int main() {
    FILE* datei1 = fopen("/Users/nils/Downloads/teil_1.txt", "r");
    FILE* datei2 = fopen("/Users/nils/Downloads/teil_2.txt" , "r");

    char c1;
    char c2;
    while (1)
    {
        c1 = fgetc(datei1);
        c2 = fgetc(datei2);
        if (c1 != EOF)
        printf("%c", c1);
        else break;
        if (c2 != EOF)
        printf("%c", c2);
        else break;
    }
    return 0;
}
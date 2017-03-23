#include <stdio.h>
#include <string.h>
#include "tipps.h"


int main()
{
    FILE* tipps;
    FILE* dreiAus;
    FILE* vierAus;
    char zeile[60]; //59 Zeichen + '\0'
    char snrTnr[10]; //9 Zeichen + '\0'
    int anzahlKreuze = 0;
    int kreuze[6] = {0, 0, 0, 0 ,0, 0};
    int gewinnZahlen[6];
    char datei[260]; //Pfad darf max. 260 Zeichen lang sein, was der max. Pfadlänge in Windows entspricht.
    printf("Bitte geben Sie den Pfad zur Tippdatei ein: ");
    scanf("%s", &datei);
    tipps = fopen(datei, "r");
    dreiAus = fopen("drei.aus", "w+");
    vierAus = fopen("vier.aus", "w+");
    printf("Bitte geben Sie die Gewinnzahlen mit einem Komma getrennt an.\nBeispiel: \"5, 6, 9, 2, 5\"\n");
    scanf("%i, %i, %i, %i, %i", &gewinnZahlen[0], &gewinnZahlen[1], &gewinnZahlen[2], &gewinnZahlen[3], &gewinnZahlen[4], &gewinnZahlen[5]);
    int anzahlTipps = 0;
    int gueltigeTipps = 0;
    int matches;
    int dreiRichtig = 0;
    int vierRichtig = 0;
    int fuenfodersechsRichtig = 0;
    while(fgets(zeile, 61, tipps) != NULL) // gibt uns eine Zeile wieder (mit Zeilenumbruch)
    {
        matches = 0;
        anzahlKreuze = 0;
        tippAuswerten(zeile, snrTnr, &anzahlKreuze, kreuze);
        anzahlTipps++;
        if (anzahlKreuze <= 6)
        {
            gueltigeTipps++;
        }
        for (int i=0; i<6; i++)
        {
            if (kreuze[i] == gewinnZahlen[i])
            {
                matches++;
            }
        }
        switch (matches)
        {
            case 3:
                dreiRichtig++;
                fputs(snrTnr, dreiAus);
                fputs("\n", dreiAus);
                break;
            case 4:
                vierRichtig++;
                fputs(snrTnr, vierAus);
                fputs("\n", vierAus);
                break;
            case 5:
                fuenfodersechsRichtig++;
                break;
            case 6:
                fuenfodersechsRichtig++;
                break;
        }
    }
    printf("Anzahl der Tipps: %i\n", anzahlTipps);
    printf("Anzahl der gültigen Tipps: %i\n", gueltigeTipps);
    printf("Anzahl der Tipps mit 3 Richtigen: %i\n", dreiRichtig);
    printf("Anzahl der Tipps mit 4 Richtigen: %i\n", vierRichtig);
    printf("Anzahl der Tipps mit 5 oder 6 Richtigen: %i\n", fuenfodersechsRichtig);
    return 0;
}

void tippAuswerten(const char* zeile, char* snrTnr, int* anzahlKreuze, int kreuze[])
{
    strncpy(snrTnr, zeile, 9);
    int j;
    int k = 0;
    for(int i=10; i<60; i++)
    {
        j = i-9;
        if (zeile[i] == 'X')
        {
            (*anzahlKreuze)++;
            if (k < 6) // max. 6 Kreuzchen
            {
                kreuze[k] = j;
                k++;
            }
        }
    }
}
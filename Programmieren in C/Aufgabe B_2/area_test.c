// Programmieren in C, RUB, WS 2016/17, Kapitel 11/12
// Bspl.: Spielfeld
// Datei: area_test.c
// Standard: C99-C11

// Test der Spielfeld-Funktionen initArea und showArea

#include <stdio.h>
#include "area.h"

int main ()
{
  /*** Erster Test ***/

  char test [][5] = {"ABCDE",
                     "BCDEA",
                     "CDEAB",
                     "DEABC",
                     "EABCD"};
  showArea (5, test);
  initArea (5, test);
  showArea (5, test);
  printf ("\n");

  /*** Zweiter Test ***/

  // Eingabe
  int laenge;
  printf ("Groesse Spielfeld: ");
  scanf ("%d", &laenge);

  if (laenge < 1)
  {
    printf ("Zu klein!\n");
    return 9999;
  }

  printf ("\n");

  // Spielfeld anlegen (variable Länge)
  char raster[laenge][laenge];

  // Spielfeld wird belegt (Leerzeichen)
  initArea (laenge, raster);

  // Mitte des Spielfeld
  raster [laenge/2][laenge/2] = 'M';
  // Hinweis: Die Mitte liegt nur exakt, wenn 'laenge' ungerade ist.
  // Für eine gerade 'laenge' nehmen wir die entsprechende Abweichung hin.

  // Ausgabe des Spielfelds
  showArea (laenge, raster);

  return 0;
}
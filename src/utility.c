#include "../include/utility.h"
#include "../include/appointment.h"
#include <stdio.h>
#include <time.h>

time_t readDate() {
    printf("Bitte geben Sie das Datum im Format TT.MM.JJJJ ein: ");
    char date[11];
    scanf("%s", date);
    struct tm date_tm = {0};

    date_tm.tm_mday = charToInt(date[0]) * 10 + charToInt(date[1]);
    date_tm.tm_mon = charToInt(date[3]) * 10 + charToInt(date[4]) - 1;
    date_tm.tm_year = charToInt(date[6]) * 1000 + charToInt(date[7]) * 100 +
                      charToInt(date[8]) * 10 + charToInt(date[9]) - 1900;
    return mktime(&date_tm);
}

// convert int-char to int
int charToInt(char input) {
  return input - '0';
}

void printOptions() {
    printf(" ----------------------------------------------------- \n");
    printf("| Bitte wählen Sie eine der folgenden Funktionen aus: |\n");
    printf("| 1. Alle Termine (heute)                             |\n");
    printf("| 2. Alle Termine (bestimmter Tag)                    |\n");
    printf("| 3. Alle Termine (gesamt)                            |\n");
    printf("| 4. Neuen Termin erstellen                           |\n");
    printf("| 5. Termin suchen                                    |\n");
    printf("| 6. Termin löschen                                   |\n");
    printf("| 7. Alle Termine löschen                             |\n");
    printf("| 8. Programm beenden                                 |\n");
    printf(" ----------------------------------------------------- \n\n");
    printf("Auswahl Benutzer: ");
}


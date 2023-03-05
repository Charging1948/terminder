#include <stdio.h>
#include <string.h>
#include "../include/functions.h"
#include "../include/utility.h"

int main(int argc, char* argv[]) {
  const char *filename = "termine.txt";
  //print welcome message
  entry();

  if (argc > 1) {
    filename = argv[1];
    printf("Datei '%s' wird zum speichern benutzt.", filename);
  }
  // read appointments from file
  List list = parseFile(filename);

  // print appointments for today
  time_t ct = time(NULL);
  struct tm *ctm = localtime(&ct);
  printList(list, ctm->tm_mday, ctm->tm_mon, ctm->tm_year);

  // print menu
  menu(list);

  // save appointments to file "filename" before exiting
  saveList(list, filename);

  // free memory and exit
  goodbye(list);
  return 0;
}

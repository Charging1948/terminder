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
    printf("Using file %s for appointments", filename);
  }
  // read appointments from file
  List list = parseFile(filename);

  // insert dummy entries for testing with today's date
  time_t ct = time(NULL);
  struct tm *ctm = localtime(&ct);
  insertElement(list, ct, "test1");
  printFullList(list);
  menu(list);

  // save appointments to file "filename" before exiting
  saveList(list, filename);
  goodbye();
  return 0;
}
